#include "EPollPoller.h"
#include "Logger.h"
#include "Channel.h"

#include <strings.h>
#include <errno.h>
#include <unistd.h>

// channel未添加到poller中
const int kNew = -1;
// channel已添加到poller中
const int kAdded = 1;
// channel已从poller中删除
const int kDeleted = 2;

// 构造函数 => 对于epoll_create1函数的调用
EPollPoller::EPollPoller(EventLoop* loop)
    : Poller(loop),epollfd_(::epoll_create1(EPOLL_CLOEXEC)),events_(kInitEventListSize) {
    if(epollfd_ < 0){

    }
}
// 析构函数
EPollPoller::~EPollPoller(){
    ::close(epollfd_);
};

 // 轮询事件，timeoutMs为超时时间，activeChannels为待激活事件 => 对于epoll_wait函数的调用
Timestamp EPollPoller::poll(int timeoutMs, ChannelList* activeChannels){
    
    LOG_INFO("File: %s, Function: %s, Line: %d, fd total count: %ld", __FILE__, __func__, __LINE__, channels_.size());
    int numEvents = ::epoll_wait(epollfd_, &events_[0], static_cast<int>(events_.size()), timeoutMs);
    int saveErrno = errno;
    Timestamp now(Timestamp::now());

    if(numEvents > 0){
        LOG_INFO("File: %s, Function: %s, Line: %d, events happened: %d\n", __FILE__, __func__, __LINE__, numEvents);
        // 处理事件
        fillActiveChannels(numEvents, activeChannels);
        if(numEvents == events_.size()){
            // 扩容
            events_.resize(events_.size() * 2);
        }
    }else if(numEvents == 0){
        LOG_DEBUG("File: %s, Function: %s, Line: %d, timeout! \n", __FILE__, __func__, __LINE__);
    }else{
        if(saveErrno != EINTR){
            errno = saveErrno;
            LOG_ERROR("File: %s, Function: %s, Line: %d, epoll_wait error: %d\n", __FILE__, __func__, __LINE__, saveErrno);
        }
    }
    return now;
}

// 填充激活事件
void EPollPoller::fillActiveChannels(int numEvents, ChannelList* activeChannels) const{
    // 遍历numEvents个事件
    for(int i = 0; i < numEvents; ++i){
        // 获取事件中的Channel指针
        Channel* channel = static_cast<Channel*>(events_[i].data.ptr);
        // 设置Channel的revents
        channel->set_revents(events_[i].events);

        // EventLoop就拿到了它的poller给它返回的所有发生事件的channel列表了
        activeChannels->push_back(channel);
    }
}



// 更新Channel =>对于epoll_ctl函数的调用
void EPollPoller::updateChannel(Channel* channel){
    const int index = channel->index();
    LOG_INFO("File: %s, Function: %s, Line: %d, fd = %d, events = %d, op = %d\n", __FILE__, __func__, __LINE__,channel->fd(), channel->events(), index);
    
    if(index == kNew || index == kDeleted){
        
        int fd = channel->fd();
        if(index == kNew){
            // 添加新的fd
            channels_[fd] = channel;
        }else{
            // 已存在删除想重新添加

        }
        channel->set_index(kAdded);
        update(EPOLL_CTL_ADD, channel);
        
    }else{
        int fd = channel->fd();

        if(channel->isNoneEvent()){
            update(EPOLL_CTL_DEL, channel);
            channel->set_index(kDeleted);
        }else{
            update(EPOLL_CTL_MOD, channel);
        }  
    }

}
// 移除Channel =>对于epoll_ctl函数的调用
void EPollPoller::removeChannel(Channel* channel){
    // 获取文件描述符
    int fd = channel->fd();
    // 获取索引
    int index = channel->index();
    // 打印日志
    LOG_INFO("File: %s, Function: %s, Line: %d, fd = %d, events = %d, op = %d\n", __FILE__, __func__, __LINE__, fd, channel->events(), index);

    // 用于存放要移除的fd

    size_t n = channels_.erase(fd);

    // 如果索引为kAdded，则调用update函数，传入参数为EPOLL_CTL_DEL和channel
    if(index == kAdded){
        update(EPOLL_CTL_DEL, channel);
    }
    // 设置索引为kNew
    channel->set_index(kNew);
}

// 更新操作
void EPollPoller::update(int operation, Channel* channel){
    // 创建 epoll_event 结构体
    struct epoll_event event;
    // 初始化 epoll_event 结构体
    bzero(&event, sizeof event);
    // 设置 epoll_event 中的 events 字段
    event.events = channel->events();
    // 将 channel 指针赋值给 epoll_event 结构体中的 data 字段
    event.data.ptr = channel;
    // 获取 channel 的文件描述符
    int fd = channel->fd();
    // 打印日志
    LOG_INFO("File: %s, Function: %s, Line: %d, fd = %d, events = %d, op = %d", __FILE__, __func__, __LINE__, fd, channel->events(), operation);
    // 执行 epoll_ctl 操作
    if(::epoll_ctl(epollfd_, operation, fd, &event) < 0){
        // 如果操作是 EPOLL_CTL_DEL，则打印错误日志
        if(operation == EPOLL_CTL_DEL){
            LOG_ERROR("epoll_ctl del error: %d\n", errno);
        }else{
            // 否则，打印 fatal 日志
           LOG_FATAL("epoll_ctl add/mod error: %d\n", errno);
        }
    }
}