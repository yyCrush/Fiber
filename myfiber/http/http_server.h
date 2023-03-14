/**
 * @file http_server.h
 * @brief HTTP服务器封装
 * @author myfiber.yin
 * @email 564628276@qq.com
 * @date 2019-06-09
 * @copyright Copyright (c) 2019年 myfiber.yin All rights reserved (www.myfiber.top)
 */

#ifndef __myfiber_HTTP_HTTP_SERVER_H__
#define __myfiber_HTTP_HTTP_SERVER_H__

#include "myfiber/tcp_server.h"
#include "http_session.h"
#include "servlet.h"

namespace myfiber {
namespace http {

/**
 * @brief HTTP服务器类
 */
class HttpServer : public TcpServer {
public:
    /// 智能指针类型
    typedef std::shared_ptr<HttpServer> ptr;

    /**
     * @brief 构造函数
     * @param[in] keepalive 是否长连接
     * @param[in] worker 工作调度器
     * @param[in] accept_worker 接收连接调度器
     */
    HttpServer(bool keepalive = false
               ,myfiber::IOManager* worker = myfiber::IOManager::GetThis()
               ,myfiber::IOManager* io_worker = myfiber::IOManager::GetThis()
               ,myfiber::IOManager* accept_worker = myfiber::IOManager::GetThis());

    /**
     * @brief 获取ServletDispatch
     */
    ServletDispatch::ptr getServletDispatch() const { return m_dispatch;}

    /**
     * @brief 设置ServletDispatch
     */
    void setServletDispatch(ServletDispatch::ptr v) { m_dispatch = v;}

    virtual void setName(const std::string& v) override;
protected:
    virtual void handleClient(Socket::ptr client) override;
private:
    /// 是否支持长连接
    bool m_isKeepalive;
    /// Servlet分发器
    ServletDispatch::ptr m_dispatch;
};

}
}

#endif
