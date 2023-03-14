#include "myfiber/myfiber.h"
#include <assert.h>

myfiber::Logger::ptr g_logger = myfiber_LOG_ROOT();

void test_assert() {
    myfiber_LOG_INFO(g_logger) << myfiber::BacktraceToString(10);
    // assert(0,"hello");
    myfiber_ASSERT2(0 ==1, "abcdef xx");
}

int main()
{
    test_assert();
    return 0;
}