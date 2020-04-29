//
// Created by antonrampage on 18.11.2019.
//

#include <iostream>
#include <vector>
#include <cmath>

#include "LED.h"
#include "rpi_ws281x/ws2811.h"


static inline int32_t rgb_to_hex(RGB &led_rgb) {
    return ((led_rgb.g & 0xff) << 16) + ((led_rgb.r & 0xff) << 8) + (led_rgb.b & 0xff);
}

LED::LED(int32_t width, int32_t length) :
    width(width),
    length(length),
    ledstring(new ws2811_t) {
    *ledstring = {0, 0, 0, TARGET_FREQ, DMA, {GPIO_PIN, 0, width * length, STRIP_TYPE, 0, MAX_BRGHT}};
    try {
        ws2811_return_t ret;
        if ((ret = ws2811_init(ledstring)) != WS2811_SUCCESS) {
            throw ret;
        }
    }
    catch (ws2811_return_t ret) {
        std::cout << "ws2811_init failed: " << ws2811_get_return_t_str(ret) << std::endl;
    }

    for (int i = 0; i < width * length; ++i) {
        ledstring->channel[0].leds[i] = 0x000000;
    }
}

LED::~LED() {
    ws2811_fini(ledstring);
    delete ledstring;
}

void LED::show_led_on_pi(RGB &led_rgb) {
    // left
//	std::cout << led_rgb.r << ' ' << led_rgb.g << ' ' << led_rgb.b << std::endl;
    for (int i = width * length - 1; i >= width + width * length / 2; --i) {
        ledstring->channel[0].leds[i] = ledstring->channel[0].leds[i - width];
    }
    // right
    for (int i = 0; i < width * length / 2 - width; ++i) {
        ledstring->channel[0].leds[i] = ledstring->channel[0].leds[i + width];
    }
    // Set the left most updateLEDs with the new color
    for (int i = width * length / 2 - width; i < width * length / 2 + width; ++i) {
        ledstring->channel[0].leds[i] = rgb_to_hex(led_rgb);
    }
}

int32_t LED::transform_coord(int32_t x, int32_t y) {
    int centre = width * length / 2 - width / 2 - 1;
    int res = 0;
    if (x % 2 != 0) {
        res = (x == 0) ? centre : (centre + ((x * width) - y + 1));
    } else {
        res = centre + ((x * width) + y);
    }
    return res;
}

bool LED::check_coord(int32_t x, int32_t y) {
    return ((y <= width / 2) && (y >= -width / 2 + 1)) &&
        ((x <= length / 2) && (x >= -length / 2 + 1));
}

void LED::draw_line(Point &a_real, Point &b_real, RGB &led_rgb) {
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
    float dy = std::fabs(b.y - a.y);

    float error = dx / 2.0f;
    int y_step = (a.y < b.y) ? 1 : -1;
    int y = static_cast<int>(a.y);

    const int max_x = static_cast<int>(b.x);

    for (int x = static_cast<int>(a.x); x <= max_x; x++) {
        if (steep) {
            if (check_coord(y, x)) {
                ledstring->channel[0].leds[transform_coord(y, x)] = rgb_to_hex(led_rgb);
            }
        } else {
            if (check_coord(x, y)) {
                ledstring->channel[0].leds[transform_coord(x, y)] = rgb_to_hex(led_rgb);
            }
        }
        error -= dy;
        if (error < 0) {
            y += y_step;
            error += dx;
        }
    }
}

void LED::show_figure_on_led(Polygon *polygon) {
    for (int i = 0; i < polygon->verteces; ++i) {
        if (i == polygon->verteces - 1) {
            draw_line(polygon->vectors[i], polygon->vectors[0], polygon->color);
        } else {
            draw_line(polygon->vectors[i], polygon->vectors[i + 1], polygon->color);
        }
    }
}

float_t LED::check_missing(float_t rad) {
    float_t x = (1 + std::sqrt(1 + 2 * rad)) / 2;
    if ((x - std::floor(x) < 0.5000001f) && (x - std::floor(x) > 0.4999999f)) {
        return std::floor(x) + 0.5f;
    }
    return -1;
}

