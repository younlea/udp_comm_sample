#include "UdpComm.hpp"
#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

UdpComm::UdpComm(const std::string &local_ip, int receive_port, const std::string &remote_ip, int send_port)
    : local_ip_(local_ip), receive_port_(receive_port), remote_ip_(remote_ip), send_port_(send_port), sockfd_(-1) {
    sockfd_ = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd_ < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(local_ip.c_str());
    servaddr.sin_port = htons(receive_port);

    if (bind(sockfd_, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind failed");
        close(sockfd_);
        exit(EXIT_FAILURE);
    }

    recv_thread_ = std::thread(&UdpComm::receive_udp, this);
}

UdpComm::~UdpComm() {
    close(sockfd_);
    if (recv_thread_.joinable()) {
        recv_thread_.join();
    }
}

void UdpComm::set_receive_callback(std::function<void(const std::string &, const std::string &, const std::string &)> callback) {
    receive_callback_ = callback;
}

void UdpComm::send_data(const std::string &command, const std::string &data) {
    std::string trimmed_command = command.substr(0, 4);
    std::string message = trimmed_command + data;

    struct sockaddr_in destaddr;
    memset(&destaddr, 0, sizeof(destaddr));

    destaddr.sin_family = AF_INET;
    destaddr.sin_port = htons(send_port_);
    inet_pton(AF_INET, remote_ip_.c_str(), &destaddr.sin_addr);

    sendto(sockfd_, message.c_str(), message.size(), 0, (const struct sockaddr *)&destaddr, sizeof(destaddr));
}

void UdpComm::receive_udp() {
    char buffer[1024];
    struct sockaddr_in srcaddr;
    socklen_t len = sizeof(srcaddr);

    while (true) {
        int n = recvfrom(sockfd_, buffer, 1024, 0, (struct sockaddr *)&srcaddr, &len);
        buffer[n] = '\0';
        std::string command(buffer, 4);
        std::string data(buffer + 4, n - 4);
        char addr_str[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &srcaddr.sin_addr, addr_str, INET_ADDRSTRLEN);

        if (receive_callback_) {
            receive_callback_(command, data, addr_str);
        }
    }
}
