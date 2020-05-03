//
// Created by kira on 03.05.2020.
//
#include "serial.h"
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;


constexpr const char * serial_port  = "/dev/serial0";

int main() {
    serial::Connection connection(serial_port, 19200);
    std::vector<uint8_t> buf{128, 0};
    while (true) {
        std::cout << connection.read(buf.data(), 5) << std::endl;
        std::cout <<
            "c: " << static_cast<int>(buf[0]) << " | "
            "f: " << static_cast<int>(buf[1]) << " | "
            "r: " << static_cast<int>(buf[2]) << " | "
            "g: " << static_cast<int>(buf[3]) << " | "
            "b: " << static_cast<int>(buf[4]) << std::endl;
        connection.write(buf.data(), 2);
        std::this_thread::sleep_for(40ms);
    }
}
