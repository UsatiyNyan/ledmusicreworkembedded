//
// Created by kira on 30.04.2020.
//

#ifndef RPI_LED_LIB_PARSER_INCLUDE_CONFIG_H_
#define RPI_LED_LIB_PARSER_INCLUDE_CONFIG_H_

#include <atomic>
#include "rgb.h"

namespace parser {
enum FLAGS : uint8_t {
    BASIC = 0x00,
    CIRCLE = 0x01,
    POLYGON = 0x02,
    BPM = 0x03,
    ROTATION = 0x04,
    LENGTH_AND_WIDTH = 0x05,
    RGB = 0xFF
};
constexpr uint8_t NOTHING_CHANGED = 0xFF;
class Config {
 public:
    Config() = default;
    [[nodiscard]] uint8_t get_mode() const;
 private:
    uint8_t _mode = FLAGS::BASIC;
    float _radian = 0;
    uint16_t _bpm = 80;
    std::atomic<uint8_t> _changed = NOTHING_CHANGED;
};
}  // namespace parser

#endif //RPI_LED_LIB_PARSER_INCLUDE_CONFIG_H_
