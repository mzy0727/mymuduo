#include "TcpServer.h"
#include "Acceptor.h"
#include "EventLoop.h"
#include "EventLoopThreadPool.h"
#include "InetAddress.h"
#include "Logger.h"


#include <stdio.h>
#include <functional>
#include <strings.h>

static EventLoop* CheckLoopNotNull(EventLoop* loop){
    if(loop == nullptr){
        LOG_FATAL("mainLoop is null! \n");
    }
    return loop;
}

TcpServer::TcpServer(EventLoop* loop, const InetAddress& listenAddr, const std::string& name, int numThreads, int option)
    : loop_(CheckLoopNotNull(loop)),
      ipPort_(listenAddr.toIPPort()),
      name_(name),
      acceptor_(new Acceptor(loop, listenAddr, option == kReusePort)),
      threadPool_(new EventLoopThreadPool(loop, name_)),
      connectionCallback_(),
      messageCallback_(),
      nextConnId_(1)
{
    acceptor_->setNewConnectionCallback(std::bind(&TcpServer::newConnection, this,std::placeholders::_1, std::placeholders::_2));
}
 TcpServer::~TcpServer(){
    for(auto &item : connections_){
        // 这个局部的shared_ptr对象，出了右括号，会自动调用析构函数，释放资源
        TcpConnectionPtr conn(item.second);
        // 先关闭连接，再删除连接
        item.second.reset();
        conn->getLoop()->runInLoop(std::bind(&TcpConnection::connectDestroyed, conn));
    }
 }
void TcpServer::setThreadNum(int numThreads){
     threadPool_->setThreadNum(numThreads);
}
 // 开启服务器监听
void TcpServer::start(){
     if(started_++ == 0){   // 防止一个Tcpserver对象被start多次
         threadPool_->start(threadInitCallback_);   // 启动底层的loop线程池
         loop_->runInLoop(std::bind(&Acceptor::listen, acceptor_.get()));
     }
}
void TcpServer::newConnection(int sockfd, const InetAddress& peerAddr){
    // 轮询算法，选择一个subloop，来管理channel
    EventLoop* ioLoop = threadPool_->getNextLoop();
    char buf[64] = {0};
    snprintf(buf, sizeof buf, "-%s#%d", ipPort_.c_str(), nextConnId_);
    ++nextConnId_;
    std::string connName = name_ + buf;

    LOG_INFO("TcpServer::newConnection [%s] - new connection [%s] from %s \n", name_.c_str(), connName.c_str(), peerAddr.toIPPort().c_str());

    // 通过sockfd获取其绑定的本机的IP地址和端口信息
    sockaddr_in local;
    ::bzero(&local, sizeof local);
    socklen_t addrlen = sizeof local;
    if(::getsockname(sockfd, (sockaddr*)&local, &addrlen) < 0){
        LOG_ERROR("sockets::getLocalAddr");
    }

    InetAddress localAddr(local);

    // 根据连接成功的sockfd，创建TcpConnection对象，并将其加入到map中
    TcpConnectionPtr conn(new TcpConnection(ioLoop, connName, sockfd, localAddr, peerAddr));
    connections_[connName] = conn;
    // 下面的回调都是用户设置给TcpServer => TcpConnection => Channel => Poller => notify channel 调用回调
    conn->setConnectionCallback(connectionCallback_);
    conn->setMessageCallback(messageCallback_);
    conn->setWriteCompleteCallback(writeCompleteCallback_);
    // 设置了如何关闭连接的回调  conn => shutdown
    conn->setCloseCallback(std::bind(&TcpServer::removeConnection, this, std::placeholders::_1));
    // 直接调用TcpConnection的connectEstablished()方法
    ioLoop->runInLoop(std::bind(&TcpConnection::connectEstablished, conn));


}

// 删除连接的回调函数
void TcpServer::removeConnection(const TcpConnectionPtr& conn){
    loop_->runInLoop(std::bind(&TcpServer::removeConnectionInLoop, this, conn));

}
// 删除连接的回调函数，用于在循环中
void TcpServer::removeConnectionInLoop(const TcpConnectionPtr& conn){
    LOG_INFO("TcpServer::removeConnectionInLoop [%s] - connection %s \n", name_.c_str(), conn->name().c_str());
   
    connections_.erase(conn->name());
    EventLoop *ioLoop = conn->getLoop();
    ioLoop->queueInLoop(std::bind(&TcpConnection::connectDestroyed, conn));


}