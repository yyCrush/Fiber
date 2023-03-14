#include "myfiber/myfiber.h"

static myfiber::Logger::ptr g_logger = myfiber_LOG_ROOT();

void test_fiber() {
    static int s_count = 5;
    myfiber_LOG_INFO(g_logger) << "test in fiber s_count=" << s_count;

    sleep(1);
    if(--s_count >= 0) {
        myfiber::Scheduler::GetThis()->schedule(&test_fiber);
    }
}

int main(int argc, char** argv) {
    myfiber_LOG_INFO(g_logger) << "main";
    myfiber::Scheduler sc(3, false, "test");
    sc.start();
    sleep(2);
    myfiber_LOG_INFO(g_logger) << "schedule";
    sc.schedule(&test_fiber);
    sc.stop();
    myfiber_LOG_INFO(g_logger) << "over";
    return 0;
}
