#pragma once

#include "noncopyable.h"

#include <functional>
#include <memory>
#include <vector>
#include <string>

class EventLoop;
class EventLoopThread;

class EventLoopThreadPool : noncopyable{
public:
    using ThreadInitCallback = std::function<void(EventLoop*)>;
    
    // 构造函数
    EventLoopThreadPool(EventLoop* baseLoop, const std::string& name);
    // 析构函数
    ~EventLoopThreadPool();
    // 设置线程数量
    void setThreadNum(int numThreads) {numThreads_ = numThreads;}
    // 启动线程池
    void start(const ThreadInitCallback &cb = ThreadInitCallback());

    // 获取下一个线程
    EventLoop* getNextLoop();

    // 判断是否已经启动
    bool started() const {return started_;}
    // 获取名称
    const std::string& name() const {return name_;}
    
    std::vector<EventLoop*> getAllLoops();

private:
    // 基础事件循环
    EventLoop* baseLoop_;
    // 名称
    std::string name_;
    // 是否已经启动
    bool started_;
    // 线程数量
    int numThreads_;
    // 下一个线程索引
    int next_;
    // 线程池
    std::vector<std::unique_ptr<EventLoopThread>> threads_;
    // 事件循环
    std::vector<EventLoop*> loops_;
};
