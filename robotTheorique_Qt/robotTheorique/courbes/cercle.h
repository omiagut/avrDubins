#ifndef CERCLE_H
#define CERCLE_H
#include "parametres.h"

class Cercle
{
public:
    Cercle(const float x, const float y, const float r);
    Cercle(const Position *p, const float r, const Cotes co);
    Cercle();
    ~Cercle();

    float x;
    float y;
    float r;

    Point* pointSurCercle(const float &a);
    Point* milieu(const Cercle *c);
    float distanceDesCentres(const Cercle *c);

    float radian(const Point *from, const Point *to, bool sens);

    bool operator==(const Cercle &c);
};

#endif // CERCLE_H
