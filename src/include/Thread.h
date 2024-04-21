#pragma once
#include "noncopyable.h"

#include<thread>
#include<memory>
#include<functional>
#include<string>
#include<atomic>


class Thread : noncopyable{
public:
    // 使用 std::function 作为回调函数类型
    using ThreadFunc = std::function<void()>;
    // 构造函数，传入一个函数和一个名称
    explicit Thread(ThreadFunc, const std::string& name = std::string());
    // 析构函数
    ~Thread();

    // 启动线程
    void start();
    // 等待线程结束
    void join();

    // 判断线程是否已经启动
    bool started() const { return started_; }
    // 获取线程的 tid
    pid_t tid() const { return tid_; }
    // 获取线程的名称
    const std::string& name() const { return name_; }

    // 获取创建的线程数量
    static int numCreated() { return numCreated_; }
private:
    // 设置默认的名称
    void setDefaultName();

    // 线程是否已经启动
    bool started_;
    // 线程是否已经结束
    bool joined_;
    // 线程对象
    std::shared_ptr<std::thread> thread_;
    // 线程的 tid
    pid_t tid_;
    // 回调函数
    ThreadFunc func_;
    // 名称
    std::string name_;

    // 线程计数器
    static  std::atomic_int numCreated_;     
};