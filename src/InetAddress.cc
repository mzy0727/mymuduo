#include "InetAddress.h"

#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>

/**
 * @brief 构造函数
 * @param ip IP地址
 * @param port 端口号
 * @note 
 * @author mzy
 * @date 2024-04-16
*/
 InetAddress::InetAddress(std::string ip, uint16_t port){
    bzero(&addr_, sizeof addr_);
    addr_.sin_family = AF_INET;
    addr_.sin_port = htons(port);
    addr_.sin_addr.s_addr = inet_addr(ip.c_str());
 }

InetAddress::InetAddress(const struct sockaddr_in& addr){
    addr_ = addr;
}

/**
 * @brief 返回IP地址
 * @param 
 * @return 
 * @note 
 * @author mzy
 * @date 2024-04-16
*/
std::string InetAddress::toIP() const{
     char buf[64] = {0};
    inet_ntop(AF_INET, &addr_.sin_addr, buf, sizeof buf);
    return buf;
}
/**
 * @brief 返回IP地址和端口号
 * @param 
 * @return 
 * @note 
 * @author mzy
 * @date 2024-04-16
*/
// 转换为ip:port格式
std::string InetAddress::toIPPort() const{
    // ip:port
    char buf[64] = {0};
    inet_ntop(AF_INET, &addr_.sin_addr, buf, sizeof buf);
    size_t end = strlen(buf);
    uint16_t port = ntohs(addr_.sin_port);
    sprintf(buf+end, ":%u", port);
    return buf;
}
/**
 * @brief 返回端口号
 * @param 
 * @return 
 * @note 
 * @author mzy
 * @date 2024-04-16
*/
uint16_t InetAddress::toPort() const{
    return ntohs(addr_.sin_port);
}
/**
 * @brief 返回sockaddr_in结构体
 * @param 
 * @return 
 * @note 
 * @author mzy
 * @date 2024-04-16 
*/
// 获取socket地址结构体
const struct sockaddr* InetAddress::getSockAddr() const{
    return (struct sockaddr*)&addr_;
}

// #include <iostream>
// int main()
// {
//     InetAddress addr("127.0.0.1", 8080);
//     std::cout << addr.toIP() << std::endl;

//     return 0;
// }