#ifndef CUSTOMUDPCOMM_HPP
#define CUSTOMUDPCOMM_HPP

#include "udpcomm.hpp"

class CustomUdpComm : public UdpComm {
public:
    CustomUdpComm(const std::string& local_ip, int local_port, const std::string& remote_ip, int remote_port)
        : UdpComm(local_ip, local_port, remote_ip, remote_port) {}

protected:
    void on_receive(const std::string& command, const std::string& data, const sockaddr_in& addr) override;
};

#endif // CUSTOMUDPCOMM_HPP
