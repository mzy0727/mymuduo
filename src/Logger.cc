#include "Logger.h"
#include "Timestamp.h"

#include <iostream>

/**
 * @brief 获取单例对象
 * @return 
 * @note 
 * @author mzy
 * @date 2024-04-16
*/
Logger& Logger::getInstance(){
    static Logger instance;
    return instance;
}
/**
 * @brief 设置日志级别
 * @param level 日志级别
 * @return
 * @note 
 * @author mzy
 * @date 2024-04-16
*/

void Logger::setLogLevel(int level){
    logLevel_ = level;
}
/**
 * @brief 写日志
 * @param msg 日志信息
 * @return
 * @note 
 * @author mzy
 * @date 2024-04-16
*/
void Logger::writeLog(std::string msg){
    switch (logLevel_)
    {
        case INFO:
            // 打印INFO日志
            std::cout << "[INFO]";
            break;
        
        case FATAL:
            // 打印FATAL日志
            std::cout << "[FATAL]";
            break;
        
        case ERROR:
            // 打印ERROR日志
            std::cout << "[ERROR]";
            break;
        
        default:
            // 打印默认日志
            break;
    }
    
    // 输出当前时间戳和消息
    std::cout << Timestamp::now().toString() << " " << msg << std::endl;
}