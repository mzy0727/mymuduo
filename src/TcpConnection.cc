#include "TcpConnection.h"
#include "Channel.h"
#include "EventLoop.h"
#include "Socket.h"
#include "Logger.h"
#include "errno.h"

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/tcp.h>
#include<sys/socket.h>
#include<string.h>
#include<atomic>
#include<string>
#include<functional>

static EventLoop* CheckLoopNotNull(EventLoop* loop){
    if(loop == nullptr){
        LOG_FATAL("TcpConnection Loop is null! \n");
    }
    return loop;
}

TcpConnection::TcpConnection(EventLoop *loop,
                    const std::string &name,
                    int sockfd,
                    const InetAddress &localAddr,
                    const InetAddress &peerAddr)
                    :loop_(CheckLoopNotNull(loop)),
                    name_(name),
                    state_(kConnecting),
                    reading_(true),
                    socket_(new Socket(sockfd)),
                    channel_(new Channel(loop, sockfd)),
                    localAddr_(localAddr),
                    peerAddr_(peerAddr),
                    highWaterMark_(64*1024*1024)  //64M


{
    // 下面给channel_设置回调函数 ，poller给channel通知感兴趣的事件发生了，channel会回调相应的操作函数
    channel_->setReadCallback(std::bind(&TcpConnection::handleRead, this, std::placeholders::_1));
    channel_->setWriteCallback(std::bind(&TcpConnection::handleWrite, this));
    channel_->setCloseCallback(std::bind(&TcpConnection::handleClose, this));
    channel_->setErrorCallback(std::bind(&TcpConnection::handleError, this));
    LOG_INFO("TcpConnection::ctor[%s] at %p fd=%d\n", name_.c_str(), this, sockfd);
    socket_->setKeepAlive(true);
}

TcpConnection::~TcpConnection(){
    LOG_INFO("TcpConnection::dtor[%s] at %p fd=%d state=%d\n", name_.c_str(), this, channel_->fd(), (int)state_);
}

