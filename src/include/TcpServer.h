#pragma once
#include "TcpServer.h"
#include "Acceptor.h"
#include "EventLoopThreadPool.h"
#include "TcpConnection.h"
#include "Buffer.h"
#include "Callbacks.h"


#include <functional>
#include <memory>
#include <string>
#include <atomic>
#include <unordered_map>

class EventLoop;
class InetAddress;


class TcpServer{
public:
    using ThreadInitCallback = std::function<void(EventLoop*)>;
    enum Option{
        kNoReusePort,
        kReusePort,
    };
    TcpServer(EventLoop* loop, const InetAddress& listenAddr, const std::string& name, int numThreads = 0, int option = kNoReusePort);
    ~TcpServer();

    void setThreadInitCallback(const ThreadInitCallback& cb){
        threadInitCallback_ = cb;
    }
    void setConnectionCallback(const ConnectionCallback& cb){
        connectionCallback_ = cb;
    }
    void setMessageCallback(const MessageCallback& cb){
        messageCallback_ = cb;
    }
    void setWriteCompleteCallback(const WriteComleteCallback& cb){
        writeCompleteCallback_ = cb;
    }
    // 设置底层subloop的个数
    void setThreadNum(int numThreads);
    // 开启服务器监听
    void start();

    const std::string& ipPort() const {
        return ipPort_;
    }

    const std::string& name() const {
        return name_;
    }

    EventLoop* getLoop() const {
        return loop_;
    }

    
    
    


private:
    // 等待新连接的回调函数
    void newConnection(int sockfd, const InetAddress& peerAddr);
    // 删除连接的回调函数
    void removeConnection(const TcpConnectionPtr& conn);
    // 删除连接的回调函数，用于在循环中
    void removeConnectionInLoop(const TcpConnectionPtr& conn);


    // 当前服务器运行的事件循环
    using ConnectionMap = std::unordered_map<std::string, std::shared_ptr<TcpConnection>>;

    EventLoop* loop_;
    // 表示当前服务器的ip和端口
    const std::string ipPort_;
    // 表示当前服务器的名称
    const std::string name_;
    // 创建一个acceptor
    std::unique_ptr<Acceptor> acceptor_;
    // 创建一个线程池
    std::shared_ptr<EventLoopThreadPool> threadPool_;

    // 连接回调
    ConnectionCallback connectionCallback_;     // 有新连接时的回调
    MessageCallback messageCallback_;            // 有读写消息时的回调
    WriteComleteCallback writeCompleteCallback_;

    // 线程初始化回调
    ThreadInitCallback threadInitCallback_; // loop线程初始化的回调

    // 用于判断是否已经启动
    std::atomic_int started_;

    // 用于记录连接的id
    int nextConnId_;
    // 保存所有的连接
    ConnectionMap connections_; // 保存所有的连接

};