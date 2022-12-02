#include "courbe.h"
#include <math.h>

Courbe::Courbe(Courbes c) {
    this->c = c;
}

Courbe::Courbe() {}
Courbe::~Courbe() {}

void Courbe::setNull() {
    courbureStart = NULL;
    courbureGoal = NULL;
    cercleTangent = NULL;
    tangenceStart = NULL;
    tangenceGoal = NULL;
}

void Courbe::setCerclesCourbure(const Position *start, const Position *goal, const float r) {
    switch (c) {
    case RSR :
    case RLR :
        courbureStart = new Cercle(start, r, DROITE);
        courbureGoal = new Cercle(goal, r, DROITE);
        break;
    case RSL :
        courbureStart = new Cercle(start, r, DROITE);
        courbureGoal = new Cercle(goal, r, GAUCHE);
        break;
    case LSR :
        courbureStart = new Cercle(start, r, GAUCHE);
        courbureGoal = new Cercle(goal, r, DROITE);
        break;
    case LSL :
    case LRL :
        courbureStart = new Cercle(start, r, GAUCHE);
        courbureGoal = new Cercle(goal, r, GAUCHE);
        break;       
    default :
        ;
    }
}

void Courbe::setPointsTangence() {
    if (!isValide())
        return;

    switch (c) {
    case RSR :
    case LSL :
        setPointsTangenceExterieurs();
        break;
    case RSL :
    case LSR :
        setPointsTangenceInterieurs();
        break;
    case RLR :
    case LRL :
        setCercleTangent();
        break;
    }
}

void  Courbe::setup(const Position *start, const Position *goal, const float r) {
    setNull();
    setCerclesCourbure(start, goal, r);
    setPointsTangence();
}

bool Courbe::isValide() {
    valide = true;
    if (*courbureStart == *courbureGoal)
        valide = false;

    switch (c) {
    case RSL:
    case LSR:
        /* les cercles
         * se croisent -> pas de tangente intérieure
         * se touchent en un point -> pas de changement de position
         */
        if (courbureStart->distanceDesCentres(courbureGoal) <= courbureStart->r*2.0)
            valide = false;
        break;
    case RLR:
    case LRL:
        // le cercle tangent ne touche pas les cercles de courbure -> pas de tangence
        if (courbureStart->distanceDesCentres(courbureGoal) > courbureStart->r*4.0)
            valide = false;
    default:
        ;
    }
    return valide;
}


/*
 * Le segment tangent est parallèle au segment reliant les centres des cercles de courbure
 * Les rayons portant les points de tangence sont perpendiculaires
 * au segment reliant les centres des cercles de courbure
 */
void Courbe::setPointsTangenceExterieurs() {
    // pente du segment reliant les centres
    float pente = atan2f((courbureGoal->y - courbureStart->y),
                         (courbureGoal->x - courbureStart->x));
    if (c == RSR) {
        tangenceStart = courbureStart->pointSurCercle(pente + PI/2.0);
        tangenceGoal = courbureGoal->pointSurCercle(pente + PI/2.0);
    }
    else { // LSL
        tangenceStart = courbureStart->pointSurCercle(pente - PI/2.0);
        tangenceGoal = courbureGoal->pointSurCercle(pente - PI/2.0);
    }
}

/*
 * Sommets du triangle de calcul :
 *  point milieu du segment reliant les centres (hypothénuse)
 *  centre du cercle de courbure (angle hypothenuse rayon)
 *  point de tangence (donc angle de 90°)
 *
 * PI : le résultat de atan2 est orienté. C'est l'angle formé par le segment avec l'abcisse.
 * Le point d'origine est soit A, soit B.
 * Si la valeur renvoyée pour un segment AB est beta, pour le segment BA atan2 renvoie beta+PI
 */
void Courbe::setPointsTangenceInterieurs() {
    float pente = atan2f((courbureGoal->y - courbureStart->y),
                         (courbureGoal->x - courbureStart->x));
    float hypothenuse = courbureStart->distanceDesCentres(courbureGoal)/2.0;
    // angle dont le sommet = centre du cercle de courbure, côtés = segment des centres et rayon
    float angleHypothenuseRayon = acos(courbureStart->r/hypothenuse);
    if (c == RSL) {
        tangenceStart = courbureStart->pointSurCercle(pente+angleHypothenuseRayon);
        tangenceGoal = courbureGoal->pointSurCercle(pente+angleHypothenuseRayon+PI);
    }
    else { // LSR
        tangenceStart = courbureStart->pointSurCercle(pente-angleHypothenuseRayon);
        tangenceGoal = courbureGoal->pointSurCercle(pente-angleHypothenuseRayon+PI);
    }
}

