#pragma once

#include "noncopyable.h"

class InetAddress;

class Socket : noncopyable{
public:
    // 构造函数
    explicit Socket(int sockfd):sockfd_(sockfd){}
    // 析构函数
    ~Socket();

    // 返回socket文件描述符
    int fd() const { return sockfd_; }

    // 绑定本地地址
    void bindAddress(const InetAddress& loacaladdr);

    // 监听
    void listen();

    // 接受客户端连接
    int accept(InetAddress* peeraddr);

    // 关闭写通道
    void shutdownWrite();

    // 设置TCP非延迟
    void setTcpNoDelay(bool on);
    // 设置地址重用
    void setReuseAddr(bool on);
    // 设置端口重用
    void setReusePort(bool on);
    // 设置keepalive
    void setKeepAlive(bool on);

private:
    // 私有变量
    const int sockfd_;
};

