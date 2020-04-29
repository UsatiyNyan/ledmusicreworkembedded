#include "player.h"
#include "serial.h"
#include "uart.h"
#include "LED.h"
#define BAUDRATE 19200

Player::Player(size_t delay, const char *device) :
    delay(delay),
    device(device),
    rgb({0, 0, 0}),
    polygons(new fixed_queue<Polygon *>(64)),
    verteces(3),
    base_polygon(new Polygon(0, 0, 0, 0)),
    tr_matrix(new Point[2]),
    mode(2),
    led_(8, 32) {
    tr_matrix[0].x = 1;
    tr_matrix[0].y = 0;
    tr_matrix[1].x = 0;
    tr_matrix[1].y = 1;
}

Player::~Player() {
    delete base_polygon;
    delete[] tr_matrix;
}

void Player::render() {
    auto *tmp = new Polygon(verteces, rgb.r, rgb.g, rgb.b);
    tmp->set_items(base_polygon->vectors, verteces);
    polygons->push_back(tmp);

    for (unsigned kI = 0; kI < polygons->size(); ++kI) {
        auto polygon = polygons->at(kI);
        // mode == 0 => polygon
        // mode == 1 => circle
        if (mode == 1) {
            led_.show_circle_on_led(polygon);
            polygon->radius += 1;
        } else {
            led_.show_figure_on_led(polygon);
            polygon->expand();
        }
    }
}

void serial_interface(Player &player) {
    int32_t filed = serialport_init(player.device.c_str(), BAUDRATE);
    serialport_flush(filed);
    read_serial_port(filed, player);
    serialport_flush(filed);
    serialport_close(filed);
}

void show_leds(Player &player) {
    while (true) {
        // mode == 2 => basic
        if (player.mode == 2) {
            player.led_.show_led_on_pi(player.rgb);
        } else {
            player.render();
        }
        player.led_.render();
        usleep(player.delay);
    }
}
