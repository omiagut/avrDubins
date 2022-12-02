#include "robot.h"
#include "courbes/cercle.h"
#include <math.h>
#include <iomanip>
#include <iostream>
using namespace std;

Robot::Robot(float rayon) {
    this->rayon = rayon;
    setVitesseMax(); // vitesse/minute
    courbe = NULL;
    theorique = NULL;
}

Robot::Robot(Robot *rbt) {
    rayon = rbt->rayon;
    vitesse_max = rbt->vitesse_max;
    vitesse = rbt->vitesse;
}

Robot::Robot() {}
Robot::~Robot() {}


/* ----------------------------------------------------------
 * calcul de la courbe
*/
void Robot::setPositions(Position *start, Position *goal) {
    this->start = start;
    this->goal = goal;
}

void Robot::setup(Courbes c) {
    delete courbe;
    courbe = new Courbe(c);
    courbe->setup(start, goal, rayon);
}

/*
 * Calcul de la courbe c (RSR..LRL)
 */
void Robot::calcTrajet(Courbes c) {
    setup(c);
    courbe->calcTrajet(start, goal);
}

void Robot::plusCourt() {
    delete courbe;
    courbe = new Courbe;
    float dst = INFINITY;
    Courbes c = RSR;
    courbe = courbe->plusCourte(start, goal, rayon, dst, c);
}

void Robot::arrondi(float &tps) {
    if (tps - floor(tps) > 0.5)
        tps = ceil(tps);
    else
        tps = floor(tps);
}

/*
 * Temps mis pour chaque phase du trajet sur la courbe
 * Ici l'on suppose que la vitesse en ligne droite est différente
 * de la vitesse en courbe
 */
void Robot::tempsTrajet() {
    if (!courbe->valide) {
        for (int i=START; i<= GOAL; ++i)
            courbe->trajet[i] = INFINITY;
        return;
    }

    float ms = 60000.0;
    courbe->trajet[START] = courbe->trajet[START] / vitesse * ms;
    arrondi(courbe->trajet[START]);

    if (courbe->c < RLR)
        //courbe->trajet[TANGENT] = courbe->trajet[TANGENT] / (vitesse_max * LIGNE_DROITE) * ms;
        courbe->trajet[TANGENT] = courbe->trajet[TANGENT] / vitesse* ms;
    else
        courbe->trajet[TANGENT] = courbe->trajet[TANGENT] / vitesse * ms;
    arrondi(courbe->trajet[TANGENT]);

    courbe->trajet[GOAL] = courbe->trajet[GOAL] / vitesse * ms;
    arrondi(courbe->trajet[GOAL]);
}


/* --------------------------------------------------
 * Initialisation de la vitesse (cm/minute)
 */
void Robot::setVitesseMax() {
    vitesse_max = RPM * DIAMETRE * PI;
}

/*
 * vitesse arbitraire, proportionnelle à la vitesse max
 */
void Robot::setVitesse(float prop) {
    vitesse = vitesse_max * prop;
}


/* ---------------------------------------------------
 * Initialisation arbitraire du rayon
*/
void Robot::setRayon(const float rayon) {
    this->rayon = rayon;
}

/*
 * On pourrait aussi determiner le rayon en fonction de la période,
 * c'est à dire lier rayon à vitesse angulaire que l'on peut atteindre
 * La période T = 2 * PI * Rayon / v
 * => Rayon = (T * v) / (2 * PI)
 */
void Robot::calcRayon(const float T) {
    rayon = (T * vitesse) / ( 2 * PI);
}

/* -----------------------------------------------------
 * Transformation de la vitesse du robot en vitesse
 * de la roue lente et de la roue rapide
 * si R = (entraxe / 2) * (vg + vd) / (vd - vg)
 *        vitesse roue rapide = v + delta, roue lente = v - delta
 * => R = (entraxe / 2) * ((v + delta) + (v - delta)) / ((v + delta) - (v - delta))
 * => R = (entraxe / 2) * (2 * v) / (2 * delta)
 * => R = (entraxe / 2) * v / delta
 * => ../..
 * => delta = (e * v) / (2 * R)
 */
