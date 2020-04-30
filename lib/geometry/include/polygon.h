//
// Created by kira on 27.11.2019.
//

#ifndef PLAYER_LIB_PLAYER_POLYGON_H_
#define PLAYER_LIB_PLAYER_POLYGON_H_

#include "rgb.h"
#include "point.h"
#include <vector>

namespace geometry {
class Polygon {
 public:
    Polygon(const std::vector<Point> &vertices, const clr::RGB & rgb);
    void expand(const std::vector<Point> &tr_matrix);
    Point &operator[](size_t i);
    [[nodiscard]] const std::vector<Point> &get_vertices() const;
    [[nodiscard]] clr::RGB get_color() const;
 private:
    std::vector<Point> _vertices;
    clr::RGB _clr;
    float _cos = 0;
    bool _ind_cos = false;
};
class Polygons {
 public:

 private:
    std::vector<geometry::Polygon> _polygons;
};
}  // namespace geometry

#endif //PLAYER_LIB_PLAYER_POLYGON_H_
