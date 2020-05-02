#ifndef __LIB_UART__
#define __LIB_UART__

#include "serial.h"
#include "config.h"
#include "job_thread.h"
#include "rgb.h"
#include "fixed_queue.h"
#include <string>

namespace parser {
class Parser : public executor::JobThread {
 public:
    explicit Parser(container::FixedQueue<clr::RGB> &rgb_queue, Config &config);

 private:
    void parse_basic(uint8_t checksum);
    void parse_rgb(uint8_t checksum);
    void parse_circle(uint8_t checksum);
    void parse_polygon(uint8_t checksum);
    void parse_bpm(uint8_t checksum);
    void parse_rotation(uint8_t checksum);
    void parse_length_and_width(uint8_t checksum);

    void job() override;

    container::FixedQueue<clr::RGB> &_rgb_queue;
    Config &_config;
    serial::Connection _connection;
    std::vector<uint8_t> _read_buf{128};
    std::vector<uint8_t> _write_buf = {'<', '>'};
};
}  // namespace parser

#endif // __LIB_UART__
