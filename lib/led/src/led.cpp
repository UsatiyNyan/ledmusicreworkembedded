//
// Created by antonrampage on 18.11.2019.
//
#include "led.h"
#include "rgb.h"
#include "ws2811.h"
#include "base_exception.h"

#include <vector>
#include <algorithm>

using exception::Exception;

namespace led {
static int rgb_to_hex(const clr::RGB &led_rgb) {
    return ((led_rgb.g & 0xff) << 16) + ((led_rgb.r & 0xff) << 8) + (led_rgb.b & 0xff);
}

WS281X::WS281X(size_t width, size_t length)
    : _width(width),
      _length(length) {
    _led_diodes.freq = WS2811_TARGET_FREQ;
    _led_diodes.dmanum = 5;
    _led_diodes.channel[0].gpionum = 21;
    _led_diodes.channel[0].count = static_cast<int>(width * length);
    _led_diodes.channel[0].invert = 0;
    _led_diodes.channel[0].brightness = 255;
    _led_diodes.channel[0].strip_type = WS2811_STRIP_RGB;
    _led_diodes.channel[1] = {};
    ws2811_return_t ret = ws2811_init(&_led_diodes);
    if (ret != WS2811_SUCCESS) {
        throw Exception("ws2811_init: " + std::string(ws2811_get_return_t_str(ret)));
    }
    for (size_t i = 0; i < width * length; ++i) {
        _led_diodes.channel[0].leds[i] = 0x000000;  // black
    }
}

WS281X::WS281X(WS281X &&other) noexcept {
    if (this != &other) {
        this->_led_diodes = other._led_diodes;
        this->_width = other._width;
        this->_length = other._length;
        other._led_diodes = {};  // TODO: check work
    }
}

WS281X &WS281X::operator=(WS281X &&other) noexcept {
    if (this != &other) {
        this->_led_diodes = other._led_diodes;
        this->_width = other._width;
        this->_length = other._length;
        other._led_diodes = {};  // TODO: check work
    }
    return *this;
}

WS281X::~WS281X() {
    ws2811_fini(&_led_diodes);
}

void WS281X::simple_mode(const clr::RGB &led_rgb) {
//    std::cout << led_rgb.r << ' ' << led_rgb.g << ' ' << led_rgb.b << std::endl;
    // left
    for (size_t i = _width * _length - 1; i >= _width + _width * _length / 2; --i) {
        _led_diodes.channel[0].leds[i] = _led_diodes.channel[0].leds[i - _width];
    }
    // right
    for (size_t i = 0; i < _width * _length / 2 - _width; ++i) {
        _led_diodes.channel[0].leds[i] = _led_diodes.channel[0].leds[i + _width];
    }
    // Set the left most updateLEDs with the new color
    for (size_t i = _width * _length / 2 - _width; i < _width * _length / 2 + _width; ++i) {
        _led_diodes.channel[0].leds[i] = rgb_to_hex(led_rgb);
    }
}

void WS281X::draw_line(const Point &a_real, const Point &b_real, const clr::RGB &led_rgb) {
    Point a = {a_real.x + 0.5f, a_real.y + 0.5f};
    Point b = {b_real.x + 0.5f, b_real.y + 0.5f};
    bool steep = (std::fabs(a.y - b.y) > std::fabs(a.x - b.x));
    if (steep) {
        std::swap(a.x, a.y);
        std::swap(b.x, b.y);
    }
    if (a.x > b.x) {
        std::swap(a.x, b.x);
        std::swap(a.y, b.y);
    }

    float dx = b.x - a.x;
    float dy = std::abs(b.y - a.y);

    float error = dx / 2.0f;
    int y_step = (a.y < b.y) ? 1 : -1;
    int y = static_cast<int>(a.y);

    const int max_x = static_cast<int>(b.x);

    for (int x = static_cast<int>(a.x); x <= max_x; ++x) {
        if (steep) {
            if (check_coord(y, x)) {
                _led_diodes.channel[0].leds[transform_coord(y, x)] = rgb_to_hex(led_rgb);
            }
        } else if (check_coord(x, y)) {
            _led_diodes.channel[0].leds[transform_coord(x, y)] = rgb_to_hex(led_rgb);
        }
        error -= dy;
        if (error < 0) {
            y += y_step;
            error += dx;
        }
    }
}

void WS281X::show_polygon(const Polygon &polygon, const clr::RGB &color) {
    const auto &vertices = polygon.get_vertices();
    for (size_t i = 0; i < vertices.size(); ++i) {
        if (i == vertices.size() - 1) {
            draw_line(vertices[i], vertices[0], color);
        } else {
            draw_line(vertices[i], vertices[i + 1], color);
        }
    }
}

static float check_missing(float rad) {
    float x = (1 + std::sqrt(1 + 2 * rad)) / 2;
    if ((x - std::floor(x) < 0.5000001f) && (x - std::floor(x) > 0.4999999f)) {
        return std::floor(x) + 0.5f;
    }
    return -1;
}
void WS281X::draw_eight_points(float x0, float y0, float x, float y, const clr::RGB &color) {
    if (check_coord(std::round(x0 + x), std::round(y0 + y))) {
        _led_diodes.channel[0].leds[transform_coord(x0 + x, y0 + y)] =
            rgb_to_hex(color);
    }
    if (check_coord(std::round(x0 + y), std::round(y0 + x))) {
        _led_diodes.channel[0].leds[transform_coord(x0 + y, y0 + x)] =
            rgb_to_hex(color);
    }
    if (check_coord(std::round(x0 + x), std::round(y0 - y))) {
        _led_diodes.channel[0].leds[transform_coord(x0 + x, y0 - y)] =
            rgb_to_hex(color);
    }
    if (check_coord(std::round(x0 + y), std::round(y0 - x))) {
        _led_diodes.channel[0].leds[transform_coord(x0 + y, y0 - x)] =
            rgb_to_hex(color);
    }
    if (check_coord(std::round(x0 - x), std::round(y0 + y))) {
        _led_diodes.channel[0].leds[transform_coord(x0 - x, y0 + y)] =
            rgb_to_hex(color);
    }
    if (check_coord(std::round(x0 - y), std::round(y0 + x))) {
        _led_diodes.channel[0].leds[transform_coord(x0 - y, y0 + x)] =
            rgb_to_hex(color);
    }
    if (check_coord(std::round(x0 - x), std::round(y0 - y))) {
        _led_diodes.channel[0].leds[transform_coord(x0 - x, y0 - y)] =
            rgb_to_hex(color);
    }
    if (check_coord(std::round(x0 - y), std::round(y0 - x))) {
        _led_diodes.channel[0].leds[transform_coord(x0 - y, y0 - x)] =
            rgb_to_hex(color);
    }
}

void WS281X::show_circle(const Circle &circle, const clr::RGB &color) {
    float radius = circle.get_radius();
    Point center = circle.get_center();

    float x0 = center.x + 0.5f;
    float y0 = center.y + 0.5f;
    float ir_x = std::abs(x0) - std::floor(std::abs(x0));
    float ir_y = std::abs(y0) - std::floor(std::abs(y0));;

    bool mode = false;
    if (((ir_x - 0.5 < 0.25) && (ir_x - 0.5 >= 0)) &&
        ((ir_y - 0.5 < 0.25) && (ir_y - 0.5 >= 0))) {
        x0 = std::floor(x0) + 0.5f;
        y0 = std::floor(y0) + 0.5f;
        mode = true;
    }

    if (!mode) {
        int x = 0;
        int y = static_cast<int>(radius);
        int delta = 1 - 2 * y;
        int error = 0;
        auto x_i = static_cast<int>(x0);
        auto y_i = static_cast<int>(y0);
        while (y >= 0) {
            if (check_coord(x_i + x, y_i + y)) {
                _led_diodes.channel[0].leds[transform_coord(x_i + x, y_i + y)] =
                    rgb_to_hex(color);
            }
            if (check_coord(x_i + x, y_i - y)) {
                _led_diodes.channel[0].leds[transform_coord(x_i + x, y_i - y)] =
                    rgb_to_hex(color);
            }
            if (check_coord(x_i - x, x_i + y)) {
                _led_diodes.channel[0].leds[transform_coord(x_i - x, y_i + y)] =
                    rgb_to_hex(color);
            }
            if (check_coord(x_i - x, y_i - y)) {
                _led_diodes.channel[0].leds[transform_coord(x_i - x, y_i - y)] =
                    rgb_to_hex(color);
            }
            error = 2 * (delta + y) - 1;
            if (delta < 0 && error <= 0) {
                ++x;
                delta += 2 * x + 1;
                continue;
            }
            error = 2 * (delta - x) - 1;
            if (delta > 0 && error > 0) {
                --y;
                delta += 1 - 2 * y;
                continue;
            }
            ++x;
            delta += 2 * (x - y);
            --y;
        }
    } else {  // TODO: check 0.5
        float x = 0.5f;
        float y = std::floor(radius) + 0.5f;
        float rad = y;
        float d = 0;
        float v = 0;
        float g = 0;
        float x_mis = check_missing(rad);
        if (x_mis != -1) {
            draw_eight_points(x0, y0, x_mis, y, color);
        }
        while (y >= (rad + 0.5) / 2) {
            draw_eight_points(x0, y0, x, y, color);
            g = (x + 0.5f) * (x + 0.5f) + y * y - rad * rad;
            v = x * x + (y - 0.5f) * (y - 0.5f) - rad * rad;
            d = (x + 0.5f) * (x + 0.5f) + (y - 0.5f) * (y - 0.5f) - rad * rad;
            //std::cout << v << ' ' << g << ' ' << d  << std::endl;
            if (d < 0) {
                if (std::fabs(g) - std::fabs(d) <= 0) {
                    x++;
                } else {
                    x++;
                    y--;
                }
            } else if (d > 0) {
                if (std::fabs(d) - std::fabs(v) <= 0) {
                    x++;
                    y--;
                } else {
                    y--;
                }
            } else {
                x++;
                y--;
            }
        }
    }
}
void WS281X::render() {
    ws2811_render(&_led_diodes);
}
size_t WS281X::get_width() const {
    return _width;
}
size_t WS281X::get_length() const {
    return _length;
}
int WS281X::transform_coord(int x, int y) { // TODO: Ask Anton
    int center = static_cast<int>(_width * _length / 2 - _width / 2 - 1);
    if (x % 2 != 0) {
        return center + ((x * static_cast<int>(_width)) - y + 1);
    } else {
        return center + ((x * static_cast<int>(_width)) + y);
    }
}
bool WS281X::check_coord(int x, int y) {
    return ((y <= _width / 2) && (y >= -_width / 2 + 1)) &&
        ((x <= _length / 2) && (x >= -_length / 2 + 1));
}
}  // namespace led
