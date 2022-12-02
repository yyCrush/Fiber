#ifndef __SYLAR_THREAD_H__
#define __SYLAR_THREAD_H__

#include <thread>
#include <functional>
#include <semaphore.h>
#include <atomic>
// #include "mutex.h"
//一般线程写少读多，但是std::thread不分读写锁
namespace sylar {

class Semaphore {
public:

    Semaphore(uint32_t count = 0);
    ~Semaphore();

    void wait();
    void notify();
private:
    sem_t m_semaphore;
};

template<class T>
struct ScopedLockImpl {
public:
    ScopedLockImpl(T& mutex)
        :m_mutex(mutex) {
        m_mutex.lock();
        m_locked = true;
    }
    ~ScopedLockImpl() {
        unlock();
    }
    void lock() {
        if(!m_locked) {
            m_mutex.lock();
            m_locked = true;
        }
    }
    void unlock() {
        if(m_locked) {
            m_mutex.unlock();
            //如果先释放锁，再设置bool，可能跳到某个抢到锁的线程把bool设成true，
            //然后再跳回来，把bool 设成false
            m_locked = false;
        }
    }
private:
    /// mutex
    T& m_mutex;
    /// 是否已上锁
    bool m_locked;
};

class Mutex {
public: 
    /// 局部锁
    typedef ScopedLockImpl<Mutex> Lock;
    Mutex() {
        pthread_mutex_init(&m_mutex, nullptr);
    }
    ~Mutex() {
        pthread_mutex_destroy(&m_mutex);
    }
    void lock() {
        pthread_mutex_lock(&m_mutex);
    }
    void unlock() {
        pthread_mutex_unlock(&m_mutex);
    }
private:
    /// mutex
    pthread_mutex_t m_mutex;
};

class  NullMutex {
public:

    typedef ScopedLockImpl<NullMutex> Lock;
    NullMutex() {}
    ~NullMutex() {}
    void lock() {}
    void unlock() {}
};

//局部读锁模板
template<class T>
struct ReadScopedLockImpl {
public:
    ReadScopedLockImpl(T& mutex)
        :m_mutex(mutex) {
        m_mutex.rdlock();
        m_locked = true;
    }
    ~ReadScopedLockImpl() {
        unlock();
    }
    void lock() {
        if(!m_locked) {
            m_mutex.rdlock();
            m_locked = true;
        }
    }
    void unlock() {
        if(m_locked) {
            m_mutex.unlock();
            m_locked = false;
        }
    }
private:
    /// mutex
    T& m_mutex;
    /// 是否已上锁
    bool m_locked;
};

//局部写锁模板

template<class T>
struct WriteScopedLockImpl {
public:
    WriteScopedLockImpl(T& mutex)
        :m_mutex(mutex) {
        m_mutex.wrlock();
        m_locked = true;
    }

    ~WriteScopedLockImpl() {
        unlock();
    }
    void lock() {
        if(!m_locked) {
            m_mutex.wrlock();
            m_locked = true;
        }
    }
    void unlock() {
        if(m_locked) {
            m_mutex.unlock();
            m_locked = false;
        }
    }
private:
    /// Mutex
    T& m_mutex;
    /// 是否已上锁
    bool m_locked;
};

class RWMutex {
public:
    /// 局部读锁
    typedef ReadScopedLockImpl<RWMutex> ReadLock;
    /// 局部写锁
    typedef WriteScopedLockImpl<RWMutex> WriteLock;
    RWMutex() {
        pthread_rwlock_init(&m_lock, nullptr);
    }
    ~RWMutex() {
        pthread_rwlock_destroy(&m_lock);
    }
    void rdlock() {
        pthread_rwlock_rdlock(&m_lock);
    }
    void wrlock() {
        pthread_rwlock_wrlock(&m_lock);
    }
    void unlock() {
        pthread_rwlock_unlock(&m_lock);
    }
private:
    /// 读写锁
    pthread_rwlock_t m_lock;
};

class NullRWMutex {
public:
    /// 局部读锁
    typedef ReadScopedLockImpl<NullMutex> ReadLock;
    /// 局部写锁
    typedef WriteScopedLockImpl<NullMutex> WriteLock;
    NullRWMutex() {}
    ~NullRWMutex() {}
    void rdlock() {}
    void wrlock() {}
    void unlock() {}
};

class Spinlock {
public:
    typedef ScopedLockImpl<Spinlock> Lock;
    Spinlock() {
        pthread_spin_init (&m_mutex, 0);
    }
    ~Spinlock() {
        pthread_spin_destroy(&m_mutex);
    }
    void lock() {
        pthread_spin_lock(&m_mutex);
    }
    void unlock() {
        pthread_spin_unlock(&m_mutex);
    }

private:
    pthread_spinlock_t m_mutex;
};

class CASLock {
public:
    CASLock() {

    }
    ~CASLock () {

    }
    void lock() {

    }
    void unlock() {

    }
};


class Thread {
public:
    /// 线程智能指针类型
    typedef std::shared_ptr<Thread> ptr;
    Thread(std::function<void()> cb, const std::string& name);
    ~Thread();
    pid_t getId() const { return m_id;}
    const std::string& getName() const { return m_name;}
    void join();
    static Thread* GetThis();

    static const std::string& GetName();

    static void SetName(const std::string& name);
private:

    static void* run(void* arg);
private:
    /// 线程id
    pid_t m_id = -1;
    /// 线程结构
    pthread_t m_thread = 0;
    /// 线程执行函数
    std::function<void()> m_cb;
    /// 线程名称
    std::string m_name;
    /// 信号量
    Semaphore m_semaphore;
};

}


#endif