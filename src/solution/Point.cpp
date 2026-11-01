//
// Created by a on 31.10.2026.
//

#include "Point.h"
#include <cmath>
#include <iostream>

#include "tester.hpp"

#define POW12 4096
#define POW11 2048

namespace solution {
    Point::Point() {}
    Point::Point(const double x, const double y, const double z) : x(x), y(y), z(z) {
        findRadius();
    }

    double Point::getX() { return x; }
    double Point::getY() { return y; }
    double Point::getZ() { return z; }

    void Point::setX(const double x) {
        this->x = x;
        findRadius();
    }

    void Point::setY(const double y) {
        this->y = y;
        findRadius();
    }

    void Point::setZ(const double z) {
        this->z = z;
        findRadius();
    }

    void Point::setPoint(const double x, const double y, const double z) {
        this->x = x;
        this->y = y;
        this->z = z;
        findRadius();
    }

    //znajduje potrzebne kąty
    void Point::findRadius() {
        radiusXY = int (atan2 (y, x) * POW11 / M_PI);
        if (radiusXY < 0) { radiusXY += POW12; }

        radiusXZ = int (atan2 (z, x) * POW11 / M_PI);
        if (radiusXZ < 0) { radiusXZ += POW12; }
    }

    int Point::getRadiusXY() { return radiusXY; }
    int Point::getRadiusXZ() { return radiusXZ; }
} // solution