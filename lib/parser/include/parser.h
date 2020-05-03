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
    void retrieve_data();
    void check_sum();

    void parse_basic();
    void parse_rgb();
    void parse_circle();
    void parse_polygon();
    void parse_bpm();
    void parse_rotation();
    void parse_length_and_width();

    void job() override;

    container::FixedQueue<clr::RGB> &_rgb_queue;
    Config &_config;
    serial::Connection _connection;
    std::vector<uint8_t> _read_buf{128};
    std::vector<uint8_t> _write_buf = {'<', '>'};
};
}  // namespace parser

#endif // __LIB_UART__
