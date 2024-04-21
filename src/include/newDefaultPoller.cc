#include "Poller.h"
#include "EPollPoller.h"

#include <stdlib.h>

Poller* Poller::newDefaultPoller(EventLoop* loop){
    // 创建poll实例
    if(getenv("MUDUO_USE_POLL")){
        return nullptr;
    }else{   // 创建epoll实例
        return new EPollPoller(loop);
    }
}