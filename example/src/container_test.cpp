//
// Created by kira on 03.05.2020.
//

#include <iostream>
#include "rgb.h"
#include "fixed_queue.h"

int main() {
    container::FixedQueue<int> fixed_queue(10);
    fixed_queue.push_back(1);
    std::cout << fixed_queue.back();
    return 0;
};

