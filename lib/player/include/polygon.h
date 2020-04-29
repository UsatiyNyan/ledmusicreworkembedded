//
// Created by kira on 27.11.2019.
//

#ifndef PLAYER_LIB_PLAYER_POLYGON_H_
#define PLAYER_LIB_PLAYER_POLYGON_H_

#include <stdint-gcc.h>
#include <cstdlib>
#include <cmath>

typedef struct RGB {
    int32_t r;
    int32_t g;
    int32_t b;
} RGB;

typedef struct Point {
    float_t x;
    float_t y;
} Point;

class Polygon {
public:
    Polygon(size_t  verteces, int32_t r, int32_t g, int32_t b);
    ~Polygon();

    void set_items(const Point *matrix, size_t size);
    void expand(const Point *tr_matrix = nullptr);

    size_t verteces;
    Point *vectors;
    RGB color;
    float_t radius;
    float_t cos;
    int32_t ind_cos;
};

#endif //PLAYER_LIB_PLAYER_POLYGON_H_
