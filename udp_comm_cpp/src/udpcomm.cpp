#include "udpcomm.hpp"
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

UdpComm::UdpComm(const std::string& local_ip, int local_port, const std::string& remote_ip, int remote_port)
    : local_ip_(local_ip), local_port_(local_port), remote_ip_(remote_ip), remote_port_(remote_port), sockfd_(-1) {
    sockfd_ = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd_ < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&local_addr_, 0, sizeof(local_addr_));
    memset(&remote_addr_, 0, sizeof(remote_addr_));

    local_addr_.sin_family = AF_INET;
    local_addr_.sin_addr.s_addr = inet_addr(local_ip.c_str());
    local_addr_.sin_port = htons(local_port);

    remote_addr_.sin_family = AF_INET;
    remote_addr_.sin_addr.s_addr = inet_addr(remote_ip.c_str());
    remote_addr_.sin_port = htons(remote_port);

    if (bind(sockfd_, (const struct sockaddr *)&local_addr_, sizeof(local_addr_)) < 0) {
        perror("bind failed");
        close(sockfd_);
        exit(EXIT_FAILURE);
    }

    receive_thread_ = std::thread(&UdpComm::receive_udp, this);
}

UdpComm::~UdpComm() {
    if (sockfd_ >= 0) {
        close(sockfd_);
    }
    if (receive_thread_.joinable()) {
        receive_thread_.join();
    }
}

void UdpComm::send_data(const std::string& command, const std::string& data) {
    if (command.length() > 4) {
        std::cerr << "Command is longer than 4 characters. Trimming to 4 characters." << std::endl;
    }
    std::string cmd = command.substr(0, 4);
    std::string message = cmd + data;

    std::lock_guard<std::mutex> lock(socket_mutex_);
    sendto(sockfd_, message.c_str(), message.length(), 0, (const struct sockaddr *)&remote_addr_, sizeof(remote_addr_));
}

void UdpComm::set_receive_callback(ReceiveCallback callback) {
    receive_callback_ = callback;
}

void UdpComm::receive_udp() {
    char buffer[1024];
    sockaddr_in sender_addr;
    socklen_t sender_addr_len = sizeof(sender_addr);

    while (true) {
        int len = recvfrom(sockfd_, buffer, sizeof(buffer), 0, (struct sockaddr *)&sender_addr, &sender_addr_len);
        if (len > 0) {
            buffer[len] = '\0';
            std::string message(buffer);
            std::string command = message.substr(0, 4);
            std::string data = message.substr(4);

            if (receive_callback_) {
                receive_callback_(command, data, sender_addr);
            } else {
                on_receive(command, data, sender_addr);
            }
        }
    }
}
