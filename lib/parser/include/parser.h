#ifndef __LIB_UART__
#define __LIB_UART__

#include "serial.h"
#include "config.h"
#include <string>

namespace parser {
class Parser {
 public:
    explicit Parser(serial::Connection &&connection, Config &config);

 private:
    clr::RGB _rgb{};
    Config &_config;
    serial::Connection _connection;
};
}  // namespace parser

#endif // __LIB_UART__
