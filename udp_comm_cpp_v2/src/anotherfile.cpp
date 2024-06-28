#include "CustomUdpComm.hpp"
#include <iostream>

extern CustomUdpComm *udp_comm;

void some_function() {
    std::string command = "TEST";
    std::string data = "Data from another_file.cpp";
    udp_comm->send_data(command, data);
}

int main() {
    // Make sure to initialize udp_comm in main.cpp before calling this function
    some_function();
    return 0;
}
