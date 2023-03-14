#ifndef __myfiberY_NONCOPYABLE_H__
#define __myfiberY_NONCOPYABLE_H__

namespace myfiber{

class Noncopyable {
public:
    Noncopyable() = default;
    ~Noncopyable() = default; 
    Noncopyable(const Noncopyable& ) = delete;
    Noncopyable &operator = (const Noncopyable&) = delete;
};

}

#endif