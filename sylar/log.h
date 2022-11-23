#ifndef __SYLAR_LOG_H__
#define __SYLAR_LOG_H__

#include <string>
#include <memory>
#include <list>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include "util.h"
#include "singleton.h"
// #include <stdint.h>

#define SYLAR_LOG_LEVEL(loger,level) \
    if(logger->getLevel() <= level) \
        sylar::LogEventWrap(sylar::LogEvent::ptr(new sylar::LogEvent(logger, level, \
        __FILE__,__LINE__, 0, sylar::GetThreadId(), sylar::GetFiberId(), time(0)))).getSS()

#define SYLAR_LOG_DEBUG(logger) SYLAR_LOG_LEVEL(logger, sylar::LogLevel::DEBG)
#define SYLAR_LOG_INFO(logger) SYLAR_LOG_LEVEL(logger, sylar::LogLevel::INFO)
#define SYLAR_LOG_WARN(logger) SYLAR_LOG_LEVEL(logger, sylar::LogLevel::WARN)
#define SYLAR_LOG_ERROR(logger) SYLAR_LOG_LEVEL(logger, sylar::LogLevel::ERROR)
#define SYLAR_LOG_FATAL(logger) SYLAR_LOG_LEVEL(logger, sylar::LogLevel::FATAL)

#define SYLAR_LOG_FMT_LEVEL(logger, level, fmt, ...) \
    if(logger->getLevel() <= level) \
        sylar::LogEventWrap(sylar::LogEvent::ptr(new sylar::LogEvent(logger, level, \
                        __FILE__, __LINE__, 0, sylar::GetThreadId(),\
                sylar::GetFiberId(), time(0)))).getEvent()->format(fmt, __VA_ARGS__)

#define SYLAR_LOG_FMT_DEBUG(logger, fmt, ...) SYLAR_LOG_FMT_LEVEL(logger, sylar::LogLevel::DEBUG, fmt, __VA_ARGS__)
#define SYLAR_LOG_FMT_INFO(logger, fmt, ...)  SYLAR_LOG_FMT_LEVEL(logger, sylar::LogLevel::INFO, fmt, __VA_ARGS__)
#define SYLAR_LOG_FMT_WARN(logger, fmt, ...)  SYLAR_LOG_FMT_LEVEL(logger, sylar::LogLevel::WARN, fmt, __VA_ARGS__)
#define SYLAR_LOG_FMT_ERROR(logger, fmt, ...) SYLAR_LOG_FMT_LEVEL(logger, sylar::LogLevel::ERROR, fmt, __VA_ARGS__)
#define SYLAR_LOG_FMT_FATAL(logger, fmt, ...) SYLAR_LOG_FMT_LEVEL(logger, sylar::LogLevel::FATAL, fmt, __VA_ARGS__)
#define SYLAR_LOG_ROOT() sylar::LoggerMgr::GetInstance()->getRoot()
#define SYLAR_LOG_NAME(name) sylar::LoggerMgr::GetInstance()->getLogger(name)



namespace sylar{

class Logger;

class LogLevel {
public:
    enum Level {
        UNKNOW = 0,
        DEBUG = 1,
        INFO = 2,
        WARN = 3,
        ERROR = 4,
        FATAL = 5
    };
    static const char* ToString(LogLevel::Level level);
};


class LogEvent {
public:
typedef std::shared_ptr<LogEvent> ptr;
    LogEvent(std::shared_ptr<Logger> logger, LogLevel::Level level, const char* file, int32_t line, uint32_t elapse
        ,uint32_t thread_id, uint32_t fiber_id, uint64_t time);
    ~LogEvent();

    const char* getFile() const { return m_file;}
    int32_t getLine() const { return m_line;}
    uint32_t getElapse() const { return m_elapse;}

    uint32_t getThreadId() const { return m_threadId;}

    uint32_t getFiberId() const { return m_fiberId;}

    uint64_t getTime() const { return m_time;}

    std::string getContent() const { return m_ss.str();}


    std::shared_ptr<Logger> getLogger() const { return m_logger;}

    LogLevel::Level getLevel() const { return m_level;}

    std::stringstream& getSS() { return m_ss;}
    void format(const char* fmt, ...);

