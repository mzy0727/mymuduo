#include "Socket.h"
#include "InetAddress.h"
#include "Logger.h"

#include<netinet/in.h>
#include<netinet/tcp.h>
#include<stdio.h>
#include<unistd.h>
#include<strings.h>


Socket::~Socket(){
    ::close(sockfd_);
}

 // 绑定本地地址
void Socket::bindAddress(const InetAddress& localaddr){
    int ret = ::bind(sockfd_, localaddr.getSockAddr(), sizeof(localaddr.getSockAddr()));
    if(ret < 0){
        LOG_FATAL("File: %s, Function: %s, Line: %d, bind sockfd:%d fail\n", __FILE__, __func__, __LINE__,sockfd_);
    }
}

// 监听
void Socket::listen(){
    int ret = ::listen(sockfd_, SOMAXCONN);
    if(ret < 0){
        LOG_FATAL("File: %s, Function: %s, Line: %d, listen sockfd:%d fail\n", __FILE__, __func__, __LINE__,sockfd_);
    }
}

// 接受客户端连接
int Socket::accept(InetAddress* peeraddr){
    sockaddr_in addr;
    socklen_t len = sizeof(addr);
    bzero(&addr, sizeof(addr));
    int connfd = ::accept4(sockfd_, (sockaddr*)&addr,&len,SOCK_NONBLOCK | SOCK_CLOEXEC);
    if(connfd >= 0){
        peeraddr->setSockAddr(addr);
    }
    return connfd;
}

// 关闭写通道
void Socket::shutdownWrite(){
    if(::shutdown(sockfd_, SHUT_WR) < 0){
        LOG_ERROR("File: %s, Function: %s, Line: %d, shutdown write fail\n", __FILE__, __func__, __LINE__);
    }
}

// 设置TCP非延迟
void Socket::setTcpNoDelay(bool on){
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, IPPROTO_TCP, TCP_NODELAY, &optval, static_cast<socklen_t>(sizeof optval));
}
// 设置地址重用
void Socket::setReuseAddr(bool on){
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEADDR, &optval, static_cast<socklen_t>(sizeof optval));
}
// 设置端口重用
void Socket::setReusePort(bool on){
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEPORT, &optval, static_cast<socklen_t>(sizeof optval));
}
// 设置keepalive
void Socket::setKeepAlive(bool on){
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, SOL_SOCKET, SO_KEEPALIVE, &optval, static_cast<socklen_t>(sizeof optval));
}