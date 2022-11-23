#include <iostream>
#include "../sylar/log.h"
#include "../sylar/util.h"
#include "boost/version.hpp"
#include "boost/config.hpp"

int main(int argc, char** argv) {
    sylar::Logger::ptr logger(new sylar::Logger);
    logger->addAppender(sylar::LogAppender::ptr(new sylar::StdoutLogAppender));

    sylar::FileLogAppender::ptr file_appender(new sylar::FileLogAppender("./log.txt"));
    sylar::LogFormatter::ptr fmt(new sylar::LogFormatter("%d%T%m%n"));
    file_appender->setFormatter(fmt);
    
    logger->addAppender(file_appender);

    // sylar::LogEvent::ptr event(new sylar::LogEvent(__FILE__, __LINE__,0,1,2,time(0)));

    // std::cout << "begin" << std::endl;
    // event->getSS() << "  " << "hello sylar log"<<std::endl;

    // logger->log(sylar::LogLevel::DEBUG,event);
    std::cout << "end" << std::endl;

    SYLAR_LOG_INFO(logger) << "test"; //在析构的时候调用Loger的log输出函数
    SYLAR_LOG_FMT_ERROR(logger,"asiodlfasi%s","aab");

    auto l = sylar::LoggerMgr::GetInstance()->getLogger("xx");
    SYLAR_LOG_INFO(l) << "xxx";
    return 0;
}