void TcpConnection::send(const std::string &buf){
    if(state_ == kConnected){
        if(loop_->isInLoopThread()){
           sendInLoop(buf.c_str(),buf.size());
        }else{
            loop_->runInLoop(std::bind(&TcpConnection::sendInLoop, this, buf.c_str(), buf.size()));
        }
    }
}
// 发生数据 应用写的快 而内核发送数据慢 需要把待发送数据写入缓冲区， 而且设置了水位回调
void TcpConnection::sendInLoop(const void *data, int len){
    ssize_t nwrote = 0;
    size_t remaining = len;
    bool faultError = false;
    // 之前调用过该connection的shutdown，那么就不需要再发送数据了
    if(state_ == kDisconnected){
        LOG_ERROR("disconnected, give up writing\n");
        return ;
    }
    // 如果当前没有在写缓冲区，那么需要先设置水位回调
    // channel_第一次开始写数据，而且缓冲区没有待发送的数据
    if(!channel_->isWriting() && outputBuffer_.readableBytes() == 0){
        nwrote = ::write(channel_->fd(), data, len);
        if(nwrote >= 0){
            remaining = len - nwrote;
            if(remaining == 0 && writeCompleteCallback_){
                // 既然在这里数据全部发送完成，就不用再给channel设置epollout事件了
                loop_->queueInLoop(std::bind(writeCompleteCallback_, shared_from_this()));
            }
        }else{
            nwrote = 0;
            if(errno != EWOULDBLOCK){       // 非阻塞无数据
                LOG_ERROR("TcpConnection::sendInLoop\n");
                if(errno == EPIPE || errno == ECONNRESET){ // SIGPIPE RESET
                    faultError = true;
                }
            }
        }
    }
    // 说明当前这一次write，并没有把数据全部发送出去，剩余的数据需要保存到缓冲区当中，然后给channel
    // 注册epollout事件，poller发现tcp的发送缓冲区有空间，会通知相应的sock-channel，调用writeCallback_回调方法
    // 也就是调用TcpConnection::handleWrite方法，把发送缓冲区中的数据全部发送完成
    if(!faultError && remaining > 0){
        // 目前发送缓冲区剩余
        size_t oldLen = outputBuffer_.readableBytes();
        if(oldLen + remaining >= highWaterMark_ && oldLen < highWaterMark_ && highWaterMarkCallback_){
            loop_->queueInLoop(
                    std::bind(highWaterMarkCallback_, shared_from_this())
                );        
            }
        outputBuffer_.append(static_cast<const char*>(data)+nwrote, remaining);
        if(!channel_->isWriting()){
            // 这里一定要注册channel的写事件，否则poller不会给channel通知epollout
            channel_->enableWriting();
        }
    }
}
void TcpConnection::handleRead(Timestamp receiveTime){
    int savedErrno = 0;
    ssize_t n = inputBuffer_.readFd(channel_->fd(), &savedErrno);
    if(n > 0){
        // 已建立连接的用户，有可读事件发生了，调用用户传入的回调操作onMessage
        messageCallback_(shared_from_this(), &inputBuffer_, receiveTime);
    }else if(n == 0){
        handleClose();
    }else{
        errno = savedErrno;
        LOG_ERROR("TcpConnection::handleRead\n");
        handleError();
    }
}
void TcpConnection::handleWrite(){
    int savedErrno = 0;
    if(channel_->isWriting()){
        ssize_t n = outputBuffer_.writeFd(channel_->fd(),&savedErrno);
        if(n > 0){
            outputBuffer_.retrieve(n);
            if(outputBuffer_.readableBytes() == 0){
                channel_->disableWriting();
                if(writeCompleteCallback_){
                    // 唤醒loop对应的thread线程，，执行回调
                    loop_->queueInLoop(std::bind(writeCompleteCallback_, shared_from_this()));
                }
                if(state_ == kDisconnecting){
                    shutdownInLoop();
                }
            }
        }else{
            LOG_ERROR("TcpConnection::handleWrite\n");
        }
    }else{
        LOG_ERROR("TcpConnection fd=%d is down, no more writing\n", channel_->fd());
    }
}
// 底层 poller => channel::closeCallback =>TcpConnection::handleClose
void TcpConnection::handleClose(){
    LOG_INFO("fd = %d,TcpConnection::handleClose state=%d\n", channel_->fd(),(int)state_);
    setState(kDisconnected);
    channel_->disableAll();

    TcpConnectionPtr connPtr(shared_from_this());
    connectionCallback_(connPtr);      // 执行连接关闭的回调
    closeCallback_(connPtr);           // 关闭连接的回调  执行的是TcpServer::removeConnection
}
void TcpConnection::handleError(){
    int optval;
    socklen_t optlen = sizeof(optval);
    // 获取SO_ERROR选项的值
    int err = 0;
    if(::getsockopt(channel_->fd(), SOL_SOCKET, SO_ERROR, &optval, &optlen) < 0){
        err = errno;
    }else{
        err = optval;
    }
    LOG_ERROR("TcpConnection::handleError name=%s - SO_ERROR = %d\n", name_.c_str(), err);
}

// 连接建立
void TcpConnection::connectEstablished(){
    setState(kConnected);
    channel_->tie(shared_from_this());
    channel_->enableReading();      // 向poller注册channel的epollin事件
    // 连接建立，调用用户传入的回调操作
    connectionCallback_(shared_from_this());
}
// 连接销毁
void TcpConnection::connectDestroyed(){
    if(state_ == kConnected){
        setState(kDisconnected);
        channel_->disableAll();    // 把channel的所有感兴趣的事件，从poller中del掉

        connectionCallback_(shared_from_this());
    }
    channel_->remove();         // 把channel从poller中删除
}   

 void TcpConnection::shutdown(){
    if(state_ == kConnected){
        setState(kDisconnecting);
        loop_->runInLoop(std::bind(&TcpConnection::shutdownInLoop, this));
    }
 }

 void TcpConnection::shutdownInLoop(){
    if(!channel_->isWriting()){         // 说明outputBuffer中没有数据
        socket_->shutdownWrite();       // 关闭写端
    }
 }