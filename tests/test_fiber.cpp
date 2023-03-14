#include "myfiber/myfiber.h"

myfiber::Logger::ptr g_logger = myfiber_LOG_ROOT();


void run_in_fiber() {
    myfiber_LOG_INFO(g_logger) << "run_in_fiber begin";
    myfiber::Fiber::YieldToHold();
    myfiber_LOG_INFO(g_logger) << "run_in_fiber end";
    myfiber::Fiber::YieldToHold();
}

void test_fiber() {
    {
    g_logger->setLevel(myfiber::LogLevel::ERROR);
    myfiber::Fiber::GetThis();
    myfiber_LOG_INFO(g_logger) << "main begin";
    myfiber::Fiber::ptr fiber(new myfiber::Fiber(run_in_fiber));
    fiber->swapIn();
    myfiber_LOG_INFO(g_logger) << "main after swapIn";
    fiber->swapIn();
    myfiber_LOG_INFO(g_logger) << "main after end";
    }
    myfiber_LOG_INFO(g_logger) << "main after end2";
}

int main(int argc, char** argv) {
    myfiber::Thread::SetName("main");
    std::vector<myfiber::Thread::ptr> thrs;
    for(int i = 0; i < 3; ++i) {
        thrs.push_back(myfiber::Thread::ptr(
                    new myfiber::Thread(&test_fiber, "name_" + std::to_string(i))));
    }
    for(auto i : thrs) {
        i->join();
    }
    return 0;
}
