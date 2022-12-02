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
    float trajet[3];

    void setC(const Courbes c) {this->c = c;}
    void setNull();
    void setCerclesCourbure(const Position *start, const Position *goal, const float r);
    void setPointsTangence();
    void setup(const Position *start, const Position *goal, const float r);
    bool isValide();

    bool isSensTrigo(Courbes courbe, Cercles cercle);
    void calcTrajet(const Position *start, const Position *goal);
    Courbe* plusCourte(const Position *start, const Position *goal, float r, float &d, Courbes &c);


private:
    void setPointsTangenceExterieurs();
    void setPointsTangenceInterieurs();
    void setCercleTangent();
};

#endif // COURBE_H
