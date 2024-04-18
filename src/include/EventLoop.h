#pragma once

#include "noncopyable.h"
#include "Timestamp.h"

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
    void loop();
    void quit();
private:
    std::atomic_bool looping_;
    std::atomic_bool quit_;
    std::atomic_bool callingPendingFunctors_;
    const pid_t threadId_;
    Timestamp pollReturnTime_;
    std::unique_ptr<Poller> poller_;
    int wakeupFd_;
    std::unique_ptr<Channel> wakeupChannel_;

    using ChannelList = std::vector<Channel*>;
    ChannelList activeChannels_;
    Channel* currentActiveChannel_;

    std::mutex mutex_;
    std::vector<Functor> pendingFunctors_;

};