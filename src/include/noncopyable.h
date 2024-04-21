#pragma once


// 禁止拷贝和赋值
// 注意：不能在类中使用 = default 来自动生成拷贝和赋值函数
class noncopyable{
public:
    // 删除拷贝构造函数
    noncopyable(const noncopyable&) = delete;
    // 删除拷贝赋值操作符
    noncopyable& operator=(const noncopyable&) = delete;
protected:
    // 默认构造函数
    noncopyable() = default;
    // 析构函数
    ~noncopyable() = default;
};