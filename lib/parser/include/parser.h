#ifndef __LIB_UART__
#define __LIB_UART__

#include "serial.h"
#include <string>

namespace parser {
enum class FLAGS : uint8_t {
    BASIC = 0x00,
    CIRCLE = 0x01,
    POLYGON = 0x02,
    BPM = 0x03,
    ROTATION = 0x04,
    RGB = 0xFF
    };
class Parser {
 public:
    Parser(serial::Connection &&connection);
 private:
    serial::Connection _connection;
};
}  // namespace parser

#endif // __LIB_UART__
