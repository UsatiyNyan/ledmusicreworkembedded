#include "parser.h"

namespace parser {
Parser::Parser(serial::Connection &&connection, Config &config)
    : _connection(std::move(connection)),
      _config(config) {}
}  // namespace parser




//
//static int read_with_markers(int32_t file, char s, char e, char *buf, int32_t length) {
//    char b;
//    int32_t i = 0;
//    bool in_progress = false;
//    while (true) {
//        while (read(file, &b, 1) <= 0);
//
//        if (!in_progress) {
//            if (b == s) {
//                in_progress = true;
//            } else {
//                continue;
//            }
//        }
//
//        if (b == e || length < i) {
//            break;
//        }
//
//        if (is_num(b)) {
//            buf[i] = b;
//            i++;
//        }
//    }
//    return 0;
//}
//
//static void parse_data(const char *buf, RGB &led_rgb, int32_t sum) {
//    int32_t r = std::strtol(buf, nullptr, 10);
//    int32_t g = std::strtol(&buf[3], nullptr, 10);
//    int32_t b = std::strtol(&buf[6], nullptr, 10);
//    r -= g;
//    r /= 1000000;
//    g -= b;
//    g /= 1000;
//
//    if (sum == (r + g + b)) {
//        g_mutex.lock();
//        led_rgb.r = r;
//        led_rgb.g = g;
//        led_rgb.b = b;
//        g_mutex.unlock();
//    }
//}
//
//static bool parse_config(const char *buf, Player &player, int32_t sum) {
//    int32_t verteces = buf[0] - '0';
//    sum -= verteces;
//    int32_t mode = buf[1] - '0';
//    sum -= mode;
//    auto tmp_pts = new Point[verteces];
//    for (int32_t kI = 0; kI < verteces; ++kI) {
//        tmp_pts[kI].x =  (float_t)(buf[6 * kI + 2] - '0') * 100;
//        tmp_pts[kI].x += (float_t)(buf[6 * kI + 3] - '0') * 10;
//        tmp_pts[kI].x += (float_t)(buf[6 * kI + 4] - '0');
//        tmp_pts[kI].y =  (float_t)(buf[6 * kI + 5] - '0') * 100;
//        tmp_pts[kI].y += (float_t)(buf[6 * kI + 6] - '0') * 10;
//        tmp_pts[kI].y += (float_t)(buf[6 * kI + 7] - '0');
//        sum -= tmp_pts[kI].x;
//        sum -= tmp_pts[kI].y;
//        tmp_pts[kI].x /= 10;
//        tmp_pts[kI].y /= 10;
//        tmp_pts[kI].x -= 20;
//        tmp_pts[kI].y -= 20;
//    }
//    int32_t bpm = 0;
//    bpm += (buf[6 * verteces + 2] - '0') * 100;
//    bpm += (buf[6 * verteces + 3] - '0') * 10;
//    bpm += (buf[6 * verteces + 4] - '0');
//    sum -= bpm;
//    int32_t rotation = 0;
//    rotation += (buf[6 * verteces + 5] - '0') * 100;
//    rotation += (buf[6 * verteces + 6] - '0') * 10;
//    rotation += (buf[6 * verteces + 7] - '0');
//    sum -= rotation;
//    if (sum == 0) {
//        g_mutex.lock();
//        delete player.base_polygon;
//        player.base_polygon = new Polygon(verteces, 0, 0, 0);
//        player.base_polygon->set_items(tmp_pts, verteces);
//        player.delay = 1000000 / bpm;
//        player.verteces = verteces;
//        auto true_rot = (rotation - 20) * M_PI / 180;
//        auto tr_matrix = new Point[2];
//        tr_matrix[0].x = std::cos(true_rot);
//        tr_matrix[0].y = std::sin(true_rot);
//        tr_matrix[1].x = -std::sin(true_rot);
//        tr_matrix[1].y = std::cos(true_rot);
//        delete[] player.tr_matrix;
//        player.tr_matrix = tr_matrix;
//        player.mode = mode;
//        g_mutex.unlock();
//        return true;
//    }
//    delete[] tmp_pts;
//    return false;
//}
//
//static bool parse_new_led(const char *buf, Player &player, int32_t sum) {
//    int32_t tmp_width = 0;
//    int32_t tmp_length = 0;
//    tmp_width += (buf[0] - '0') * 10;
//    tmp_width += (buf[1] - '0');
//    tmp_length += (buf[2] - '0') * 10;
//    tmp_length += (buf[3] - '0');
//    if (tmp_length + tmp_width == sum) {
//        g_mutex.lock();
//        player.led_.change_settings(tmp_width, tmp_length);
//        g_mutex.unlock();
//        return true;
//    }
//    return false;
//}
//
//void read_serial_port(int32_t file, Player &player) {
//    fd_set rfds;
//    FD_ZERO(&rfds);
//    FD_SET(file, &rfds);
//
//    char buf[CFG_LENGTH + 1];
//    bool settings = false;
//
//    while (select(file + 1, &rfds, NULL, NULL, NULL) > 0) {
//        int32_t sum = 0;
//        read_with_markers(file, '{', '}', buf, 4);
//        sum = std::strtol(buf, nullptr, 10);
//        if (sum < 1000) {
//            read_with_markers(file, '<', '>', buf, 9);
//            parse_data(buf, player.rgb, sum);
//            settings = false;
//        } else if (!settings) {
//            if (sum < 2000) {
//                sum -= 1000;
//                read_with_markers(file, '[', ']', buf, 4);
//                settings = parse_new_led(buf, player, sum);
//            } else {
//                sum -= 2000;
//                read_with_markers(file, '[', ']', buf, CFG_LENGTH);
//                settings = parse_config(buf, player, sum);
//            }
//        }
//    }
//}
