#include "fixed_queue.h"
#include "serial.h"
#include "parser.h"
#include "led.h"
#include "player.h"
#include <iostream>


int main() {
    parser::Config cfg;
    container::FixedQueue<clr::RGB> rgb_queue(cfg.get_2d_objs_amount());
    player::Player led_player(rgb_queue, cfg);
    led_player.run();


    parser::Parser reader(rgb_queue, cfg);
    reader.run();
    std::this_thread::sleep_for(1000s);
    return 0;
}
