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
    container::FixedQueue<clr::RGB> rgb_queue(10);

    player::Player led_player(rgb_queue, cfg);
    led_player.run();
    // run parser thread
    serial::Connection connection(serial_port, baud);
    parser::Parser reader(std::move(connection), cfg);


    return 0;
}
