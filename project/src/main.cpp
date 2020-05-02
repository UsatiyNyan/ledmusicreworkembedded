#include "fixed_queue.h"
#include "serial.h"
#include "parser.h"
#include "led.h"
#include "player.h"
#include <iostream>

constexpr size_t baud = 19200;
constexpr const char * serial_port  = "/dev/serial0";

int main() {
    parser::Config cfg;
    container::FixedQueue<clr::RGB> rgb_queue(cfg.get_2d_objs_amount());
    for (size_t i = 0; i < 1000; ++i) {
        rgb_queue.push_back(clr::RGB{
           static_cast<uint8_t>(i),
           static_cast<uint8_t>(i),
           static_cast<uint8_t>(i)});
//        std::cout
//            << static_cast<int>(rgb_queue[i].r) << ' '
//            << static_cast<int>(rgb_queue[i].g) << ' '
//            << static_cast<int>(rgb_queue[i].b) << std::endl;
    }
    for (size_t i = 0; i < rgb_queue.size(); ++i) {
        std::cout
            << static_cast<int>(rgb_queue[i].r) << ' '
            << static_cast<int>(rgb_queue[i].g) << ' '
            << static_cast<int>(rgb_queue[i].b) << std::endl;
    }
//    player::Player led_player(rgb_queue, cfg);
//    led_player.run();
//     run parser thread
//    serial::Connection connection(serial_port, baud);
//    parser::Parser reader(std::move(connection), cfg);


    return 0;
}