void LED::draw_eight_points(float_t x0, float_t y0, float_t x, float_t y, RGB &color) {
    if (check_coord(std::round(x0 + x), std::round(y0 + y))) {
        ledstring->channel[0].leds[transform_coord(x0 + x, y0 + y)] =
            rgb_to_hex(color);
    }
    if (check_coord(std::round(x0 + y), std::round(y0 + x))) {
        ledstring->channel[0].leds[transform_coord(x0 + y, y0 + x)] =
            rgb_to_hex(color);
    }
    if (check_coord(std::round(x0 + x), std::round(y0 - y))) {
        ledstring->channel[0].leds[transform_coord(x0 + x, y0 - y)] =
            rgb_to_hex(color);
    }
    if (check_coord(std::round(x0 + y), std::round(y0 - x))) {
        ledstring->channel[0].leds[transform_coord(x0 + y, y0 - x)] =
            rgb_to_hex(color);
    }
    if (check_coord(std::round(x0 - x), std::round(y0 + y))) {
        ledstring->channel[0].leds[transform_coord(x0 - x, y0 + y)] =
            rgb_to_hex(color);
    }
    if (check_coord(std::round(x0 - y), std::round(y0 + x))) {
        ledstring->channel[0].leds[transform_coord(x0 - y, y0 + x)] =
            rgb_to_hex(color);
    }
    if (check_coord(std::round(x0 - x), std::round(y0 - y))) {
        ledstring->channel[0].leds[transform_coord(x0 - x, y0 - y)] =
            rgb_to_hex(color);
    }
    if (check_coord(std::round(x0 - y), std::round(y0 - x))) {
        ledstring->channel[0].leds[transform_coord(x0 - y, y0 - x)] =
            rgb_to_hex(color);
    }
}

void LED::show_circle_on_led(Polygon *polygon) {
    float_t x0 = polygon->vectors[0].x + 0.5f;
    float_t y0 = polygon->vectors[0].y + 0.5f;
    double_t ir_x = std::fabs(x0) - std::floor(std::fabs(x0));
    double_t ir_y = std::fabs(y0) - std::floor(std::fabs(y0));;
    int mode = 0;
    if (((ir_x - 0.5 < 0.25) && (ir_x - 0.5 >= 0)) &&
        ((ir_y - 0.5 < 0.25) && (ir_y - 0.5 >= 0))) {
        x0 = std::floor(x0) + 0.5f;
        y0 = std::floor(y0) + 0.5f;
        mode = 1;
    }

    if (!mode) {
        int x = 0;
        int y = static_cast<int>(polygon->radius);
        int delta = 1 - 2 * y;
        int error = 0;
        auto x_i = static_cast<int>(x0);
        auto y_i = static_cast<int>(y0);
        while (y >= 0) {
            if (check_coord(x_i + x, y_i + y)) {
                ledstring->channel[0].leds[transform_coord(x_i + x, y_i + y)] =
                    rgb_to_hex(polygon->color);
            }
            if (check_coord(x_i + x, y_i - y)) {
                ledstring->channel[0].leds[transform_coord(x_i + x, y_i - y)] =
                    rgb_to_hex(polygon->color);
            }
            if (check_coord(x_i - x, x_i + y)) {
                ledstring->channel[0].leds[transform_coord(x_i - x, y_i + y)] =
                    rgb_to_hex(polygon->color);
            }
            if (check_coord(x_i - x, y_i - y)) {
                ledstring->channel[0].leds[transform_coord(x_i - x, y_i - y)] =
                    rgb_to_hex(polygon->color);
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
    } else {
        float_t x = 0.5f;
        float_t y = std::floor(polygon->radius) + 0.5f;
        float_t rad = y;
        float_t d = 0;
        float_t v = 0;
        float_t g = 0;
        float_t x_mis = check_missing(rad);
        if (x_mis != -1) {
            draw_eight_points(x0, y0, x_mis, y, polygon->color);
        }
        while (y >= (rad + 0.5) / 2) {
            draw_eight_points(x0, y0, x, y, polygon->color);
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

void LED::change_settings(int32_t tmp_width, int32_t tmp_length) {
    std::cout << tmp_width << ' ' << tmp_length;
    if (tmp_width <= 0 || tmp_length <= 0) {
        return;
    }
    ws2811_fini(ledstring);
    width = tmp_width;
    length = tmp_length;
    delete ledstring;
    ledstring = new ws2811_t;
    *ledstring = {0, 0, 0, TARGET_FREQ, DMA, {GPIO_PIN, 0, width * length, STRIP_TYPE, 0, MAX_BRGHT}};
    ws2811_return_t ret;
    try {
        if ((ret = ws2811_init(ledstring)) != WS2811_SUCCESS) {
            throw ret;
        }
    }
    catch (ws2811_return_t ret) {
        std::cout << "ws2811_init failed: " << ws2811_get_return_t_str(ret) << std::endl;
    }
    throw ret;
}

void LED::render() {
    ws2811_render(ledstring);
}

int32_t LED::get_width() const {
    return width;
}

int32_t LED::get_length() const {
    return length;
}
