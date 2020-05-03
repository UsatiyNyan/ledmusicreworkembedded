//
// Created by kira on 30.04.2020.
//

#ifndef RPI_LED_LIB_FIXED_QUEUE_INCLUDE_FIXED_QUEUE_H_
#define RPI_LED_LIB_FIXED_QUEUE_INCLUDE_FIXED_QUEUE_H_

#include <vector>
#include <mutex>

namespace container {
template<typename T>
class FixedQueue {
 public:
    explicit FixedQueue(size_t size)
        : _data(size) {}

    void push_back(T &&item) {
        std::unique_lock _(_mutex);
        _data[_back] = std::move(item);
        _back = ++_back % _data.size();
    }
    T const &operator[](size_t i) const {
        return _data[(_back - i - 1) % _data.size()];
    }
    [[nodiscard]] const T &back() const {
        return _data[(_back - 1) % _data.size()];
    }
    [[nodiscard]] size_t size() const {
        return _data.size();
    }
 private:
    std::mutex _mutex;
    std::vector<T> _data;
    size_t _back = 0;
};
}  // namespace container

#endif //RPI_LED_LIB_FIXED_QUEUE_INCLUDE_FIXED_QUEUE_H_
