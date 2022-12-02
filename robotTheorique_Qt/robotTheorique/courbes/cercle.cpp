#include "cercle.h"
#include <math.h>

Cercle::Cercle(const float x, const float y, const float r) {
    this->x = x;
    this->y = y;
    this->r = r;
}

/*
 * Crée un cercle de courbure de rayon r tangent à la position, à gauche ou à droite
 */
Cercle::Cercle(const Position *p, const float r, const Cotes cote) {
    float z;
    if (cote == GAUCHE)
        z = p->z + PI/2;
    else
        z = p->z - PI/2;

    to0_2PI(z); // ramène z entre 0 et 2*PI

    this->r = r;
    // centre du cercle
    x = p->x + r * cos(z);
    y = p->y + r * sin(z);
}

Cercle::Cercle() {}
Cercle::~Cercle() {}

/*
 * Distance entre les centres de 2 cercles
 */
float Cercle::distanceDesCentres(const Cercle *c) {
    float dx = c->x - x;
    float dy = c->y - y;
    float distance = sqrt((dx*dx)+(dy*dy));
    return distance;
}

/*
 * Point à mi-distance des centres de 2 cercles
 */
Point* Cercle::milieu(const Cercle *c) {
    float dx = c->x - x;
    float dy = c->y - y;
    return new Point(x + dx/2, y +dy/2);
}

/*
 * Pour créer les points de tangence entre deux cercles
 * crée un point sur la circonférence en fonction d'un angle avec l'abcisse
 */
Point* Cercle::pointSurCercle(const float &a) {
    Point *p = new Point;
    p->x = x + r * cos(a);
    p->y = y + r * sin(a);
    return p;
}


/*
 * calcul des distances
*/

/*
 * Renvoi le radian entre 2 points sur le cercle,
 * en fonction du sens de rotation
 * true = sens trigonométrique (counter clock)
 */
float Cercle::radian(const Point *from, const Point *to, bool sens) {
    float alpha = atan2f(from->y-y, from->x-x);
    float beta  = atan2f(to->y-y, to->x-x);

    float arc;
    if (sens == false) {
        if (alpha > beta)
            arc = alpha - beta;
        else
            arc = -alpha - (PI * 2.0) + beta;
    }
    else {
        if (alpha < beta)
            arc = alpha - beta;
        else
            arc = -alpha + (PI * 2.0) + beta;
    }
    if (arc < 0.0)
        arc = -arc;
    return arc;
}

/**/

bool Cercle::operator ==(const Cercle &c) {
    if (x == c.x && y == c.y)
        return true;
    else
        return false;
}
