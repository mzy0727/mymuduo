#pragma once

#include "noncopyable.h"
#include "InetAddress.h"
#include "EventLoop.h"
#include "Socket.h"


#include <memory>
#include <string>
#include <atomic>


class TcpConnection : noncopyable{
public:
    TcpConnection(EventLoop *loop,
                    const std::string &name,
                    int sockfd,
                    const InetAddress &localAddr,
                    const InetAddress &peerAddr);

    ~TcpConnection();

    EventLoop *getLoop() const { return loop_; }
private:
    EventLoop *loop_;
    const std::string name_;
    std::atomic_int states;
    bool reading;

    std::unique_ptr<Socket> socket_;
    std::unique_ptr<Channel> channel_;

    const InetAddress localAddr_;
    const InetAddress peerAddr_;
    

};
