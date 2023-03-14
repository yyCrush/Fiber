#include <iostream>
#include "../myfiber/log.h"
#include "../myfiber/util.h"
#include "boost/version.hpp"
#include "boost/config.hpp"

int main(int argc, char** argv) {
    myfiber::Logger::ptr logger(new myfiber::Logger);
    logger->addAppender(myfiber::LogAppender::ptr(new myfiber::StdoutLogAppender));

    myfiber::FileLogAppender::ptr file_appender(new myfiber::FileLogAppender("./log.txt"));
    myfiber::LogFormatter::ptr fmt(new myfiber::LogFormatter("%d%T%m%n"));
    file_appender->setFormatter(fmt);
    
    logger->addAppender(file_appender);

    // myfiber::LogEvent::ptr event(new myfiber::LogEvent(__FILE__, __LINE__,0,1,2,time(0)));

    // std::cout << "begin" << std::endl;
    // event->getSS() << "  " << "hello myfiber log"<<std::endl;

    // logger->log(myfiber::LogLevel::DEBUG,event);
    std::cout << "end" << std::endl;

    myfiber_LOG_INFO(logger) << "test"; //在析构的时候调用Loger的log输出函数
    myfiber_LOG_FMT_ERROR(logger,"asiodlfasi%s","aab");

    auto l = myfiber::LoggerMgr::GetInstance()->getLogger("xx");
    myfiber_LOG_INFO(l) << "xxx";
    return 0;
}


