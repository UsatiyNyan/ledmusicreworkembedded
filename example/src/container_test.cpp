//
// Created by kira on 03.05.2020.
//

#include <iostream>
#include "rgb.h"
#include "fixed_queue.h"

int main() {
    container::FixedQueue<int> fixed_queue(4);
    fixed_queue.push_back(0);
    fixed_queue.push_back(1);
    fixed_queue.push_back(2);
    fixed_queue.push_back(3);
    for (uint8_t i = 4; i < 100; ++i) {
        fixed_queue.push_back(i);
        std::cout << "--------------------------" << std::endl;
        std::cout << fixed_queue[0] << std::endl;
        std::cout << fixed_queue[1] << std::endl;
        std::cout << fixed_queue[2] << std::endl;
        std::cout << fixed_queue[3] << std::endl;
        std::cout << "==========================" << std::endl;
        std::cout << fixed_queue.at_reversed(0) << std::endl;
        std::cout << fixed_queue.at_reversed(1) << std::endl;
        std::cout << fixed_queue.at_reversed(2) << std::endl;
        std::cout << fixed_queue.at_reversed(3) << std::endl;
        std::cout << "++++++++++++++++++++++++++" << std::endl;
        std::cout << fixed_queue.size() << std::endl;
        std::cout << "++++++++++++++++++++++++++" << std::endl;
    }

    return 0;
};

