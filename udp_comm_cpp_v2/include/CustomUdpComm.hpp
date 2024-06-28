#ifndef CUSTOMUDPCOMM_HPP
#define CUSTOMUDPCOMM_HPP

#include "UdpComm.hpp"

class CustomUdpComm : public UdpComm {
public:
    CustomUdpComm(const std::string &local_ip, int receive_port, const std::string &remote_ip, int send_port);
    void on_receive(const std::string &command, const std::string &data, const std::string &addr);
};

#endif // CUSTOMUDPCOMM_HPP
