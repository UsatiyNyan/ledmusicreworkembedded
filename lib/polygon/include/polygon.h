//
// Created by kira on 27.11.2019.
//

#ifndef PLAYER_LIB_PLAYER_POLYGON_H_
#define PLAYER_LIB_PLAYER_POLYGON_H_

#include "rgb.h"
#include <vector>

namespace geometry {
struct Point {
    float x;
    float y;
};

class Polygon {
 public:
    Polygon(const std::vector<Point> &vertices, const clr::RGB & rgb);
    void expand(const std::vector<Point> &tr_matrix);

 private:
    std::vector<Point> _vertices;
    clr::RGB _clr;
    float _cos = 0;
    bool _ind_cos = false;
};
}  // namespace geometry

#endif //PLAYER_LIB_PLAYER_POLYGON_H_
