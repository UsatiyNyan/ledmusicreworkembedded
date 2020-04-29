#ifndef __PLAYERH__
#define __PLAYERH__

#include <thread>
#include <string>
#include <cstdint>
#include <cmath>
#include "fixed_queue.h"
#include "LED.h"
#include "polygon.h"


class Player {
public:
    explicit Player(size_t delay, const char *device);
    ~Player();
    void render();

    size_t delay;
    std::string device;
    RGB rgb;
    fixed_queue<Polygon *> *polygons;
    int32_t verteces;
    Polygon *base_polygon;
    Point *tr_matrix;
    int32_t mode;
    LED led_;

private:
    // singleton
    Player &operator=(Player const &);
    Player(Player const &);
};

void serial_interface(Player &player);
void show_leds(Player &player);

#endif