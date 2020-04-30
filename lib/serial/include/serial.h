#ifndef __ARDUINO_SERIAL_LIB_H__
#define __ARDUINO_SERIAL_LIB_H__

#include "file_descriptor.h"
#include <string>

namespace serial {
class Connection {
 public:
    Connection(const std::string &serialport, int baud);
    Connection(Connection &&other) noexcept;

    size_t write(const void *data, size_t size);
    void write_exact(const void *data, size_t size);
    size_t read(void *data, size_t size);
    void read_exact(void *data, size_t size);
    void flush();
 private:
    fd::FileDescriptor _fd;
};
}  // namespace serial
#endif
