#include "myfiber/myfiber.h"
#include "myfiber/iomanager.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <sys/epoll.h>

myfiber::Logger::ptr g_logger = myfiber_LOG_ROOT();

int sock = 0;

void test_fiber() {
    myfiber_LOG_INFO(g_logger) << "test_fiber sock=" << sock;

    //sleep(3);

    //close(sock);
    //myfiber::IOManager::GetThis()->cancelAll(sock);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    fcntl(sock, F_SETFL, O_NONBLOCK);

    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
    inet_pton(AF_INET, "110.242.68.3", &addr.sin_addr.s_addr);

    if(!connect(sock, (const sockaddr*)&addr, sizeof(addr))) {
    } else if(errno == EINPROGRESS) {
        myfiber_LOG_INFO(g_logger) << "add event errno=" << errno << " " << strerror(errno);
        myfiber::IOManager::GetThis()->addEvent(sock, myfiber::IOManager::READ, [](){
            myfiber_LOG_INFO(g_logger) << "read callback";
        });
        myfiber::IOManager::GetThis()->addEvent(sock, myfiber::IOManager::WRITE, [](){
            myfiber_LOG_INFO(g_logger) << "write callback";
            //close(sock);
            myfiber::IOManager::GetThis()->cancelEvent(sock, myfiber::IOManager::READ);
            close(sock);
        });
    } else {
        myfiber_LOG_INFO(g_logger) << "else " << errno << " " << strerror(errno);
    }

}

void test1() {
    std::cout << "EPOLLIN=" << EPOLLIN
              << " EPOLLOUT=" << EPOLLOUT << std::endl;
    myfiber::IOManager iom(2, false);
    iom.schedule(&test_fiber);
}

myfiber::Timer::ptr s_timer;
void test_timer() {
    myfiber::IOManager iom(4, true);
    // s_timer = iom.addTimer(1000, [](){
    //     static int i = 0;
    //     myfiber_LOG_INFO(g_logger) << "hello timer i=" << i;
    //     if(++i == 3) {
    //         //s_timer->reset(2000, true);
    //         s_timer->cancel();
    //     }
    // }, true);

    iom.addTimer(1000, [](){
        static int i = 0;
        myfiber_LOG_INFO(g_logger) << "hello timer i=" << i;
    }, false);
}


int main(int argc, char** argv) {
    //  test1();
    test_timer();
    return 0;
}
