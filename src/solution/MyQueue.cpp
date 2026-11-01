//
// Created by a on 1.11.2026.
//

#include "MyQueue.h"

#include <cmath>
#include <rclcpp/logging.hpp>

namespace solution {

//magiczne numerki
#define POW12 4096
#define RANGE 3 //jak daleko może być od celu
#define ITERATIONS 5 //przez ile iteracji ma być w zakresie

    MyQueue::MyQueue() : MyQueue(Point(1,0,0)) {
        countCorrectXY = ITERATIONS;
        countCorrectXZ = ITERATIONS;
    }
    MyQueue::MyQueue(Point point) { q.push(point); }

    void MyQueue::push(Point p) { q.push(p); }
    Point MyQueue::front() { return q.front(); }

    //spracdza czy można zwiękrzyć licznik trafień XY
    bool MyQueue::checkXY(const int rad) {
        int dif = abs(q.front().getRadiusXY() - rad);

        if (dif <= RANGE || (POW12-dif) <= RANGE) {
            countCorrectXY++;
            if (check()) {pop();} //ewentualne przejście do nowego elementu
            return true;
        } else {
            countCorrectXY = 0;
            return false;
        }
    }
    //spracdza czy można zwiękrzyć licznik trafień XZ
    bool MyQueue::checkXZ(const int rad) {
        int dif = abs(q.front().getRadiusXZ() - rad);

        if (dif <= RANGE || (POW12-dif) <= RANGE) {
            countCorrectXZ++;
            if (check()) {pop();} //ewentualne przejście do nowego elementu
            return true;
        } else {
            countCorrectXZ = 0;
            return false;
        }
    }

    bool MyQueue::check() {
        return(countCorrectXY >= ITERATIONS && countCorrectXZ >= ITERATIONS && q.size() > 1);
    }

    void MyQueue::pop() {
        q.pop();
        countCorrectXY = 0;
        countCorrectXZ = 0;
    }

} // solution