#include <iostream>
#include "player.h"

#define DELAY 20000
#define SERIAL_PORT "/dev/serial0"

int main() {
    Player player(DELAY, SERIAL_PORT);
    std::thread t1(serial_interface, std::ref(player));
    std::thread t2(show_leds, std::ref(player));
    t1.join();
    t2.join();
    return 0;
}
