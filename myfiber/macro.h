#ifndef __myfiber_MACRO_H__
#define __myfiber_MACRO_H__

#include <string.h>
#include <assert.h>
#include "util.h"


#if defined __GNUC__ || defined __llvm__
#   define myfiber_LIKELY(x)        __builtin_expect(!!(x), 1)
#   define myfiber_UNLIKELY(x)      __builtin_expect(!!(x), 0) 
#else
#   define myfiber_LIKELY(x)      (x)
#   define myfiber_UNLIKELY(x)      (x)
#endif
/// 断言宏封装
#define myfiber_ASSERT(x) \
    if(myfiber_UNLIKELY(!(x))) { \
        myfiber_LOG_ERROR(myfiber_LOG_ROOT()) << "ASSERTION: " #x \
            << "\nbacktrace:\n" \
            << myfiber::BacktraceToString(100, 2, "    "); \
        assert(x); \
    }

/// 断言宏封装
#define myfiber_ASSERT2(x, w) \
    if(myfiber_UNLIKELY(!(x))) { \
        myfiber_LOG_ERROR(myfiber_LOG_ROOT()) << "ASSERTION: " #x \
            << "\n" << w \
            << "\nbacktrace:\n" \
            << myfiber::BacktraceToString(100, 2, "    "); \
        assert(x); \
    }


#endif
