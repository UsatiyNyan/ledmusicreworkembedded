//
// Created by kira on 30.04.2020.
//

#include "circle.h"

namespace geometry {
Circle::Circle(const Point &center, const clr::RGB &rgb)
    : _center(center),
      _clr(rgb) {}

void Circle::expand() {
    ++_radius;
}
Point Circle::get_center() const {
    return _center;
}
clr::RGB Circle::get_color() const {
    return _clr;
}
size_t Circle::get_radius() const {
    return _radius;
}
}  // namespace geometry
