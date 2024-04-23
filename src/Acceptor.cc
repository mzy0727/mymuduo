#include "Acceptor.h"
#include "EventLoop.h"
#include "InetAddress.h"
#include "Logger.h"
#include "errno.h"

static int createNonblocking(){
    int sockfd = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, 0);
    if(sockfd < 0){
        LOG_FATAL("%s:%s:%d listen socket create err:%d \n", __FILE__, __FUNCTION__, __LINE__, errno);
    }
    
}

 // 构造函数，传入事件循环、监听地址和是否重用端口
Acceptor::Acceptor(EventLoop* loop, const InetAddress& listenAddr,bool reuseport)
    : loop_(loop),
    acceptSocket_(createNonblocking()),
    acceptChannel_(loop, acceptSocket_.fd()),
    listening_(false)
{
    acceptSocket_.setReuseAddr(true);
    acceptSocket_.setReusePort(reuseport);
    acceptSocket_.bindAddress(listenAddr);
    // TcpServer::start() Acceptor.listen  有新用户的连接，要执行一个回调（connfd=》channel=》subloop）
    // baseLoop => acceptChannel_(listenfd) => handleRead => newConnection => subloop
    acceptChannel_.setReadCallback(std::bind(&Acceptor::handleRead, this));
}
Acceptor::~Acceptor(){
    acceptChannel_.disableAll();
    acceptChannel_.remove();
}

// 开始监听
void Acceptor::listen(){
    // 设置监听状态
    listening_ = true;
    // 开始监听
    acceptSocket_.listen();
    // 使接受通道可读
    acceptChannel_.enableReading(); 
}

// listenfd有事件发生了，就是有新用户连接了
void Acceptor::handleRead(){
    InetAddress peerAddr;
    // 接受新用户连接
    int connfd = acceptSocket_.accept(&peerAddr);
    if(connfd >= 0){
        
        if(newConnectionCallback_){
            // 轮询找到subLoop，唤醒，分发当前的新客户端的Channel
            newConnectionCallback_(connfd, peerAddr);
        }else{
            ::close(connfd);
        }
    }else{
        LOG_ERROR("%s:%s:%d accept err:%d \n", __FILE__, __FUNCTION__, __LINE__, errno);
        if(errno == EMFILE){
            LOG_ERROR("%s:%s:%d asockfd reached limit!\n", __FILE__, __FUNCTION__, __LINE__);
        }
    }
}