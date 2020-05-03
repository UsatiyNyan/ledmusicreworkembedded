//
// Created by kira on 30.04.2020.
//

#ifndef RPI_LED_LIB_PARSER_INCLUDE_CONFIG_H_
#define RPI_LED_LIB_PARSER_INCLUDE_CONFIG_H_

#include "rgb.h"
#include "polygon.h"
#include "circle.h"

#include <atomic>
#include <vector>
#include <chrono>

using namespace std::chrono_literals;

namespace parser {
enum FLAGS : uint8_t {
    BASIC = 0x00,
    CIRCLE = 0x01,
    POLYGON = 0x02,
    BPM = 0x03,
    ROTATION = 0x04,
    LENGTH_AND_WIDTH = 0x05,
    RGB = 0xFF,
    NOTHING_CHANGED = 0xFF
};
class Config {
    friend class Parser;
 public:
    Config() = default;
    Config(Config &) = delete;
    Config(Config &&) = delete;

    [[nodiscard]] uint8_t get_mode() const;
    [[nodiscard]] const geometry::Point &get_center() const;
    [[nodiscard]] const std::vector<geometry::Point> &get_vertices() const;
    [[nodiscard]] std::vector<geometry::Point> get_tr_matrix() const;
    [[nodiscard]] const std::chrono::milliseconds &get_timeout() const;
    [[nodiscard]] size_t get_width() const;
    [[nodiscard]] size_t get_length() const;
    [[nodiscard]] size_t get_2d_objs_amount() const;

    std::atomic<uint8_t> changed = NOTHING_CHANGED;
 private:
    std::vector<geometry::Point> _vertices = {{-1, -1}, {-1, 1}, {2, 0}};
    geometry::Point _center = {0, 0};
    size_t _length = 32;
    size_t _width = 8;
    float _radian = 0;
    std::chrono::milliseconds _timeout = 25ms;
    uint8_t _mode = FLAGS::POLYGON;
};
}  // namespace parser

#endif //RPI_LED_LIB_PARSER_INCLUDE_CONFIG_H_
