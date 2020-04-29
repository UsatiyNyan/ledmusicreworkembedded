//
// Created by antonrampage on 18.11.2019.
//

#ifndef LIB_LED_H_
#define LIB_LED_H_

#include "ws2811.h"
#include "polygon.h"

#include <cmath>
#include <vector>

#define TARGET_FREQ                             WS2811_TARGET_FREQ
#define GPIO_PIN                                21
#define DMA                                     5
#define STRIP_TYPE                              WS2811_STRIP_RGB
#define MAX_BRIGHT                               255

namespace led {
class WS281X {
 public:
    WS281X(int32_t width, int32_t length);
    ~WS281X();
    void show_led_on_pi(RGB &led_rgb);
    void show_figure_on_led(Polygon *polygon);
    void show_circle_on_led(Polygon *polygon);
    void draw_line(Point &a, Point &b, RGB &led_rgb);
    float_t check_missing(float_t rad);
    void draw_eight_points(float_t x0, float_t y0, float_t x, float_t y, RGB &color);
    [[nodiscard]] int32_t get_width() const;
    [[nodiscard]] int32_t get_length() const;
    void change_settings(int32_t width, int32_t length);
    void render();
 private:
    int32_t transform_coord(int32_t x, int32_t y);
    bool check_coord(int32_t x, int32_t y);
    ws2811_t ledstring;
    int32_t width;
    int32_t length;
};
}  // namespace led

#endif //LIB_LED_H_