void Robot::setVitesseRoues() {
    float delta = (vitesse * ENTRAXE) / (2.0 * rayon);
    float lente = vitesse - delta;
    float rapide = vitesse + delta;

    for (int i = START; i <= GOAL; ++i) {
        switch(i) {
        case START:
            if (courbe->c == RSR || courbe->c == RSL || courbe->c == RLR) { // start à droite
                vitessesRoues[START].roueDroite = lente;
                vitessesRoues[START].roueGauche = rapide;
            }
            else { // start à gauche
                vitessesRoues[START].roueDroite = rapide;
                vitessesRoues[START].roueGauche = lente;
            }
            break;
        case TANGENT:
            if (courbe->c == RLR) { // cercle tangent à gauche
                vitessesRoues[TANGENT].roueDroite = rapide;
                vitessesRoues[TANGENT].roueGauche = lente;
            }
            else {  // cercle tangent à droite
                if (courbe->c == LRL) {
                    vitessesRoues[TANGENT].roueDroite = lente;
                    vitessesRoues[TANGENT].roueGauche= rapide;
                }
                else { // segment tangent
                    //vitessesRoues[TANGENT].roueDroite = vitesse_max * LIGNE_DROITE;
                    //vitessesRoues[TANGENT].roueGauche = vitesse_max * LIGNE_DROITE;
                    // normalement, la vitesse est constante ...
                    vitessesRoues[TANGENT].roueDroite = vitesse;
                    vitessesRoues[TANGENT].roueGauche = vitesse;
                }
            }
            break;
        case GOAL:
            if (courbe->c == RSR || courbe->c == LSR || courbe->c == RLR) { // goal à droite
                vitessesRoues[GOAL].roueDroite = lente;
                vitessesRoues[GOAL].roueGauche = rapide;
            }
            else { // goal à gauche
                vitessesRoues[GOAL].roueDroite = rapide;
                vitessesRoues[GOAL].roueGauche = lente;
            }
        }
        setOCRnA(i);
        setTicsSeconde(i);
    }
}


/*
 * Le modèle inverse permet de calculer la position théorique
 * à tout endroit sur la courbe
 * C'est la fonction appelée toutes les secondes par mainwindow::moveTheorique,
 * qui déplace la position théorique du robot sur la courbe
*/
void Robot::moveTheorique(int phase, const uint16_t step) {
    float d;        // distance en 1 seconde ou restante
    float dz;       // distance angulaire

    if (vitessesRoues[phase].roueDroite == vitessesRoues[phase].roueGauche) { // ligne droite
        //d = vitesse_max * LIGNE_DROITE / 60.0 / 1000.0 * (float) step;
        // normalement, la vitesse est constante ...
        d = vitesse / 60.0 / 1000.0 * (float) step;
        toutDroit(d);
    }
    else { // tourne
        d = vitesse / 60.0 / 1000.0 * (float) step;
        dz = d/rayon;
        if (vitessesRoues[phase].roueDroite < vitessesRoues[phase].roueGauche)
            aDroite(dz);
        else
            aGauche(dz);       
    }
}

/*
 * la nouvelle position theorique est un point sur un cercle
 * dont le centre est l'ancienne position
 * dont le rayon est le déplacement.
 * theorique->z, la pente du segment, ne change pas
 */
void Robot::toutDroit(float d) {
    Cercle *c = new Cercle(theorique->x, theorique->y, d);
    Point *p = c->pointSurCercle(theorique->z);
    theorique->x = p->x;
    theorique->y = p->y;
}

void Robot::aDroite(float dz) {
    // coordonnées du centre du cercle de courbure
    float x0 = theorique->x - (rayon * cos(theorique->z + PI/2.0));
    float y0 = theorique->y - (rayon * sin(theorique->z + PI/2.0));
    // nouvelle position
    theorique->z -= dz;
    theorique->x = x0 + (rayon * cos(theorique->z + PI/2.0));
    theorique->y = y0 + (rayon * sin(theorique->z + PI/2.0));
}

void Robot::aGauche(float dz) {
    // coordonnées du centre du cercle de courbure
    float x0 = theorique->x - (rayon * cos(theorique->z - PI/2.0));
    float y0 = theorique->y - (rayon * sin(theorique->z - PI/2.0));
    // nouvelle position
    theorique->z += dz;
    theorique->x = x0 + (rayon * cos(theorique->z - PI/2.0));
    theorique->y = y0 + (rayon * sin(theorique->z - PI/2.0));
}

/*
 * Quand on connaît la vitesse de chaque roue par phase, il est facile de calculer :
 * - la PWM théorique à laquelle cette vitesse correspond
 * - la valeur que les encodeurs devraient théoriquement renvoyer
 */

/* pwm théorique */
void Robot::setOCRnA(const int phase) {
    float _ocr0A = (float) 256 / vitesse_max * vitessesRoues[phase].roueDroite;
    float _ocr2A = (float) 256 / vitesse_max * vitessesRoues[phase].roueGauche;
    arrondi(_ocr0A);
    arrondi(_ocr2A);
    vitessesRoues[phase].ocr0A = (uint8_t) _ocr0A;
    vitessesRoues[phase].ocr2A = (uint8_t) _ocr2A;
}

/*
 * nombre de tics théorique des encodeurs / seconde (ou secondes)
 * Distance parcourue à la seconde / circonférence * nb de tics sur un tour
 */
void Robot::setTicsSeconde(const int phase, const float secondes) {
    float distanceSeconde;

    /* roue droite */
    distanceSeconde = vitessesRoues[phase].roueDroite / 60.0 * secondes;
    vitessesRoues[phase].ticsDroite = (uint16_t) distanceSeconde / (DIAMETRE * PI) * TICS;

    /* roue gauche */
    distanceSeconde = vitessesRoues[phase].roueGauche / 60.0 * secondes;
    vitessesRoues[phase].ticsGauche =  (uint16_t) distanceSeconde / (DIAMETRE * PI) * TICS;
}

void Robot::





