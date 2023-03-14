#ifndef __myfiber_SCHEDULER_H__
#define __myfiber_SCHEDULER_H__

#include <memory>
#include <vector>
#include <list>
#include <iostream>
#include "fiber.h"
#include "thread.h"
#include "log.h"

namespace myfiber {

class Scheduler {
public:
    typedef std::shared_ptr<Scheduler> ptr;
    typedef Mutex MutexType;

    //threads线程数量   use_caller是否使用当前调用线程   name协程调度器名称
    Scheduler(size_t threads = 1, bool use_caller = true, const std::string& name = "");
    virtual ~Scheduler();
    //返回调度器名称
    const std::string& getName() const { return m_name;}
    //返回当前协程调度器
    static Scheduler* GetThis();
    //返回当前协程调度器的调度协程
    static Fiber* GetMainFiber();
    //启动协程调度器.创建执行run的多个线程
    void start();
    //停止协程调度器
    void stop();

    /**
     * @brief 调度协程
     * @param[in] fc 协程或函数
     * @param[in] thread 协程执行的线程id,-1标识任意线程
     */
    template<class FiberOrCb>
    void schedule(FiberOrCb fc, int thread = -1) {
        bool need_tickle = false;
        {
            MutexType::Lock lock(m_mutex);
            need_tickle = scheduleNoLock(fc, thread);
        }

        if(need_tickle) {
            tickle();
        }
    }

    /**
     * @brief 批量调度协程  好处是锁一次，可以全部放进去
     * @param[in] begin 协程数组的开始
     * @param[in] end 协程数组的结束
     */
    template<class InputIterator>
    void schedule(InputIterator begin, InputIterator end) {
        bool need_tickle = false;
        {
            MutexType::Lock lock(m_mutex);
            while(begin != end) {
                need_tickle = scheduleNoLock(&*begin, -1) || need_tickle;
                ++begin;
            }
        }
        if(need_tickle) {
            tickle();
        }
    }

    void switchTo(int thread = -1);
    std::ostream& dump(std::ostream& os);
protected:
    //通知协程调度器有任务了
    virtual void tickle();
    //协程调度函数
    void run();
    // 返回是否可以停止
    virtual bool stopping();
    // 协程无任务可调度时执行idle协程
    virtual void idle();
    //设置当前的协程调度器
    void setThis();
    //是否有空闲线程
    bool hasIdleThreads() { return m_idleThreadCount > 0;}
private:
    //协程调度启动(无锁)
    template<class FiberOrCb>
    bool scheduleNoLock(FiberOrCb fc, int thread) {
        bool need_tickle = m_fibers.empty();
        FiberAndThread ft(fc, thread);
        if(ft.fiber || ft.cb) {
            m_fibers.push_back(ft);
        }
        return need_tickle;
    }
private:
    //协程/函数/线程组
    struct FiberAndThread {
        /// 协程
        Fiber::ptr fiber;
        /// 协程执行函数
        std::function<void()> cb;
        /// 指定线程id执行当前任务
        int thread;
        //协程f 线程id
        FiberAndThread(Fiber::ptr f, int thr)
            :fiber(f), thread(thr) {
        }
        //f 协程指针 thr 线程id
        FiberAndThread(Fiber::ptr* f, int thr)
            :thread(thr) {
            fiber.swap(*f);
        }
        //f 协程执行函数 thr 线程id
        FiberAndThread(std::function<void()> f, int thr)
            :cb(f), thread(thr) {
        }
        //f 协程执行函数指针  thr 线程id
        FiberAndThread(std::function<void()>* f, int thr)
            :thread(thr) {
            cb.swap(*f);
        }
        FiberAndThread()
            :thread(-1) {
        }
        //重置数据
        void reset() {
            fiber = nullptr;
            cb = nullptr;
            thread = -1;
        }
    };
private:
    /// Mutex
    MutexType m_mutex;
    /// 线程池
    std::vector<Thread::ptr> m_threads;
    /// 待执行的协程队列
    std::list<FiberAndThread> m_fibers;
    /// use_caller为true时有效, 调度协程
    Fiber::ptr m_rootFiber;
    /// 协程调度器名称
    std::string m_name;
protected:
    /// 协程下的线程id数组
    std::vector<int> m_threadIds;
    /// 线程数量
    size_t m_threadCount = 0;
    /// 工作线程数量
    std::atomic<size_t> m_activeThreadCount = {0};
    /// 空闲线程数量
    std::atomic<size_t> m_idleThreadCount = {0};
    /// 是否正在停止
    bool m_stopping = true;
    /// 是否自动停止
    bool m_autoStop = false;
    /// 主线程id(use_caller)
    int m_rootThread = 0;
};

class SchedulerSwitcher {
public:
    SchedulerSwitcher(Scheduler* target = nullptr);
    ~SchedulerSwitcher();
private:
    Scheduler* m_caller;
};

}

#endif
