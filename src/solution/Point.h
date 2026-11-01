//
// Created by a on 31.10.2026.
//

#ifndef SCORPIO_ZADANIE_REKRUTACYJNE_SOFTWARE_POINT_H
#define SCORPIO_ZADANIE_REKRUTACYJNE_SOFTWARE_POINT_H

namespace solution {

//klasa do matematyki
class Point {
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    int radiusXY = 0;
    int radiusXZ = 0;

    void findRadius ();

    public:

    Point();
    Point(const double x, const double y, const double z);

    double getX ();
    double getY ();
    double getZ ();
    void setX (const double x);
    void setY (const double y);
    void setZ (const double z);
    void setPoint (const double x, const double y, const double z);

    int getRadiusXY ();
    int getRadiusXZ ();
};
} // solution

#endif //SCORPIO_ZADANIE_REKRUTACYJNE_SOFTWARE_POINT_H
