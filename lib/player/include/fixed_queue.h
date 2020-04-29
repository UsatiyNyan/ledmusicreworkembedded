//
// Created by kira on 30.11.2019.
//

#ifndef PLAYER_UI_PLAYER_UI_FIXED_QUEUE_H_
#define PLAYER_UI_PLAYER_UI_FIXED_QUEUE_H_

template <typename T>
class fixed_queue {
public:
    explicit fixed_queue(unsigned size);
    ~fixed_queue();

    void push_back(const T& item);
    T &at(unsigned id);

    [[nodiscard]] unsigned size() const;

private:
    unsigned _size;
    T *_data;
    unsigned _front;
    unsigned _back;
    unsigned _current_size;
};


template<typename T>
fixed_queue<T>::fixed_queue(unsigned size) :
    _size(size),
    _data(new T[size]),
    _front(0),
    _back(0),
    _current_size(0) {}

template<typename T>
fixed_queue<T>::~fixed_queue() {
    delete[] _data;
}

template<typename T>
unsigned fixed_queue<T>::size() const {
    return _current_size;
}

template<typename T>
T &fixed_queue<T>::at(unsigned id) {
    return _data[(_front + id) % _size];
}

template<typename T>
void fixed_queue<T>::push_back(const T& item) {
    if ((_back + 1) % _size == _front) {
        delete _data[_front];
        _front = (_front + 1) % _size;
    } else {
        ++_current_size;
    }
    _data[_back] = item;
    _back = (_back + 1) % _size;
}

#endif //PLAYER_UI_PLAYER_UI_FIXED_QUEUE_H_
