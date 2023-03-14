#include "ws_servlet.h"

namespace myfiber {
namespace http {

FunctionWSServlet::FunctionWSServlet(callback cb
                                     ,on_connect_cb connect_cb
                                     ,on_close_cb close_cb)
    :WSServlet("FunctionWSServlet")
    ,m_callback(cb)
    ,m_onConnect(connect_cb)
    ,m_onClose(close_cb) {
}

int32_t FunctionWSServlet::onConnect(myfiber::http::HttpRequest::ptr header
                                     ,myfiber::http::WSSession::ptr session) {
    if(m_onConnect) {
        return m_onConnect(header, session);
    }
    return 0;
}

int32_t FunctionWSServlet::onClose(myfiber::http::HttpRequest::ptr header
                                     ,myfiber::http::WSSession::ptr session) {
    if(m_onClose) {
        return m_onClose(header, session);
    }
    return 0;
}

int32_t FunctionWSServlet::handle(myfiber::http::HttpRequest::ptr header
                                   ,myfiber::http::WSFrameMessage::ptr msg
                                   ,myfiber::http::WSSession::ptr session) {
    if(m_callback) {
        return m_callback(header, msg, session);
    }
    return 0;
}

WSServletDispatch::WSServletDispatch() {
    m_name = "WSServletDispatch";
}

void WSServletDispatch::addServlet(const std::string& uri
                    ,FunctionWSServlet::callback cb
                    ,FunctionWSServlet::on_connect_cb connect_cb
                    ,FunctionWSServlet::on_close_cb close_cb) {
    ServletDispatch::addServlet(uri, std::make_shared<FunctionWSServlet>(cb, connect_cb, close_cb));
}

void WSServletDispatch::addGlobServlet(const std::string& uri
                    ,FunctionWSServlet::callback cb
                    ,FunctionWSServlet::on_connect_cb connect_cb
                    ,FunctionWSServlet::on_close_cb close_cb) {
    ServletDispatch::addGlobServlet(uri, std::make_shared<FunctionWSServlet>(cb, connect_cb, close_cb));
}

WSServlet::ptr WSServletDispatch::getWSServlet(const std::string& uri) {
    auto slt = getMatchedServlet(uri);
    return std::dynamic_pointer_cast<WSServlet>(slt);
}

}
}
