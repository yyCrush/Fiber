#ifndef __myfiber_HTTP_WS_SERVER_H__
#define __myfiber_HTTP_WS_SERVER_H__

#include "myfiber/tcp_server.h"
#include "ws_session.h"
#include "ws_servlet.h"

namespace myfiber {
namespace http {

class WSServer : public TcpServer {
public:
    typedef std::shared_ptr<WSServer> ptr;

    WSServer(myfiber::IOManager* worker = myfiber::IOManager::GetThis()
             , myfiber::IOManager* io_worker = myfiber::IOManager::GetThis()
             , myfiber::IOManager* accept_worker = myfiber::IOManager::GetThis());

    WSServletDispatch::ptr getWSServletDispatch() const { return m_dispatch;}
    void setWSServletDispatch(WSServletDispatch::ptr v) { m_dispatch = v;}
protected:
    virtual void handleClient(Socket::ptr client) override;
protected:
    WSServletDispatch::ptr m_dispatch;
};

}
}

#endif
