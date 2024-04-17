#pragma once

#include <string>
#include <netinet/in.h>


class InetAddress{

public:
    // 构造函数1
    explicit InetAddress(std::string ip = "127.0.0.1", uint16_t port = 0);
    // 构造函数2
    explicit InetAddress(const struct sockaddr_in& addr);
    // 返回IP地址
    std::string toIP() const;
    // 返回IP地址和端口号
    std::string toIPPort() const;
    // 返回端口号
    uint16_t toPort() const;
    
    // 获取sockaddr指针
    const struct sockaddr* getSockAddr() const;
    // 设置sockaddr指针
    void setSockAddr(const struct sockaddr_in& addr){
        addr_ = addr;
    }
  
private:
    struct sockaddr_in addr_; // 网络字节序

};