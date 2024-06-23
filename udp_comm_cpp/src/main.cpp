#include "customudpcomm.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <arpa/inet.h>

void handle_receive(const std::string& command, const std::string& data, const sockaddr_in& addr) {
    std::cout << "Received message: Command=" << command << ", Data=" << data
              << ", From=" << inet_ntoa(addr.sin_addr) << ":" << ntohs(addr.sin_port) << std::endl;
}

void daemon_thread(CustomUdpComm& udp_comm) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    CustomUdpComm udp_comm("0.0.0.0", 5002, "127.0.0.1", 5003);
    udp_comm.set_receive_callback(handle_receive);

    std::thread daemon(daemon_thread, std::ref(udp_comm));

    std::string command;
    std::string data;
    while (true) {
        std::cout << "Enter command: ";
        std::getline(std::cin, command);
        std::cout << "Enter data: ";
        std::getline(std::cin, data);
        udp_comm.send_data(command, data);
    }

    if (daemon.joinable()) {
        daemon.join();
    }

    return 0;
}
