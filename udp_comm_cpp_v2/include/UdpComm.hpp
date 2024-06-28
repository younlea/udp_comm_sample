#ifndef UDPCOMM_HPP
#define UDPCOMM_HPP

#include <string>
#include <functional>
#include <thread>

class UdpComm {
public:
    UdpComm(const std::string &local_ip, int receive_port, const std::string &remote_ip, int send_port);
    virtual ~UdpComm();

    void set_receive_callback(std::function<void(const std::string &, const std::string &, const std::string &)> callback);
    void send_data(const std::string &command, const std::string &data);

protected:
    void receive_udp();

    std::string local_ip_;
    int receive_port_;
    std::string remote_ip_;
    int send_port_;
    int sockfd_;
    std::function<void(const std::string &, const std::string &, const std::string &)> receive_callback_;
    std::thread recv_thread_;
};

#endif // UDPCOMM_HPP
