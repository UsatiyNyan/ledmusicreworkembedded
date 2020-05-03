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
        : _data(size) {}

    void push_back(T &&item) {
        std::unique_lock _(_mutex);
        _data.push_back(item);
        _data.pop_front();
    }
    T const &operator[](size_t i) const {
        return _data[i];
    }
    [[nodiscard]] const T &back() const {
        return _data.back();
    }
    [[nodiscard]] size_t size() const {
        return _data.size();
    }
 private:
    std::mutex _mutex;
    std::deque<T> _data;
};
}  // namespace container

#endif //RPI_LED_LIB_FIXED_QUEUE_INCLUDE_FIXED_QUEUE_H_
