#pragma once

#include "noncopyable.h"
#include "InetAddress.h"
#include "Callbacks.h"
#include "Buffer.h"
#include "Timestamp.h"


#include <memory>
#include <string>
#include <atomic>

class Channel;
class EventLoop;
class Socket;
/*
TcpServer =>Acceptor => 有一个新用户的连接，通过accpet函数拿到connfd

=>TcpConnection 设置相应回调 => Channel => Poller => Channel的回调操作
*/
class TcpConnection : noncopyable,public std::enable_shared_from_this<TcpConnection>{
public:
    TcpConnection(EventLoop *loop,
                    const std::string &name,
                    int sockfd,
                    const InetAddress &localAddr,
                    const InetAddress &peerAddr);

    ~TcpConnection();

    EventLoop *getLoop() const { return loop_; }
    const std::string &name() const { return name_; }
    const InetAddress &localAddress() const { return localAddr_; }
    const InetAddress &peerAddress() const { return peerAddr_; }
    
    bool connected() const { return state_ == kConnected; }
    // 发送数据
    void send(const std::string &buf);
    // 关闭连接
    void shutdown();

    void setConnectionCallback(const ConnectionCallback &cb) { connectionCallback_ = cb; }
    void setMessageCallback(const MessageCallback &cb) { messageCallback_ = cb; }
    void setWriteCompleteCallback(const WriteComleteCallback &cb) { writeCompleteCallback_ = cb; }
    void setHighWaterMarkCallback(const HighWaterMarkCallback &cb, size_t highWaterMark) { highWaterMarkCallback_ = cb; highWaterMark_ = highWaterMark;}
    void setCloseCallback(const CloseCallback &cb) { closeCallback_ = cb; }

    // 连接建立
    void connectEstablished();
    // 连接销毁
    void connectDestroyed();

    
private:
    enum StateE{
        // 未连接
        kDisconnected,
        // 正在连接
        kConnecting,
        // 连接成功
        kConnected,
        // 正在断开连接
        kDisconnecting,
    };
    void setState(StateE state) { state_ = state; }
    void handleRead(Timestamp receiveTime);
    void handleWrite();
    void handleClose();
    void handleError();

    // void send(const std::string &buf);

    void sendInLoop(const void *message, int len);

   
    void shutdownInLoop();
    EventLoop *loop_;   // 这里绝对不是baseloop，因为tcpconnection是在subloop中管理的
    // 定义一个常量name_，用于存储套接字的名称
    const std::string name_;
    // 使用std::atomic_int类型定义一个变量state_，用于存储套接字的当前状态
    std::atomic_int state_;
    // 定义一个变量reading_,用于存储读取标志
    bool reading_;

    // 使用std::unique_ptr<Socket>类型定义一个变量socket_，用于存储套接字
    std::unique_ptr<Socket> socket_;
    // 使用std::unique_ptr<Channel>类型定义一个变量channel_,用于存储通道
    std::unique_ptr<Channel> channel_;

    // 定义两个常量localAddr_和peerAddr_，分别用于存储本地地址和对端地址
    const InetAddress localAddr_;
    const InetAddress peerAddr_;
    
    // 回调函数
    ConnectionCallback connectionCallback_;
    MessageCallback messageCallback_;
    WriteComleteCallback writeCompleteCallback_;
    CloseCallback closeCallback_;
    HighWaterMarkCallback highWaterMarkCallback_;
    
    size_t highWaterMark_;

    // 定义输入缓冲区inputBuffer_和输出缓冲区outputBuffer_
    Buffer inputBuffer_;
    Buffer outputBuffer_;
};
