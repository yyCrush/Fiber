#include "myfiber/myfiber.h"
#include <unistd.h>

myfiber::Logger::ptr g_logger = myfiber_LOG_ROOT();

int count = 0;
// myfiber::RWMutex s_mutex;
myfiber::Mutex s_mutex;

void fun1() {
    myfiber_LOG_INFO(g_logger) << "name: " << myfiber::Thread::GetName()
                            << " this.name: " << myfiber::Thread::GetThis()->getName()
                            << " id: " << myfiber::GetThreadId()
                            << " this.id: " << myfiber::Thread::GetThis()->getId();

    for(int i = 0; i < 100000; ++i) {
        myfiber::Mutex::Lock lock(s_mutex);
        // myfiber::RWMutex::WriteLock lock(s_mutex);
        ++count;
    }
}

void fun2() {
    while(true) {
        myfiber_LOG_INFO(g_logger) << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
    }
}

void fun3() {
    while(true) {
        myfiber_LOG_INFO(g_logger) << "========================================";
    }
}

int main(int argc, char** argv) {
    myfiber_LOG_INFO(g_logger) << "thread test begin";
    YAML::Node root = YAML::LoadFile("/home/zyy/workspace/myfiber/bin/conf/log2.yml");
    myfiber::Config::LoadFromYaml(root);
    
    std::vector<myfiber::Thread::ptr> thrs;
    for(int i = 0; i < 5; ++i) {
        myfiber::Thread::ptr thr(new myfiber::Thread(&fun2, "name_" + std::to_string(i * 2)));
        myfiber::Thread::ptr thr2(new myfiber::Thread(&fun3, "name_" + std::to_string(i * 2 + 1)));
        thrs.push_back(thr);
        thrs.push_back(thr2);
    }

    for(size_t i = 0; i < thrs.size(); ++i) {
        thrs[i]->join();
    }
    myfiber_LOG_INFO(g_logger) << "thread test end";
    myfiber_LOG_INFO(g_logger) << "count=" << count;
    

    
    return 0;
}


