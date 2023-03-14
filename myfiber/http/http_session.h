/**
 * @file http_session.h
 * @brief HTTPSession封装
 * @author myfiber.yin
 * @email 564628276@qq.com
 * @date 2019-06-07
 * @copyright Copyright (c) 2019年 myfiber.yin All rights reserved (www.myfiber.top)
 */

#ifndef __myfiber_HTTP_SESSION_H__
#define __myfiber_HTTP_SESSION_H__

#include "myfiber/socket_stream.h"
#include "http.h"

namespace myfiber {
namespace http {

/**
 * @brief HTTPSession封装
 */
class HttpSession : public SocketStream {
public:
    /// 智能指针类型定义
    typedef std::shared_ptr<HttpSession> ptr;

    /**
     * @brief 构造函数
     * @param[in] sock Socket类型
     * @param[in] owner 是否托管
     */
    HttpSession(Socket::ptr sock, bool owner = true);

    /**
     * @brief 接收HTTP请求
     */
    HttpRequest::ptr recvRequest();

    /**
     * @brief 发送HTTP响应
     * @param[in] rsp HTTP响应
     * @return >0 发送成功
     *         =0 对方关闭
     *         <0 Socket异常
     */
    int sendResponse(HttpResponse::ptr rsp);
};

}
}

#endif
