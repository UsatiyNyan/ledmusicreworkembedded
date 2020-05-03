//
// Created by kira on 30.04.2020.
//

#include "circle.h"

namespace geometry {
Circle::Circle(const Point &center)
    : _center(center) {

}
void Circle::expand() {
    ++_radius;
}
Point Circle::get_center() const {
    return _center;
}
size_t Circle::get_radius() const {
    return _radius;
}
Circles::Circles(const Point &center, size_t size)
    : _circles(size, Circle(center)) {
    for (int i = 0; i != size; ++i) {
        for (int j = i; j >= 0; --j) {
            _circles[j].expand();
        }
    }
}
Circles::Circles(Circles &&other) noexcept {
    this->_circles = std::move(other._circles);
}
Circles &Circles::operator=(Circles &&other) noexcept {
    this->_circles = std::move(other._circles);
    return *this;
}
Circle &Circles::operator[](size_t i) {
    return _circles[i];
}
}  // namespace geometry