/*
 * Sommets du triangle de calcul :
 *  point milieu du segment reliant les centres des cercles de courbure
 *  centre du cercle de courbure
 *  centre du cercle tangent
 *
 * L'hypothénuse du triangle de calcul est le segment reliant le centre du cercle
 * de courbure au centre du cercle tangent ( = rayon*2)
 */
void Courbe::setCercleTangent() {
    float pente = atan2f((courbureGoal->y - courbureStart->y),
                         (courbureGoal->x - courbureStart->x));

    float hypothenuse = courbureStart->r*2.0;
    float angle = acos(courbureStart->distanceDesCentres(courbureGoal)/2/hypothenuse);
    Point *centre = NULL;
    // par commodité, avant d'être positionné le cercleTangent sert à calculer son propre centre
    cercleTangent = new Cercle(courbureStart->x, courbureStart->y, courbureStart->r*2);

    if (c == RLR) {
        centre = cercleTangent->pointSurCercle(pente - angle);
        tangenceStart = courbureStart->pointSurCercle(pente - angle);
        tangenceGoal = courbureGoal->pointSurCercle(pente - PI + angle);
    }
    else {
        centre = cercleTangent->pointSurCercle(pente + angle);
        tangenceStart = courbureStart->pointSurCercle(pente + angle);
        tangenceGoal = courbureGoal->pointSurCercle(pente - PI - angle);
    }
    // le cercleTangent a calculé son centre, il est détruit puis positionné
    delete cercleTangent;
    cercleTangent = new Cercle(centre->x, centre->y, courbureStart->r);
}


/*
 * calcul des distances (en pixels)
*/
/*
 * Renvoie true si le robot tourne sur son cercle de courbure
 * dans le sens inverse des aiguilles d'une montre
 * (sens trigonométrique)
 */
bool Courbe::isSensTrigo(Courbes courbe, Cercles cercle) {
    bool b;
    switch (courbe) {
        case RSR :
            b = false;
            break;
        case LSL :
            b = true;
            break;
        case RSL :
            if (cercle == START)
                b = false;
            else
                b = true;
            break;
        case LSR :
            if (cercle == START)
                b = true;
            else
                b = false;
            break;
        case RLR :
            if ((cercle == START) || (cercle == GOAL))
                b = false;
            else    // TANGENT
                b = true;
            break;
        case LRL :
            if ((cercle == START) || (cercle == GOAL))
                b = true;
            else    // TANGENT
                b = false;
        default :
            break;
    }
    return b;
}

/*
 * distance à parcourir sur une courbe
 */
void Courbe::calcTrajet(const Position *start, const Position *goal) {
    if (!valide)
        return;

    Point *s = new Point(start->x, start->y);
    Point *g = new Point(goal->x, goal->y);
    trajet[START] = courbureStart->radian(s, tangenceStart, isSensTrigo(c, START));
    trajet[GOAL] = courbureGoal->radian(tangenceGoal, g, isSensTrigo(c, GOAL));
    trajet[TANGENT] = 0.0;
    if (c < RLR) {
        float dx = tangenceGoal->x - tangenceStart->x;
        float dy = tangenceGoal->y - tangenceStart->y;
        trajet[TANGENT] = sqrt(dx * dx + dy * dy);
    }
    else {
        trajet[TANGENT] = cercleTangent->radian(tangenceStart, tangenceGoal, isSensTrigo(c, TANGENT));
        trajet[TANGENT] *= cercleTangent->r;
    }

    trajet[START] *= courbureStart->r;
    trajet[GOAL] *= courbureGoal->r;
}

Courbe* Courbe::plusCourte(const Position *start, const Position *goal, float r, float &d, Courbes &c) {
    Courbe *crb = new Courbe;
    float dst = d;
    setC(c);
    int cc = (int) this->c;
    do {
        setup(start, goal, r);
        calcTrajet(start, goal);
        dst = trajet[START] + trajet[TANGENT] + trajet[GOAL];
        if (dst < d) {
            d = dst;
            *crb = *this;
        }
        cc++;
        setC((Courbes) cc);
    } while (cc <= LRL);
    return crb;
}

