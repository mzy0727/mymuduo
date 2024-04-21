#include "EventLoop.h"
#include "Logger.h"
#include "EPollPoller.h"
#include "Channel.h"

#include <sys/eventfd.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

// 防止一个线程创建多个EventLoop  thread_local == __thread
__thread EventLoop* t_loopInThisThread = nullptr;

// 定义默认的Poller IO复用接口的超时时间
const int kPollTimeMs = 10000;

// 创建wakeupfd，用于notify唤醒subReactor处理新来的channel
int createEventfd(){
    int evtfd = eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
    if(evtfd < 0){
        // 创建失败
        LOG_FATAL("File: %s, Function: %s, Line: %d, eventfd error: %d\n"__FILE__, __func__, __LINE__,errno);
    }
    return evtfd;
}

EventLoop::EventLoop()
    : looping_(false),
      quit_(false),
      callingPendingFunctors_(false),
      threadId_(CurrentThread::tid()),
      poller_(Poller::newDefaultPoller(this)),
      wakeupFd_(createEventfd()),
      wakeupChannel_(new Channel(this, wakeupFd_)),
      currentActiveChannel_(nullptr){
    LOG_DEBUG("EventLoop created %p in thread %d \n", this, threadId_);
    if(t_loopInThisThread){
        // 每个线程只能有一个EventLoop
        LOG_FATAL("Another EventLoop %p exists in this thread %d\n", t_loopInThisThread, threadId_);
    }else{
        t_loopInThisThread = this;
    }

    // 设置wakeupfd的事件类型以及发生事件后的回调操作
    wakeupChannel_->setReadCallback(std::bind(&EventLoop::handleRead, this));
    // 每一个eventloop都将监听wakeupchannel的EPOLLIN读事件了
    wakeupChannel_->enableReading();
}

EventLoop::~EventLoop(){
    // 删除wakeupChannel_
    wakeupChannel_->disableAll();
    wakeupChannel_->remove();
    ::close(wakeupFd_);
    t_loopInThisThread = nullptr;
}

void EventLoop::loop(){
    looping_ = true;
    quit_ = false;

    LOG_INFO("EventLoop %p start looping\n", this);

    while(!quit_){
        activeChannels_.clear();
        pollReturnTime_ = poller_->poll(kPollTimeMs, &activeChannels_);
        for(Channel* channel : activeChannels_){
            // Poller监听哪些channel发生事件了，然后上报给EventLoop，通知channel处理相应的事件
            channel->handleEvent(pollReturnTime_);
        }
        // 执行当前poller_中的所有channel的回调操作
        doPendingFunctors();
    }
    LOG_INFO("EventLoop %p stop looping\n", this);
    looping_ = false;
}

// 退出事件循环  1.loop在自己的线程中调用quit  2.在非loop的线程中，调用loop的quit
void EventLoop::quit(){
    quit_ = true;
    // 如果是在其它线程中，调用的quit   在一个subloop(woker)中，调用了mainLoop(IO)的quit
    if(!isInLoopThread()){
        // 唤醒loop所在的线程
        wakeup();
    }
}
// 在当前loop中执行cb
void EventLoop::runInLoop(Functor cb){
    if(isInLoopThread()){
        cb();
    }else{
        // 调用queueInLoop，将cb放入队列中，由loop所在的线程调用
        queueInLoop(cb);
    }

}
// 将cb放入队列中，由loop所在的线程调用
void EventLoop::queueInLoop(Functor cb){
    {
        // 加锁
        std::unique_lock<std::mutex> lock(mutex_);
        pendingFunctors_.emplace_back(cb);
    }

    // 唤醒loop所在的线程
    // || callingPendingFunctors_的意思是：当前loop正在执行回调，但是loop又有了新的回调
    if(!isInLoopThread() || callingPendingFunctors_){
        wakeup();   
    }
}

// 用来唤醒loop所在的线程,向wakeupfd写一个数据,wakeupfd的读事件会被触发,当前loop线程会调用handleRead
void EventLoop::wakeup(){
    uint64_t one = 1;
    ssize_t n = write(wakeupFd_, &one, sizeof(one));
    if(n != sizeof(one)){
        LOG_ERROR("EventLoop::wakeup() writes %d bytes instead of 8\n", n);
    }
}

void EventLoop::doPendingFunctors(){
    std::vector<Functor> functors;
    // 执行回调
    callingPendingFunctors_ = true;

    {
        // 加锁
        std::lock_guard<std::mutex> lock(mutex_);
        functors.swap(pendingFunctors_);
    }

    for(const Functor& functor : functors){
        functor();  // 执行当前loop需要执行的回调操作
    }

    callingPendingFunctors_ = false;
}

void EventLoop::updateChannel(Channel* channel){
    poller_->updateChannel(channel);    
}
void EventLoop::removeChannel(Channel* channel){
    poller_->removeChannel(channel);
}

bool EventLoop::hasChannel(Channel* channel) const{
    return poller_->hasChannel(channel);
}
void EventLoop::handleRead(){
    uint64_t one = 1;
    ssize_t n = read(wakeupFd_, &one, sizeof(one));
    if(n != sizeof(one)){
        LOG_ERROR("File: %s, Function: %s, Line: %ld, EventLoop::handleRead() reads %ld bytes instead of 8\n",__FILE__, __func__, __LINE__, n);
    }
}