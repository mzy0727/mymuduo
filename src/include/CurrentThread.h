#pragma once

#include <unistd.h>
#include <sys/syscall.h>


extern __thread int t_cachedTid;
namespace CurrentThread{

    void cacheTid();

    inline int tid() {
        if(__builtin_expect(t_cachedTid == 0, 0)){
            cacheTid();
        }
        return t_cachedTid;
    }

};