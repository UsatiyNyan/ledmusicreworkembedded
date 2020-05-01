//
// Created by antonrampage on 18.11.2019.
//

#ifndef LIB_LED_H_
#define LIB_LED_H_

#include "ws2811.h"
#include "rgb.h"
#include "polygon.h"
#include "circle.h"

#include <cmath>
#include <vector>

using namespace geometry;


namespace led {
class WS281X {
 public:
    WS281X(size_t width, size_t length);
    WS281X(WS281X &&other) noexcept;
    WS281X &operator=(WS281X &&other) noexcept;
    ~WS281X();
    void simple_mode(const clr::RGB &led_rgb);
    void show_polygon(const Polygon &polygon, const clr::RGB &color);
    void show_circle(const Circle &circle, const clr::RGB &color);
    void draw_line(const Point &a, const Point &b, const clr::RGB &led_rgb);
    void draw_eight_points(float x0, float y0, float x, float y, const clr::RGB &color);

    void render();

    [[nodiscard]] size_t get_width() const;
    [[nodiscard]] size_t get_length() const;
 private:
    int transform_coord(int x, int y);
    bool check_coord(int x, int y);
    ws2811_t _led_diodes{};
    size_t _width;
    size_t _length;
    void draw_eight_points(float x0, float y0, float x, float y, const clr::RGB &color);
};
}  // namespace led

#endif //LIB_LED_H_
