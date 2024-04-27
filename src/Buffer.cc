#include "Buffer.h"

#include <errno.h>
#include <unistd.h>
#include <sys/uio.h>

/**
 * 从fd上读取数据  Poller工作在LT模式
 * Buffer缓冲区是有大小的！ 但是从fd上读数据的时候，却不知道tcp数据最终的大小
 */ 
ssize_t Buffer::readFd(int fd, int* savedErrno){
    char extraBuf[65536] = {0}; // 栈上的内存空间 64k
    struct iovec vec[2];

    const size_t writable = writableBytes();    //这是Buffer底层缓冲区剩余的可写空间大小
    vec[0].iov_base = begin() + writerIndex_;
    vec[0].iov_len = writable;

    vec[1].iov_base = extraBuf;
    vec[1].iov_len = sizeof extraBuf;

    const int iovcnt = (writable < sizeof extraBuf) ? 2 : 1;

    const ssize_t n = ::readv(fd, vec, iovcnt);

    if(n < 0){
        *savedErrno = errno;
    }else if(n <= writable){    // Buffer的可写缓冲区已经够存储读出来的数据了
        writerIndex_ += n;
    }else{       // extrabuf里面也写入了数据 

        writerIndex_ = buffer_.size();
        append(extraBuf, n - writable);     // writerIndex_ 开始写 n - writeable 长度
    }

}
ssize_t Buffer::writeFd(int fd, int* savedErrno){
    // 尝试将可读取的字节从文件描述符写入缓冲区
    ssize_t n = ::write(fd, peek(), readableBytes());
    if (n < 0)
    {
        // 记录错误号
        *savedErrno = errno;
    }
    return n;
}