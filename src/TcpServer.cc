#include "TcpServer.h"
#include "Acceptor.h"
#include "EventLoop.h"
#include "EventLoopThreadPool.h"
#include "InetAddress.h"
#include "Logger.h"


#include <stdio.h>
#include <functional>

EventLoop* CheckLoopNotNull(EventLoop* loop){
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
 