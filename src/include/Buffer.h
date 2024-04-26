#pragma once

#include <string.h>
#include <string>
#include <vector>
#include <algorithm>
// 网络库底层的缓冲区类型定义
class Buffer {
public:
    static const size_t kCheapPrepend = 8;
    static const size_t kInitialSize = 1024;

    explicit Buffer(size_t initialSize = kInitialSize)
        : buffer_(kCheapPrepend + initialSize),
          readerIndex_(kCheapPrepend),
          writerIndex_(kCheapPrepend) 
    {}

    size_t readableBytes() const { return writerIndex_ - readerIndex_; }

    size_t writableBytes() const { return buffer_.size() - writerIndex_; }

    size_t prependableBytes() const { return readerIndex_; }
    // 返回缓冲区中可读数据的起始地址
    const char* peek() const { return begin() + readerIndex_; }


    void retrieve(size_t len) {
        if(len < readableBytes()) {
            readerIndex_ += len;        // 应用只读取了可读缓冲区数据的一部分就是len，还剩下
        }else{
            retrieveall();
        }
    }

    void retrieveall(){
        readerIndex_ = kCheapPrepend;
        writerIndex_ = kCheapPrepend;
    }

    // 把onMessage函数上报的Buffer数据，转成string类型的数据返回
    std::string retrieveAllAsString() {
        return retrieveAsString(readableBytes());
    }

    std::string retrieveAsString(size_t len) {
        std::string result(peek(), len);
        retrieve(len);  // 对缓冲区做复位操作
        return result;
    }
    // buffer_.size - writerIndex_ 表示缓冲区中可写的空间
    void ensureWritableBytes(size_t len) {
        if (writableBytes() < len) {
            makeSpace(len);
        }
    }

    // 把[data, data+len]内存上的数据，添加到writable缓冲区当中
    void append(const char* data, size_t len) {
        ensureWritableBytes(len);
        std::copy(data, data + len, beginWrite());
        writerIndex_ += len;
    }

    char* beginWrite() { return begin() + writerIndex_; }

    const char* beginWrite() const { return begin() + writerIndex_; }

    // 从fd上读取数据
    ssize_t readFd(int fd, int* saveErrno);
    // 通过fd发送数据
    ssize_t writeFd(int fd, int* saveErrno);
    
private:
    char* begin() { return &*buffer_.begin(); }     // 数组起始地址
    const char* begin() const { return &*buffer_.begin(); }

    void makeSpace(size_t len) {

        // 判断可写缓冲区的大小加上预写缓冲区的大小是否小于len加kCheapPrepend
        if (writableBytes() + prependableBytes() < len + kCheapPrepend) {
            // 如果小于，则调整缓冲区的大小
            buffer_.resize(writerIndex_ + len);
        }else {
            
            // 获取可读大小
            size_t readable = readableBytes();
            // 将从readerIndex_到writerIndex_之间的数据复制到缓冲区的kCheapPrepend位置
            std::copy(begin() + readerIndex_, begin() + writerIndex_, begin() + kCheapPrepend);
            // 修改readerIndex_
            readerIndex_ = kCheapPrepend;
            // 修改writerIndex_
            writerIndex_ = readerIndex_ + readable;
        }
    }
    std::vector<char> buffer_;
    size_t readerIndex_;
    size_t writerIndex_;
};