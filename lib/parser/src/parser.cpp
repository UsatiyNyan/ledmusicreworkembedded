#include "parser.h"
#include "base_exception.h"
#include <iostream>
#include <chrono>


using namespace std::chrono_literals;

constexpr size_t baud = 19200;
constexpr const char * serial_port  = "/dev/ttyUSB0";
//constexpr const char * serial_port  = "/dev/serial0";

namespace parser {
Parser::Parser(container::FixedQueue<clr::RGB> &rgb_queue, Config &config)
    : _connection(serial_port, baud),
      _config(config),
      _rgb_queue(rgb_queue) {
}
void Parser::job() {
    _connection.read_exact(_read_buf.data(), 2);
    uint8_t checksum = _read_buf[0];
    uint8_t flag = _read_buf[1];
    switch (flag) {
        case BASIC:
            parse_basic(checksum);
            break;
        case RGB:
            parse_rgb(checksum);
            break;
        case CIRCLE:
            parse_circle(checksum);
            break;
        case POLYGON:
            parse_polygon(checksum);
            break;
        case BPM:
            parse_bpm(checksum);
            break;
        case ROTATION:
            parse_rotation(checksum);
            break;
        case LENGTH_AND_WIDTH:
            parse_length_and_width(checksum);
            break;
        default: // TODO: FLUSH input data
            _connection.read(_read_buf.data(), 128);
            break;
    }
    _connection.write_exact(_write_buf.data(), 2);
}
void Parser::parse_basic(uint8_t checksum) {
    if ((checksum ^ BASIC) != 0xFF) {
        // TODO: flush
        _connection.read(_read_buf.data(), 128);
        return;
    }
    _config._mode = BASIC;
    _config.changed = BASIC;
}
void Parser::parse_rgb(uint8_t checksum) {
    _connection.read(_read_buf.data(), 3);
    for (size_t i = 0; i < 3; ++i) {
        checksum ^= _read_buf[i];
    }
    if ((checksum ^ RGB) != 0xFF) {
        // TODO:flush
        _connection.read(_read_buf.data(), 128);
        return;
    }
    _rgb_queue.push_back({
        _read_buf[0],
        _read_buf[1],
        _read_buf[2]
        });
}
void Parser::parse_circle(uint8_t checksum) {
    _connection.read(_read_buf.data(), 2);
    for (size_t i = 0; i < 2; ++i) {
        checksum ^= _read_buf[i];
    }
    if ((checksum ^ CIRCLE) != 0xFF) {
        // TODO:flush
        _connection.read(_read_buf.data(), 128);
        return;
    }
    _config._mode = CIRCLE;
    _config._center = {
        static_cast<float>(_read_buf[0]),
        static_cast<float>(_read_buf[1])
    };
    _config.changed = CIRCLE;
}
void Parser::parse_polygon(uint8_t checksum) {
    size_t vertices_amount = _connection.read(_read_buf.data(), 128);
    for (size_t i = 0; i < vertices_amount; ++i) {
        checksum ^= _read_buf[i];
    }
    if ((checksum ^ POLYGON) != 0xFF) {
        // TODO:flush
        _connection.read(_read_buf.data(), 128);
        return;
    }
    vertices_amount /= 2;
    std::vector<geometry::Point> new_vertices(vertices_amount);
    for (size_t i = 0; i < vertices_amount; ++i) {
        new_vertices[i].x = _read_buf[2 * i];
        new_vertices[i].y = _read_buf[2 * i + 1];
    }
    _config._mode = POLYGON;
    _config._vertices = std::move(new_vertices);
    _config.changed = POLYGON;
}
void Parser::parse_bpm(uint8_t checksum) {
    _connection.read(_read_buf.data(), 2);
    for (size_t i = 0; i < 2; ++i) {
        checksum ^= _read_buf[i];
    }
    if ((checksum ^ BPM) != 0xFF) {
        // TODO:flush
        _connection.read(_read_buf.data(), 128);
        return;
    }
    uint16_t bpm = (static_cast<uint16_t>(_read_buf[1]) << 1) | _read_buf[0];
    _config._timeout = std::chrono::milliseconds(60000 / bpm);
    _config.changed = BPM;
}
void Parser::parse_rotation(uint8_t checksum) {
    _connection.read(_read_buf.data(), 1);
    for (size_t i = 0; i < 1; ++i) {
        checksum ^= _read_buf[i];
    }
    if ((checksum ^ ROTATION) != 0xFF) {
        // TODO:flush
        _connection.read(_read_buf.data(), 128);
        return;
    }
    _config._radian = _read_buf[0];
    _config.changed = ROTATION;
}
void Parser::parse_length_and_width(uint8_t checksum) {
    _connection.read(_read_buf.data(), 2);
    for (size_t i = 0; i < 2; ++i) {
        checksum ^= _read_buf[i];
    }
    if ((checksum ^ LENGTH_AND_WIDTH) != 0xFF) {
        // TODO:flush
        _connection.read(_read_buf.data(), 128);
        return;
    }
    _config._length = (static_cast<uint16_t>(_read_buf[1]) << 1) | _read_buf[0];
    _config._width =  (static_cast<uint16_t>(_read_buf[3]) << 1) | _read_buf[2];
    _config.changed = LENGTH_AND_WIDTH;
}
}  // namespace parser