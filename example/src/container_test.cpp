//
// Created by kira on 03.05.2020.
//

#include <iostream>
#include "rgb.h"
#include "fixed_queue.h"

int main() {
    container::FixedQueue<int> fixed_queue(4);
    fixed_queue.push_back(1);
    fixed_queue.push_back(2);
    fixed_queue.push_back(3);
    fixed_queue.push_back(4);
    fixed_queue.push_back(5);
    std::cout << fixed_queue[fixed_queue.size() - 1 - 0] << std::endl;
    std::cout << fixed_queue[fixed_queue.size() - 1 - 1] << std::endl;
    std::cout << fixed_queue[fixed_queue.size() - 1 - 2] << std::endl;
    std::cout << fixed_queue[fixed_queue.size() - 1 - 3] << std::endl;
    std::cout << fixed_queue.at_reversed(0) << std::endl;
    std::cout << fixed_queue.at_reversed(1) << std::endl;
    std::cout << fixed_queue.at_reversed(2) << std::endl;
    std::cout << fixed_queue.at_reversed(3) << std::endl;
    return 0;
};

