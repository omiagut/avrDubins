/*
 * Définit une courbe de Leister Dubins
 * c : RSR..LRL
 * valide : conserve la valeur renvoyée par isValide
 * isValide dit si une courbe existe en fonction des positions de départ et d'arrivée
 *
 * courbureStart : le cercle de courbure tangent à la position de départ
 * courbureGoal : le cercle de courbure tangent à la position d'arrivée
 * tangenceStart : le point de départ du segment ou du cercle tangent
 * tangenceGoal : le point d'arrivée du segment ou du cercle tangent
 * cercleTangent : le cercle tangent des courbes RLR et RLR
 */
#ifndef COURBE_H
#define COURBE_H
#include <stdio.h>
#include "parametres.h"
#include "cercle.h"


class Courbe
{
public:
    Courbe(Courbes c);
    Courbe();
    ~Courbe();

    Courbes c;
    bool valide;
    Cercle *courbureStart;
    Cercle *courbureGoal;
    Cercle *cercleTangent;
    Point *tangenceStart;
    Point *tangenceGoal;

    void setC(const Courbes c) {this->c = c;}
    void setNull();
    void setCerclesCourbure(const Position *start, const Position *goal, const float r);
    void setPointsTangence();
    void setup(const Position *start, const Position *goal, const float r);
    bool isValide();

    bool isSensTrigo(Courbes courbe, Cercles cercle);
    Trajet distance(const Position *start, const Position *goal);
    Trajet plusCourte(const Position *start, const Position *goal, float r, float &d, Courbes &c);

private:
    void setPointsTangenceExterieurs();
    void setPointsTangenceInterieurs();
    void setCercleTangent();
};

#endif // COURBE_H
