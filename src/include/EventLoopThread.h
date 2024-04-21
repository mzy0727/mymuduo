#pragma once
#include "noncopyable.h"
#include "Thread.h"

#include <functional>
#include <mutex>
#include <condition_variable>

class EventLoop;

class EventLoopThread{

public:
    // 定义一个回调函数类型，参数为EventLoop*
    using TreadInitCallback = std::function<void(EventLoop*)>;
    // 构造函数，参数为回调函数和线程名
    EventLoopThread(const TreadInitCallback& cb = TreadInitCallback(),
    const std::string& name = std::string());
    // 析构函数
    ~EventLoopThread();
    // 开始循环
    EventLoop* startLoop();
private:
    // 线程函数
    void threadFunc();

    // 事件循环
    EventLoop* loop_;
    // 是否正在退出
    bool exiting_;
    // 线程对象
    Thread thread_;
    // 线程锁
    std::mutex mutex_;
    // 条件变量
    std::condition_variable cond_;
    // 线程初始化回调函数
    TreadInitCallback cb_;

};
