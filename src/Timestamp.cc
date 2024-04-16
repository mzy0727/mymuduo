#include "Timestamp.h"

#include <ctime>

/**
 * @brief 将时间戳转换为格式化字符串。
 * @return 表示时间戳的格式化字符串。
*/
std::string Timestamp::toString() const{
    // 生成格式化的时间字符串
    char buf[128];
    tm *tm_time = localtime(&microSecondsSinceEpoch_);
    snprintf(buf, sizeof(buf), "%4d-%02d-%02d %02d:%02d:%02d",
            tm_time->tm_year + 1900, tm_time->tm_mon + 1, tm_time->tm_mday,
            tm_time->tm_hour, tm_time->tm_min, tm_time->tm_sec);
    return buf;
    
}

/**
 * @brief 获取当前时间的时间戳
 * @return 当前时间的时间戳
*/
Timestamp Timestamp::now(){
    // 返回当前时间的时间戳
    return Timestamp(time(NULL));
}
   