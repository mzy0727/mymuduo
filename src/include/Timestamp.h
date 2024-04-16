#pragma once

#include <iostream>
#include <string>

// 定义一个时间戳类，实现非复制构造函数
class Timestamp {

public:
    // 构造函数
    Timestamp(): microSecondsSinceEpoch_(0){}
    // explicit：强制类型转换，将int64_t类型转换为Timestamp类型
    explicit Timestamp(int64_t microSecondsSinceEpoch): microSecondsSinceEpoch_(microSecondsSinceEpoch){}

    // 返回时间戳的字符串表示
    std::string toString() const;

    // 返回当前时间戳
    static Timestamp now();
    
    // 析构函数
    ~Timestamp();
private:
    // 存储时间戳的 microSecondsSinceEpoch
    int64_t microSecondsSinceEpoch_;
};