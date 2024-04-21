#include "EventLoopThread.h"
#include "EventLoop.h"

 EventLoopThread::EventLoopThread(const TreadInitCallback& cb, const std::string& name)
    : loop_(nullptr),
    exiting_(false),
    thread_(std::bind(&EventLoopThread::threadFunc, this), name),
    cb_(cb),
    mutex_(),
    cond_()
 {

 }
// 析构函数
EventLoopThread::~EventLoopThread(){
    exiting_ = true;
    if(loop_ != nullptr){
        loop_->quit();
        thread_.join();
    }
}
// 开始循环
EventLoop* EventLoopThread::startLoop(){
    //启动线程
    thread_.start();
    EventLoop* loop = nullptr;
    //循环等待EventLoop被创建
    {
        //使用unique_lock锁住mutex
        std::unique_lock<std::mutex> lock(mutex_);
        //等待loop_被设置
        while(loop_ == nullptr){
            //等待cond_.notify_all()
            cond_.wait(lock);
        }
        //获取loop_
        loop = loop_;
    }
    //返回loop_
    return loop_;
}

// 下面这个方法，实在单独的新线程里面运行的
void EventLoopThread::threadFunc(){
    EventLoop loop; // 创建一个独立的eventloop，和上面的线程是一一对应的，one loop per thread
    //回调函数
    if(cb_){
        cb_(&loop);
    }
    //设置loop_
    {
        std::unique_lock<std::mutex> lock(mutex_);
        loop_ = &loop;
        cond_.notify_one();
    }
    //运行loop_
    loop.loop();

    std::unique_lock<std::mutex> lock(mutex_);
    //loop_运行完毕，设置为nullptr
    loop_ = nullptr;
}