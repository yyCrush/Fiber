#include "myfiber/address.h"
#include "myfiber/log.h"

myfiber::Logger::ptr g_logger = myfiber_LOG_ROOT();

void test() {
    std::vector<myfiber::Address::ptr> addrs;

    myfiber_LOG_INFO(g_logger) << "begin";
    // bool v = myfiber::Address::Lookup(addrs, "localhost:3080");
    bool v = myfiber::Address::Lookup(addrs, "www.baidu.com", AF_INET);
    //bool v = myfiber::Address::Lookup(addrs, "www.myfiber.top", AF_INET);
    myfiber_LOG_INFO(g_logger) << "end";
    if(!v) {
        myfiber_LOG_ERROR(g_logger) << "lookup fail";
        return;
    }

    for(size_t i = 0; i < addrs.size(); ++i) {
        myfiber_LOG_INFO(g_logger) << i << " - " << addrs[i]->toString();
    }

    // auto addr = myfiber::Address::LookupAny("localhost:4080");
    // if(addr) {
    //     myfiber_LOG_INFO(g_logger) << *addr;
    // } else {
    //     myfiber_LOG_ERROR(g_logger) << "error";
    // }
}

void test_iface() {
    std::multimap<std::string, std::pair<myfiber::Address::ptr, uint32_t> > results;

    bool v = myfiber::Address::GetInterfaceAddresses(results);
    if(!v) {
        myfiber_LOG_ERROR(g_logger) << "GetInterfaceAddresses fail";
        return;
    }

    for(auto& i: results) {
        myfiber_LOG_INFO(g_logger) << i.first << " - " << i.second.first->toString() << " - "
            << i.second.second;
    }
}

void test_ipv4() {
    //auto addr = myfiber::IPAddress::Create("www.myfiber.top");
    auto addr = myfiber::IPAddress::Create("127.0.0.8");
    if(addr) {
        myfiber_LOG_INFO(g_logger) << addr->toString();
    }
}

int main(int argc, char** argv) {
    //test_ipv4();
    test_iface();
    // test();
    return 0;
}
