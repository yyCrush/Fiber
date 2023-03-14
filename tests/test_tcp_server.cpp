#include "myfiber/tcp_server.h"
#include "myfiber/iomanager.h"
#include "myfiber/log.h"

myfiber::Logger::ptr g_logger = myfiber_LOG_ROOT();

void run() {
    auto addr = myfiber::Address::LookupAny("0.0.0.0:8033");
    //auto addr2 = myfiber::UnixAddress::ptr(new myfiber::UnixAddress("/tmp/unix_addr"));
    std::vector<myfiber::Address::ptr> addrs;
    addrs.push_back(addr);
    //addrs.push_back(addr2);

    myfiber::TcpServer::ptr tcp_server(new myfiber::TcpServer);
    std::vector<myfiber::Address::ptr> fails;
    while(!tcp_server->bind(addrs, fails)) {
        sleep(2);
    }
    tcp_server->start();
    
}
int main(int argc, char** argv) {
    myfiber::IOManager iom(2);
    iom.schedule(run);
    return 0;
}
