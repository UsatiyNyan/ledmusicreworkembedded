#include <iostream>
#include <chrono>
#include <cmath>

#include "parser.h"
#include "base_exception.h"

using namespace std::chrono_literals;

constexpr size_t baud = 19200;
constexpr const char *serial_port = "/dev/serial0";

namespace parser {
constexpr const uint8_t BEGIN = '<';
constexpr const uint8_t END = '>';

Parser::Parser(container::FixedQueue<clr::RGB> &rgb_queue, Config &config)
    : _connection(serial_port, baud),
      _config(config),
      _rgb_queue(rgb_queue) {
}
void Parser::job() {
    /* general structure of a message:
     * '<' | checksum | flag | data | '>'
     * */
    _read_buf.clear();
    retrieve_data();
    check_sum();

//    for (const auto &byte: _read_buf) {
//        std::cout << static_cast<int>(byte) << " | ";
//    }
//    std::cout << std::endl;
    {
        std::unique_lock _(_mutex);
        uint8_t flag = _read_buf[1];
        switch (flag) {
            case BASIC:parse_basic();
                break;
            case RGB:parse_rgb();
                break;
            case CIRCLE:parse_circle();
                break;
            case POLYGON:parse_polygon();
                break;
            case BPM:parse_bpm();
                break;
            case ROTATION:parse_rotation();
                break;
            case LENGTH_AND_WIDTH:parse_length_and_width();
                break;
            default:_connection.flush_input();
                break;
        }
    }
    std::this_thread::sleep_for(10ms);
}
void Parser::retrieve_data() {
    uint8_t buf = 0;
    do {
        _connection.read_exact(&buf, 1);
    } while (buf != BEGIN);

    while (true) {
        _connection.read_exact(&buf, 1);
        if (buf == END) {
            break;
        }
        _read_buf.push_back(buf);
    }
}
void Parser::check_sum() {
    uint8_t checksum = _read_buf[0];
    for (size_t i = 1; i < _read_buf.size(); ++i) {
        checksum ^= _read_buf[i];
    }
    if (checksum != 0xFF) {
        _connection.flush_input();
        return;
    }
}
void Parser::parse_basic() {
    _config._mode = BASIC;
    _config.changed = BASIC;
}
void Parser::parse_rgb() {
    _rgb_queue.push_back({
        ((static_cast<unsigned>(_read_buf[2])) - '0') * 100 +
        ((static_cast<unsigned>(_read_buf[3])) - '0') * 10 +
        ((static_cast<unsigned>(_read_buf[4])) - '0'),
        ((static_cast<unsigned>(_read_buf[5])) - '0') * 100 +
        ((static_cast<unsigned>(_read_buf[6])) - '0') * 10 +
        ((static_cast<unsigned>(_read_buf[7])) - '0'),
        ((static_cast<unsigned>(_read_buf[8])) - '0') * 100 +
        ((static_cast<unsigned>(_read_buf[9])) - '0') * 10 +
        ((static_cast<unsigned>(_read_buf[10])) - '0')
    });
    std::cout << _rgb_queue.back().r << " | "
              << _rgb_queue.back().g << " | "
              << _rgb_queue.back().b << std::endl;
}
void Parser::parse_circle() {
    _config._center = {
        static_cast<float>(_read_buf[2]),
        static_cast<float>(_read_buf[3])
    };
    _config._mode = CIRCLE;
    _config.changed = CIRCLE;
}
void Parser::parse_polygon() {
    std::vector<geometry::Point> new_vertices(_read_buf.size() - 2);
    for (size_t i = 0; i < _read_buf.size() - 2; ++i) {
        new_vertices[i].x = _read_buf[2 + 2 * i];
        new_vertices[i].y = _read_buf[2 + 2 * i + 1];
    }
    _config._vertices = std::move(new_vertices);
    _config._mode = POLYGON;
    _config.changed = POLYGON;
}
void Parser::parse_bpm() {
    uint16_t bpm =
        ((static_cast<unsigned>(_read_buf[2])) - '0') * 100 +
        ((static_cast<unsigned>(_read_buf[3])) - '0') * 10 +
        ((static_cast<unsigned>(_read_buf[4])) - '0');
    _config._timeout = std::chrono::milliseconds(1875 / bpm);
    _config.changed = BPM;
}
void Parser::parse_rotation() {
    _config._radian = static_cast<float>(_read_buf[2]) *
                      static_cast<float>(M_PI) / 180;
    _config.changed = ROTATION;
}
void Parser::parse_length_and_width() {
    _config._length =
        ((static_cast<unsigned>(_read_buf[2])) - '0') * 100 +
        ((static_cast<unsigned>(_read_buf[3])) - '0') * 10 +
        ((static_cast<unsigned>(_read_buf[4])) - '0');

    _config._width =
        ((static_cast<unsigned>(_read_buf[5])) - '0') * 100 +
        ((static_cast<unsigned>(_read_buf[6])) - '0') * 10 +
        ((static_cast<unsigned>(_read_buf[7])) - '0'),

    _config.changed = LENGTH_AND_WIDTH;
}
}  // namespace parser
