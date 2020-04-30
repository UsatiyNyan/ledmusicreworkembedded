#include "fixed_queue.h"
#include "serial.h"
#include "parser.h"
#include "led.h"
#include <iostream>
#include <base_exception.h>

constexpr size_t delay = 20000;
constexpr size_t baud = 19200;
constexpr const char * serial_port  = "/dev/serial0";

int main() {
    parser::Config cfg;
    container::FixedQueue<clr::RGB> rgb(10);  // TODO: safe fixed queue
    // run parser thread
    // initialize Player?? or smth with Circles and Polygons
    {
        serial::Connection connection(serial_port, baud);
        parser::Parser reader(std::move(connection), cfg);
//        while (true) {
            rgb.push_back(reader.get_rgb());
//            reader.start_parsing();
//        }
    }
    Circles circles;
    Polygons polygons;
    led::WS281X ws281x(8, 32);
    // run player::thread
    return 0;
}
