//
// Created by kira on 03.05.2020.
//

#include <iostream>
#include "rgb.h"
#include "fixed_queue.h"
#include "circle.h"

int main() {
    container::FixedQueue<int> fixed_queue(4);
    for (uint8_t i = 0; i < 100; ++i) {
        fixed_queue.push_back(i);
        std::cout << "--------------------------" << std::endl;
        std::cout << fixed_queue[0] << std::endl;
        std::cout << fixed_queue[1] << std::endl;
        std::cout << fixed_queue[2] << std::endl;
        std::cout << fixed_queue[3] << std::endl;
        std::cout << "++++++++++++++++++++++++++" << std::endl;
        std::cout << fixed_queue.size() << std::endl;
        std::cout << "++++++++++++++++++++++++++" << std::endl;
    }
    geometry::Circles circles({0, 0}, 10);
    for (uint8_t i = 0; i < 10; ++i) {
        std::cout << "xxxxxxxxxxxxxxxxxxxxxxxxxx" << std::endl;
        std::cout << circles[i].get_radius() << std::endl;
    }

    return 0;
};

