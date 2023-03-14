#include "myfiber/hook.h"
#include "myfiber/log.h"
#include "myfiber/iomanager.h"
#include "sys/types.h"
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

myfiber::Logger::ptr g_logger = myfiber_LOG_ROOT();

void test_sleep() {
    myfiber::IOManager iom(1);
    iom.schedule([](){
        sleep(2);
        myfiber_LOG_INFO(g_logger) << "sleep 2";
    });

    iom.schedule([](){
        sleep(3);
        myfiber_LOG_INFO(g_logger) << "sleep 3";
    });
    myfiber_LOG_INFO(g_logger) << "test_sleep";
}

void test_sock() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
    inet_pton(AF_INET, "110.242.68.66", &addr.sin_addr.s_addr);

    myfiber_LOG_INFO(g_logger) << "begin connect";
    int rt = connect(sock, (const sockaddr*)&addr, sizeof(addr));
    myfiber_LOG_INFO(g_logger) << "connect rt=" << rt << " errno=" << errno;

    if(rt) {
        return;
    }

    const char data[] = "GET / HTTP/1.0\r\n\r\n";
    rt = send(sock, data, sizeof(data), 0);
    myfiber_LOG_INFO(g_logger) << "send rt=" << rt << " errno=" << errno;

    if(rt <= 0) {
        return;
    }

    std::string buff;
    buff.resize(4096);

    rt = recv(sock, &buff[0], buff.size(), 0);
    myfiber_LOG_INFO(g_logger) << "recv rt=" << rt << " errno=" << errno;

    if(rt <= 0) {
        return;
    }

    buff.resize(rt);
    myfiber_LOG_INFO(g_logger) << buff;
}

int main(int argc, char** argv) {
    // test_sleep();
    myfiber::IOManager iom;
    iom.schedule(test_sock);
    // test_sock();
    return 0;
}