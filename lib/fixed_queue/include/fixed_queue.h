//
// Created by kira on 30.04.2020.
//

#ifndef RPI_LED_LIB_FIXED_QUEUE_INCLUDE_FIXED_QUEUE_H_
#define RPI_LED_LIB_FIXED_QUEUE_INCLUDE_FIXED_QUEUE_H_

#include <deque>
#include <vector>
#include <mutex>

namespace container {
template<typename T>
class FixedQueue {
 public:
    explicit FixedQueue(size_t size)
        : _data(size, T()) {}

    void push_back(T &&item) {
        std::unique_lock _(_mutex);
        _data.pop_back();
        _data.push_front(item);
    }
    T const &operator[](size_t i) const {
        return _retriever[i];
    }
    [[nodiscard]] const T &back() const {
        return _data.front();
    }
    [[nodiscard]] size_t size() const {
        return _data.size();
    }
    void update() {
        std::unique_lock _(_mutex);
        _retriever.assign(_data.begin(), _data.end());
    }
 private:
    std::deque<T> _data;
    std::vector<T> _retriever;
    std::mutex _mutex;
};
}  // namespace container

#endif //RPI_LED_LIB_FIXED_QUEUE_INCLUDE_FIXED_QUEUE_H_