    void format(const char* fmt, va_list al);

private:
    const char* m_file = nullptr;
    int32_t m_line = 0;
    uint32_t m_elapse = 0;
    uint32_t m_threadId = 0;
    uint32_t m_fiberId = 0;
    uint64_t m_time = 0;
    // std::stringstream m_ss;
    std::shared_ptr<Logger> m_logger;
    LogLevel::Level m_level;
    std::stringstream m_ss;
};

class LogEventWrap {
public:

    LogEventWrap(LogEvent::ptr e);
    ~LogEventWrap();

    LogEvent::ptr getEvent() const { return m_event;}

    std::stringstream& getSS();
private:
    LogEvent::ptr m_event;
};




//日志格式器
class LogFormatter {
public:
    typedef std::shared_ptr<LogFormatter> ptr;
    LogFormatter(const std::string& pattern);
    std::string format(std::shared_ptr<Logger> logger,LogLevel::Level level,LogEvent::ptr event);

    class FormatItem {
        public:
        typedef std::shared_ptr<FormatItem> ptr;
        virtual ~FormatItem(){}
        virtual void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level , LogEvent::ptr event) = 0;
    };

    void init();

    bool isError() const { return m_error;}
    const std::string getPattern () const { return m_pattern;}
private:
    std::string m_pattern;   //"%d [%p] <%f:%l>    %m %n"
    std::vector<FormatItem::ptr> m_items;
    bool m_error = false;
};

//日志输出地
class LogAppender {
public:
    typedef std::shared_ptr<LogAppender> ptr;
    virtual ~LogAppender(){}

    virtual void log(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) = 0 ;

    void setFormatter (LogFormatter::ptr val) { m_formatter = val;}
    LogFormatter::ptr getFormatter() const { return m_formatter;}
protected:
    LogLevel::Level m_level = LogLevel::DEBUG;
    LogFormatter::ptr m_formatter;
};

//日志器
class Logger : public std::enable_shared_from_this<Logger> {
public:
    typedef std::shared_ptr<Logger> ptr;

    Logger (const std::string& name = "root");
    void log (LogLevel::Level level, const LogEvent::ptr event);

    void debug (LogEvent::ptr event);
    void info (LogEvent::ptr event);
    void warn (LogEvent::ptr event);
    void error (LogEvent::ptr event);
    void fatal (LogEvent::ptr event);

    void addAppender (LogAppender::ptr appender);
    void delAppender (LogAppender::ptr appender);
    LogLevel::Level getLevel () const { return m_level;}
    void setLevel(LogLevel::Level val ){ m_level = val;}

    const std::string& getName() const { return m_name;}

private:
    std::string m_name;                 //默认 root
    LogLevel::Level m_level;            //默认   m_level(LogLevel::DEBUG)
    std::list<LogAppender::ptr> m_appenders;
    LogFormatter::ptr m_formatter;      //在logger初始化时赋值  new LogFormatter("%d [%p] <%f:%l>    %m %n") Init初始化 std::vector<FormatItem::ptr> m_items;
};

//输出到控制台的Appender
class StdoutLogAppender : public LogAppender {
public:
    typedef std::shared_ptr<StdoutLogAppender> ptr;
    void log(std::shared_ptr<Logger> logger,LogLevel::Level level, LogEvent::ptr event) override;
private:

};

//定义输出到文件的appender
class FileLogAppender : public LogAppender {
public:
    typedef std::shared_ptr<FileLogAppender> ptr;
    FileLogAppender(const std::string& filename);
    void log(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override;

    bool reopen();
private:
    std::string m_filename;
    std::ofstream m_filestream;
};

class LoggerManager {
public:
    /**
     * @brief 构造函数
     */
    LoggerManager();
    /**
     * @brief 获取日志器
     * @param[in] name 日志器名称
     */
    Logger::ptr getLogger(const std::string& name);
    /**
     * @brief 返回主日志器
     */
    Logger::ptr getRoot() const { return m_root;}
    /**
     * @brief 将所有的日志器配置转成YAML String
     */
    std::string toYamlString();
private:
    /// 日志器容器
    std::map<std::string, Logger::ptr> m_loggers;
    Logger::ptr m_root;
};

typedef sylar::Singleton<LoggerManager> LoggerMgr;

}
#endif
