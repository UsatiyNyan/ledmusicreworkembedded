//
// Created by kira on 03.05.2020.
//
#include "serial.h"
#include <iostream>
#include <vector>

constexpr const char * serial_port  = "/dev/serial0";

int main() {
    serial::Connection connection(serial_port, 19200);
    std::vector<uint8_t> buf{};
    std::cout << connection.read(buf.data(), 3) << std::endl;
    std::cout << buf.data();
}