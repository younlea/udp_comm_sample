#include "customudpcomm.hpp"
#include <iostream>
#include <arpa/inet.h>

void CustomUdpComm::on_receive(const std::string& command, const std::string& data, const sockaddr_in& addr) {
    std::cout << "Received message: Command=" << command << ", Data=" << data
              << ", From=" << inet_ntoa(addr.sin_addr) << ":" << ntohs(addr.sin_port) << std::endl;
}
