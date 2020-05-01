#ifndef __PLAYERH__
#define __PLAYERH__

#include "parser.h"
#include "base_exception.h"
#include "led.h"
#include "fixed_queue.h"

#include <thread>
#include <string>


namespace player {
class Player {
 public:
    Player(container::FixedQueue<clr::RGB> &rgb_queue, parser::Config &config);
    void run();
    void stop();
 private:
    void job();

    geometry::Circles _circles{};
    geometry::Polygons _polygons{};
    parser::Config &_cfg;
    container::FixedQueue<clr::RGB> &_rgb_queue;
    led::WS281X _ws281x;
    std::atomic<bool> _run = true;
    std::mutex _mutex;
};
}  // namespace player

#endif