#include "CurrentThread.h"

__thread int t_cachedTid = 0;

namespace CurrentThread{
    void CurrentThread::cacheTid() {
        if(t_cachedTid == 0){
            // 通过linux系统调用，获取当前线程的tid值
            t_cachedTid = static_cast<pid_t>(::syscall(SYS_gettid));
        }
    }

}