#pragma once

#include "noncopyable.h"
#include "Timestamp.h"
#include "CurrentThread.h"

#include <atomic>
#include <functional>
#include <vector>
#include <memory>
#include <mutex>

class Channel;
class Poller;

class EventLoop : noncopyable{
public:
    using Functor = std::function<void()>;

    EventLoop();
    ~EventLoop();

    void loop();    // 开始事件循环
    void quit();    // 退出事件循环

    Timestamp pollReturnTime() const { return pollReturnTime_; }
    // 在当前loop中执行cb
    void runInLoop(Functor cb);  
    // 把cb放入队列中，唤醒loop所在的线程，执行cb
    void queueInLoop(Functor cb);  // 将cb放入pendingFunctors_中
    // 用来唤醒loop所在线程
    void wakeup();  // mianrector唤醒subrector

    // EventLoop的方法=》 Poller的方法
    void updateChannel(Channel* channel);  // 更新channel
    void removeChannel(Channel* channel);  // 移除channel
    bool hasChannel(Channel* channel) const;  // 判断channel是否在poller中
    // 判断Eventloop对象是否在自己的线程里
    bool isInLoopThread() const { return threadId_ == CurrentThread::tid(); }

private:
    void handleRead();  // 处理poller返回的channel
    void doPendingFunctors();  // 处理pendingFunctors_中的回调函数

    std::atomic_bool looping_; // 记录当前loop是否在运行
    std::atomic_bool quit_; // 记录当前loop是否要退出

    const pid_t threadId_;  // 记录当前loop所在线程的id

    Timestamp pollReturnTime_; // 记录poller返回的时间
    std::unique_ptr<Poller> poller_; 

    // 主要作用，当mainLoop获取一个新用户的channel，通过轮询算法选择一个subloop，通过该成员唤醒subloop处理channel  
    int wakeupFd_;  // 用于唤醒poller的fd
    std::unique_ptr<Channel> wakeupChannel_; 

    using ChannelList = std::vector<Channel*>;
    ChannelList activeChannels_; // 当前激活的channel
    Channel* currentActiveChannel_; // 当前正在处理的channel

    std::atomic_bool callingPendingFunctors_; // 记录当前loop是否在调用pendingFunctors_
    std::vector<Functor> pendingFunctors_;  
    std::mutex mutex_;  // 互斥锁，保证pendingFunctors_的线程安全

};