#include <cercle.h>
#include <parametres.h>
#include <courbe.h>

#ifndef ROBOT_H
#define ROBOT_H


class Robot
{
public:
    Robot(float rayon);
    Robot(Robot *rbt);
    Robot();
    ~Robot();

    float rayon;
    float vitesse_max;  // vitesse/minute en pixels ou cm
    float vitesse;
    tpVitesses vitessesRoues[3];

    Position *start;
    Position *goal;
    Position *theorique;
    Courbe *courbe;


    /* calcul de la courbe */
    void setPositions(Position *start, Position *goal);
    void setup(Courbes c);
    void calcTrajet(Courbes c);
    void plusCourt();
    void arrondi(float &tps);
    void tempsTrajet();

    /* vitesse */
    void setVitesseMax();
    void setVitesse(float prop);

    /* rayon */
    void setRayon(const float rayon);
    void calcRayon();
    void calcRayon(const float T);

    /* vitesse de chaque roue */
    void setVitesseRoues();

    /* modèle inverse, déplacement théorique */
    void moveTheorique(int phase, const unsigned step);
    void aGauche(float dz);
    void aDroite(float dz);
    void toutDroit(float d);

    /* pwm */
    void setOCRnA(const int phase);

    /* tics */
    void setTicsSeconde(const int phase, const float secondes = 1.0);
};

#endif // ROBOT_H
