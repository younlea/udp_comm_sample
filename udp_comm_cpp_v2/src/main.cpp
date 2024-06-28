#include "CustomUdpComm.hpp"
#include <iostream>

extern CustomUdpComm *udp_comm;

int main() {
    std::string local_ip = "0.0.0.0";
    std::string remote_ip = "192.168.1.41";
    int receive_port = 5003;
    int send_port = 5002;

    udp_comm = new CustomUdpComm(local_ip, receive_port, remote_ip, send_port);

    while (true) {
        std::string command;
        std::string data;
        std::cout << "Enter command (4 characters): ";
        std::cin >> command;
        std::cout << "Enter data: ";
        std::cin >> data;
        udp_comm->send_data(command, data);
    }

    delete udp_comm;
    return 0;
}
