#ifndef UDPCOMM_HPP
#define UDPCOMM_HPP

#include <iostream>
#include <string>
#include <functional>
#include <thread>
#include <mutex>
#include <netinet/in.h>

class UdpComm {
public:
    using ReceiveCallback = std::function<void(const std::string&, const std::string&, const sockaddr_in&)>;

    UdpComm(const std::string& local_ip, int local_port, const std::string& remote_ip, int remote_port);
    virtual ~UdpComm();

    void send_data(const std::string& command, const std::string& data);
    void set_receive_callback(ReceiveCallback callback);

protected:
    virtual void on_receive(const std::string& command, const std::string& data, const sockaddr_in& addr) = 0;

private:
    void receive_udp();

    std::string local_ip_;
    int local_port_;
    std::string remote_ip_;
    int remote_port_;
    int sockfd_;
    sockaddr_in local_addr_;
    sockaddr_in remote_addr_;

    std::thread receive_thread_;
    std::mutex socket_mutex_;
    ReceiveCallback receive_callback_;
};

#endif // UDPCOMM_HPP
