//
// Created by kira on 01.05.2020.
//

#include "config.h"
#include <cmath>

namespace parser {
uint8_t parser::Config::get_mode() const {
    return _mode;
}

const geometry::Point &Config::get_center() const {
    return _center;
}
const std::vector<geometry::Point> &Config::get_vertices() const {
    return _vertices;
}
std::vector<geometry::Point> Config::get_tr_matrix() const {
    float cos = std::cos(_radian);
    float sin = std::sin(_radian);
    std::vector<geometry::Point> tr_matrix{
        {cos, sin},
        {-sin, cos}
    };
    return std::move(tr_matrix);
}
const std::chrono::milliseconds &Config::get_timeout() const {
    return _timeout;
}
size_t Config::get_width() const {
    return _width;
}
size_t Config::get_length() const {
    return _length;
}
size_t Config::get_2d_objs_amount() const {
    return _width + _length;
}
}  // namespace parser
