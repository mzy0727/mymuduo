#pragma once
#include "Poller.h"

#include <sys/epoll.h>
#include <vector>

class Channel;
// 定义一个类，继承自Poller类
class EPollPoller : public Poller {
public:
    // 构造函数
    EPollPoller(EventLoop* loop);
    // 析构函数
    ~EPollPoller() override;

    // 轮询事件，timeoutMs为超时时间，activeChannels为待激活事件
    Timestamp poll(int timeoutMs, ChannelList* activeChannels) override;
    // 更新Channel
    void updateChannel(Channel* channel) override;
    // 移除Channel
    void removeChannel(Channel* channel) override;

private:
    // 初始化事件列表大小
    static const int kInitEventListSize = 16;
    
    // 填充激活事件
    void fillActiveChannels(int numEvents, ChannelList* activeChannels) const;

    // 更新操作
    void update(int operation, Channel* channel);
    
    // 使用std::vector封装epoll_event
    using EventList = std::vector<struct epoll_event>;

    int epollfd_;
    // 事件列表
    EventList events_;

};