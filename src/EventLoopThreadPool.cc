#include "EventLoopThreadPool.h"
#include "EventLoopThread.h"
#include "EventLoop.h"
 // 构造函数
EventLoopThreadPool::EventLoopThreadPool(EventLoop* baseLoop, const std::string& name)
    : baseLoop_(baseLoop),
      name_(name),
      started_(false),
      numThreads_(0),
      next_(0)
{

}
// 析构函数
EventLoopThreadPool::~EventLoopThreadPool(){

}
// 启动线程池
void EventLoopThreadPool::start(const ThreadInitCallback &cb){
    // 设置开始标志
    started_ = true;
    // 遍历numThreads_个线程
    for(int i = 0; i < numThreads_; ++i){
        // 分配内存
        char buf[name_.size() + 32];
        // 使用snprintf函数格式化字符串
        snprintf(buf, sizeof buf, "%s%d", name_.c_str(), i);
        // 创建线程
        EventLoopThread* t = new EventLoopThread(cb, buf);
        // 存储线程
        threads_.push_back(std::unique_ptr<EventLoopThread>(t));
        // 存储loop
        loops_.push_back(t->startLoop());
    }
    // 如果numThreads_为0，且cb不为空，则调用cb函数
    if(numThreads_ == 0 && cb){
        cb(baseLoop_);
    }
}

// 获取下一个线程
EventLoop* EventLoopThreadPool::getNextLoop(){
    EventLoop* loop = baseLoop_;
    if(!loops_.empty()){    // 通过轮询获取下一个处理事件的loop
        loop = loops_[next_];
        ++next_;
        if(next_ >= loops_.size()){
            next_ = 0;
        }
    }
    return loop;
}

std::vector<EventLoop*> EventLoopThreadPool::getAllLoops(){
    if(loops_.empty()){
        return std::vector<EventLoop*>(1, baseLoop_);
    }else{
        return loops_;
    }
}