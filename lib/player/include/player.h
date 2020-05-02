#ifndef __PLAYERH__
#define __PLAYERH__

#include "parser.h"
#include "base_exception.h"
#include "led.h"
#include "fixed_queue.h"
#include "job_thread.h"

#include <thread>
#include <string>

namespace loop {
class Player : public executor::JobThread {
 public:
    Player(container::FixedQueue<clr::RGB> &rgb_queue, parser::Config &config);
 private:
    void job() override;

    geometry::Circles _circles;
    geometry::Polygons _polygons;
    parser::Config &_cfg;
    container::FixedQueue<clr::RGB> &_rgb_queue;
    led::WS281X _ws281x;
    std::mutex _mutex;
};
}  // namespace executor

#endif