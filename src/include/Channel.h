#pragma once
#include "noncopyable.h"
#include "Timestamp.h"
#include "EventLoop.h"

#include <functional>
#include <memory>

class EventLoop;

class Channel : noncopyable {
public:
    using EventCallback = std::function<void()>;
    using ReadEventCallback = std::function<void(Timestamp)>;
    
    Channel(EventLoop* loop, int fd);
    ~Channel();

    // fd得到poller通知以后，处理事件的
    void handleEvent(Timestamp receiveTime);
    // 设置读回调函数
    void setReadCallback(ReadEventCallback cb){
        // 将传入的回调函数移动到成员变量
        readCallback_ = std::move(cb);
    }
    // 设置写回调函数
    void setWriteCallback(EventCallback cb){
        // 将传入的回调函数移动到成员变量
        writeCallback_ = std::move(cb);
    }
    // 设置关闭回调函数
    void setCloseCallback(EventCallback cb){
        // 将传入的回调函数移动到成员变量
        closeCallback_ = std::move(cb);
    }

    // 1. tie：
    // 将一个共享指针与事件循环关联
    // 防止当channel被手动remove掉，channel还在执行回调操作
    void tie(const std::shared_ptr<void>&);

    // 2. fd：
    // 返回文件描述符
    int fd()  const {   return fd_; }
    // 返回事件
    int events() const {    return events_; }
    // 设置接收事件
    void set_revents(int revt) {   revents_ = revt; }
    // 判断是否为空事件
    bool isNoneEvent() const {   return events_ == kNoneEvent; }

    // 3. 启用/禁用读/写事件
    void enableReading() { events_ |= kReadEvent; update(); }
    void disableReading() { events_ &= ~kReadEvent; update(); }
    void enableWriting() { events_ |= kWriteEvent; update(); }
    void disableWriting() { events_ &= ~kWriteEvent; update(); }
    void disableAll() { events_ = kNoneEvent; update(); }
    // 判断是否正在写
    bool isWriting() const {   return events_ & kWriteEvent; }
    // 判断是否正在读
    bool isReading() const {   return events_ & kReadEvent; }

    // 4. 获取事件循环
    EventLoop* ownerLoop() { return loop_; }
    // 从事件循环中移除
    void remove();

    int index() const { return index_; }
    void set_index(int idx) { index_ = idx; }


private:
    void update();
    void handleEventWithGuard(Timestamp receiveTime);
    
    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;

    // 事件循环
    EventLoop* loop_;
    // 文件描述符
    const int fd_;
    // 感兴趣的事件
    int events_;
    // poller返回的具体发生的事件
    int revents_;
    // 索引
    int index_;

    // 弱引用
    std::weak_ptr<void> tie_;
    // 是否绑定
    bool tied_;
    // 读回调
    ReadEventCallback readCallback_;
    // 写回调
    EventCallback writeCallback_;
    // 关闭回调
    EventCallback closeCallback_;
    // 错误回调
    EventCallback errorCallback_;
};