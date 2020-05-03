#include "player.h"
#include <chrono>

namespace loop {
Player::Player(container::FixedQueue<clr::RGB> &rgb_queue,
               parser::Config &config)
    : _rgb_queue(rgb_queue),
      _cfg(config),
      _ws281x(_cfg.get_width(), _cfg.get_length()),
      _circles(geometry::Circles(config.get_center(),
                                 config.get_2d_objs_amount())),
      _polygons(geometry::Polygons(config.get_vertices(),
                                   config.get_2d_objs_amount(),
                                   config.get_tr_matrix())) {
}

void Player::job() {
    auto sleepy_time = std::chrono::system_clock::now() + _cfg.get_timeout();
    if (_cfg.changed != parser::NOTHING_CHANGED) {
        std::unique_lock _(_mutex);
        switch (_cfg.changed) {
            case parser::BPM:
            case parser::NOTHING_CHANGED:
            case parser::BASIC:break;
            case parser::CIRCLE:_circles = geometry::Circles(_cfg.get_center(), _cfg.get_2d_objs_amount());
                break;
            case parser::ROTATION:
            case parser::POLYGON:
                _polygons = geometry::Polygons(_cfg.get_vertices(),
                                               _cfg.get_2d_objs_amount(),
                                               _cfg.get_tr_matrix());
                break;
            case parser::LENGTH_AND_WIDTH:_ws281x = led::WS281X(_cfg.get_width(), _cfg.get_length());
                _circles = geometry::Circles(_cfg.get_center(), _cfg.get_2d_objs_amount());
                _polygons =
                    geometry::Polygons(_cfg.get_vertices(), _cfg.get_2d_objs_amount(), _cfg.get_tr_matrix());
                break;
            default: throw exception::Exception("wrong config: " + std::to_string(_cfg.changed));
        }
        _cfg.changed = parser::NOTHING_CHANGED;
    }

    switch (_cfg.get_mode()) {
        case parser::BASIC:_ws281x.simple_mode(_rgb_queue.back());
            break;
        case parser::CIRCLE:
            for (size_t i = _rgb_queue.size() - 1; i >= 0; --i) {
                _ws281x.show_circle(_circles[i], _rgb_queue[i]);
            }
            break;
        case parser::POLYGON:
            for (size_t i = _rgb_queue.size() - 1; i >= 0; --i) {
                _ws281x.show_polygon(_polygons[i], _rgb_queue[i]);
            }
            break;
        default: throw exception::Exception("wrong mode");
    }
    _ws281x.render();
    std::this_thread::sleep_until(sleepy_time);
}
}  // namespace executor
