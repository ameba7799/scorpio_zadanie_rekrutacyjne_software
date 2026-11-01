//
// Created by a on 1.11.2026.
//

#ifndef SCORPIO_ZADANIE_REKRUTACYJNE_SOFTWARE_MYQUEUE_H
#define SCORPIO_ZADANIE_REKRUTACYJNE_SOFTWARE_MYQUEUE_H
#include <queue>
#include <string>
#include <rclcpp/logger.hpp>

#include "Point.h"

namespace solution {
class MyQueue {
public:
    std::queue<Point> q;
    int countCorrectXY = 0;
    int countCorrectXZ = 0;

    bool check();
    void pop();

    public:

    MyQueue(Point p);
    MyQueue();

    void push(Point p);
    Point front();
    bool checkXY(int rad);
    bool checkXZ(int rad);
};
} // solution

#endif //SCORPIO_ZADANIE_REKRUTACYJNE_SOFTWARE_MYQUEUE_H
