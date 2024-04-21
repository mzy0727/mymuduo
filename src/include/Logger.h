#include <string>

#include "noncopyable.h"

// logger.writeLog(std::string(logmsgFormat).c_str(), ##__VA_ARGS__); 

#define LOG_INFO(logmsgFormat, ...) \
    do{ \
        Logger& logger = Logger::getInstance(); \
        logger.setLogLevel(LogLevel::INFO); \
        char buf[1024] = {0};   \
        snprintf(buf, 1024, logmsgFormat, ##__VA_ARGS__); \
        logger.writeLog(std::string(buf)); \
    }while(0)

#define LOG_ERROR(logmsgFormat, ...) \
    do{ \
        Logger& logger = Logger::getInstance(); \
        logger.setLogLevel(LogLevel::ERROR); \
        char buf[1024] = {0};   \
        snprintf(buf, 1024, logmsgFormat, ##__VA_ARGS__); \
        logger.writeLog(std::string(buf)); \
    }while(0)

#define LOG_FATAL(logmsgFormat, ...) \
    do{ \
        Logger& logger = Logger::getInstance(); \
        logger.setLogLevel(LogLevel::FATAL); \
        char buf[1024] = {0};   \
        snprintf(buf, 1024, logmsgFormat, ##__VA_ARGS__); \
        logger.writeLog(std::string(buf)); \
        exit(1); \
    }while(0)
    
// 为满足条件mu_debug，定义DEBUG级别的日志输出
#ifdef MUDEBUG
#define LOG_DEBUG(logmsgFormat, ...) \
    do{ \
        // 获取日志实例
        Logger& logger = Logger::getInstance(); \
        // 设置日志级别为DEBUG
        logger.setLogLevel(LogLevel::DEBUG); \
        // 定义一个字符串缓冲区
        char buf[1024] = {0};   \
        // 使用snprintf函数将格式化后的字符串存入缓冲区
        snprintf(buf, 1024, logmsgFormat, ##__VA_ARGS__); \
        // 使用日志实例的writeLog函数输出日志
        logger.writeLog(std::string(buf)); \
    }while(0)
#else
    // 不满足条件mu_debug，定义空的LOG_DEBUG函数
    #define LOG_DEBUG(logmsgFormat, ...)
#endif

/**
 * @brief 日志级别
 * 
 * 定义日志级别，用于控制日志输出
*/
enum LogLevel {
    INFO,
    ERROR,
    FATAL,
    DEBUG
};

/**
 * @brief 日志类
 * 
 * 单例模式，全局唯一
*/
class Logger : noncopyable {
public:
    //! @brief 获取日志唯一的实例对象
    static Logger& getInstance();
    //! @brief 设置日志级别
    void setLogLevel(int level);
    //! @brief 写日志
    void writeLog(std::string msg);
private:
    int logLevel_;
   
};