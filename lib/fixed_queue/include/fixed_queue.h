//
// Created by kira on 30.04.2020.
//

#ifndef RPI_LED_LIB_FIXED_QUEUE_INCLUDE_FIXED_QUEUE_H_
#define RPI_LED_LIB_FIXED_QUEUE_INCLUDE_FIXED_QUEUE_H_

#include <vector>

namespace container {
template<typename T>
class FixedQueue {
 public:
    explicit FixedQueue(size_t size)
        : _data(size, 0) {}

    void push_back(T &&item) {
        if ((_back + 1) % _data.size() == _front) {
            _data[_front] = std::move(item);
            _front = (_front + 1) % _data.size();
        } else {
            ++_current_size;
            _data[_back] = item;
        }
        _back = (_back + 1) % _data.size();
    }
    T &operator[](size_t i) {
        return _data[(_front + i) % _data.size()];
    }
    [[nodiscard]] size_t size() const {
        return _current_size;
    }
 private:
    std::vector<T> _data;
    size_t _front = 0;
    size_t _back = 0;
    size_t _current_size = 0;
};
}  // namespace container

#endif //RPI_LED_LIB_FIXED_QUEUE_INCLUDE_FIXED_QUEUE_H_
