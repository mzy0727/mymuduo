#pragma once
#include "noncopyable.h"
#include "Timestamp.h"

#include <vector>
#include <unordered_map>

class Channel;
class EventLoop;

// 封装poll/epoll等
class Poller : noncopyable{
public:
    // 定义一个ChannelList类型，用于存储Channel指针
    using ChannelList = std::vector<Channel*>;
    // 构造函数，传入一个EventLoop指针
    Poller(EventLoop* loop);
    // 析构函数
    virtual ~Poller() = default;

    // 给所有IO复用保留统一的接口
    // 函数poll，传入两个参数，timeoutMs为超时时间，activeChannels为一个ChannelList指针
    virtual Timestamp poll(int timeoutMs, ChannelList* activeChannels) = 0;
    // 函数updateChannel，传入一个Channel指针
    virtual void updateChannel(Channel* channel) = 0;
    // 函数removeChannel，传入一个Channel指针
    virtual void removeChannel(Channel* channel) = 0;
    // 判断参数channel是否在当前Poller当中
    virtual bool hasChannel(Channel* channel) const;

    // EventLoop可以通过该接口获取默认的IO复用的具体实现
    static Poller* newDefaultPoller(EventLoop* loop);

protected:
    // 使用std::unordered_map存储Channel指针
     // map的key：sockfd  value：sockfd所属的channel通道类型
    using ChannelMap = std::unordered_map<int, Channel*>;
    // 定义一个ChannelMap变量，用于存储Channel指针
    ChannelMap channels_;
private:
    // 定义Poller所属的事件循环EventLoop
    EventLoop* ownerloop_;
};