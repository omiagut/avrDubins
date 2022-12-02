/*
 * Définit ce que son nom indique
 * x et y : coordonnées du centre
 * r : rayon
 *
 * Le second constructeur crée un cercle
 * - perpendiculaire au z de la position
 * - à droite ou à gauche
 *
 * Point sur le cercle renvoie un point situé sur la circonférence,
 * à l'extrémité d'un rayon formant un angle a avec l' abcisse
 *
 * milieu renvoie un point au milieu du segment reliant
 * les centre de ce cercle au centre du cercle c
 *
 * distance des centres renvoie la distance entre le centre de ce cercle
 * et le centre du cercle c (en pixels)
 *
 * radian renvoie le radian entre deux points sur la circonférence du cercle,
 * en fonction du sens de rotation
 */
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
