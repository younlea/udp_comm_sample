#include "CustomUdpComm.hpp"
#include <iostream>

CustomUdpComm::CustomUdpComm(const std::string &local_ip, int receive_port, const std::string &remote_ip, int send_port)
    : UdpComm(local_ip, receive_port, remote_ip, send_port) {
    set_receive_callback(std::bind(&CustomUdpComm::on_receive, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

void CustomUdpComm::on_receive(const std::string &command, const std::string &data, const std::string &addr) {
    std::cout << "Received message from " << addr << ": Command: " << command << ", Data: " << data << std::endl;
}
