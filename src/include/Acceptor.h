#pragma once
#include "noncopyable.h"
#include "Socket.h"
#include "Channel.h"

#include <functional>

class EventLoop;
class InetAddress;

class Acceptor : noncopyable{
public:
    // 定义一个新的连接回调函数类型，该函数接受一个整数socketfd和一个网络地址const InetAddress&作为参数
    using NewConnectionCallback = std::function<void(int socketfd, const InetAddress& )>;

    // 构造函数，传入事件循环、监听地址和是否重用端口
    Acceptor(EventLoop* loop, const InetAddress& listenAddr,bool reuseport);
    ~Acceptor();

    // 设置新连接回调函数
    void setNewConnectionCallback(const NewConnectionCallback& cb) {
        newConnectionCallback_ = cb;
    }

    // 开始监听
    void listen();
    // 判断是否正在监听
    bool listening() const {return listening_;}

private:
    // 处理读事件
    void handleRead();

    EventLoop* loop_;   // Acceptor用的就是用户定义的那个baseLoop，也称作mainLoop
    Socket acceptSocket_;
    Channel acceptChannel_;
    NewConnectionCallback newConnectionCallback_;
    bool listening_;
    int idleFd_;


};