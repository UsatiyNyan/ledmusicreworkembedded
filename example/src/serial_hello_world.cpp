//
// Created by kira on 03.05.2020.
//
#include "serial.h"
#include <iostream>
#include <vector>

constexpr const char * serial_port  = "/dev/serial0";

int main() {
    serial::Connection connection(serial_port, 19200);
    std::vector<uint8_t> buf{3, 0};
    connection.read_exact(buf.data(), 3);
    std::cout << buf.data();
}
