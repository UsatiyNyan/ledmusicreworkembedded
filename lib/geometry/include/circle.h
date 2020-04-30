//
// Created by kira on 30.04.2020.
//

#ifndef RPI_LED_LIB_POLYGON_INCLUDE_CIRCLE_H_
#define RPI_LED_LIB_POLYGON_INCLUDE_CIRCLE_H_

#include "point.h"
#include "rgb.h"
#include <cstddef>

namespace geometry {
class Circle {
 public:
    Circle(const Point &center, const clr::RGB & rgb);
    void expand();
    [[nodiscard]] Point get_center() const;
    [[nodiscard]] clr::RGB get_color() const;
    [[nodiscard]] size_t get_radius() const;
 private:
    clr::RGB _clr;
    Point _center;
    size_t _radius = 0;
};
class Circles {
 public:

 private:
    std::vector<geometry::Circle> _circles;
};
}  // namespace geometry

#endif //RPI_LED_LIB_POLYGON_INCLUDE_CIRCLE_H_
