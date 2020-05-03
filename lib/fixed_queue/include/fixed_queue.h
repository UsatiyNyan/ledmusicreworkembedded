//
// Created by kira on 30.04.2020.
//

#ifndef RPI_LED_LIB_FIXED_QUEUE_INCLUDE_FIXED_QUEUE_H_
#define RPI_LED_LIB_FIXED_QUEUE_INCLUDE_FIXED_QUEUE_H_

#include <deque>
#include <mutex>

namespace container {
template<typename T>
class FixedQueue {
 public:
    explicit FixedQueue(size_t size)
        : _size(size) {}

    void push_back(T &&item) {
        std::unique_lock _(_mutex);
        _data.push_back(item);
        if (_data.size() == _size + 1) {
            _data.pop_front();
        }
    }
    T const &operator[](size_t i) const {
        return _data[i];
    }
    T const &at_reversed(size_t i) const {
        return _data[_data.size() - 1 - i];
    }
    [[nodiscard]] const T &back() const {
        return _data.back();
    }
    [[nodiscard]] size_t size() const {
        return _data.size();
    }
 private:
    std::mutex _mutex;
    size_t _size;
    std::deque<T> _data;
};
}  // namespace container

#endif //RPI_LED_LIB_FIXED_QUEUE_INCLUDE_FIXED_QUEUE_H_
