/*
 * A la courbe de Dubins, la classe Robot introduit des notions essentielles aux calculs
 * d' odométrie : l'entraxe et la vitesse
 * De plus c'est le robot qui décide du rayon de courbure, en fonction de ses caractéristiques
 * La position théorique est la position, telle qu'elle évolue de start à goal, en utilisant le
 * modèle inverse de calcul du pdf "Odométrie"
 */

#ifndef ROBOT_H
#define ROBOT_H
#include "courbes/parametres.h"
#include "courbes/courbe.h"
#include "calculs.h"

class Robot
{
public:
    Robot(float rayon);
    Robot(Robot *rbt);
    Robot();
    ~Robot();

    Courbe *courbe;
    Position *start;
    Position *goal;

    float rayon;
    float vitesse_max;  // vitesse/minute en pixels ou cm
    float vitesse;
    tpVitesses vitessesRoues[3];

    Position *theorique;

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
    void calcRayon(const float T);

    /* vitesse de chaque roue */
    void setVitesseRoues();

    /* modèle inverse, déplacement théorique */
    void moveTheorique(const int phase, const uint16_t step);
    void aGauche(float dz);
    void aDroite(float dz);
    void toutDroit(float d);

    /* pwm */
    void setOCRnA(const int phase);

    /* tics */
    void setTicsSeconde(const int phase, const float secondes = 1.0);
};

#endif // ROBOT_H
