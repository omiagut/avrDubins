/*
 * Parametres regroupe
 * les classes les plus simples,
 * les énumérations,
 * les constantes,
 * afin qu'elles ne soient pas disséminées
 */
#ifndef PARAMETRES_H
#define PARAMETRES_H

#ifndef PI
    const float PI = 3.14159265358979323846264338327;
#endif
const float TIMON = 30.0;
const float RAYON = 120.0;
const float DELTA_X = 5.0;
const float DELTA_Y = 5.0;
const float DELTA_Z = PI/50.0;

enum Cercles {START, GOAL, TANGENT};
enum Cotes {GAUCHE, DROITE};
enum Courbes {RSR, RSL, LSR, LSL, RLR, LRL};

/*
 * ramène une valeur angulaire
 * pour qu'elle soit entre 0 et 2*PI -EPSILON
 */
void to0_2PI(float &a);

struct Point {
    float x;
    float y;
    Point() {
        x=0; y=0;
    }
    Point(const float x, const float y) {
        this->x = x;
        this->y = y;
    }
    void operator=(const Point &p) {
        this->x = p.x;
        this->y = p.y;
    }
};

/*
 * Définition de la position d'un robot :
 * x et y, le centre de son essieu
 * z : l'angle formé par son timon avec l'abcisse
 */
struct Position {
    float x;
    float y;
    float z;
    Position(const float x, const float y, const float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    Position(const Position &_p) {
        x = _p.x;
        y = _p.y;
        z = _p.z;
    }
    void operator=(const Position &p) {
        this->x = p.x;
        this->y = p.y;
        this->z = p.z;
    }

    void deltaX(const float dx) {x += dx;}
    void deltaY(const float dy) {y += dy;}
    void deltaZ(const float dz) {z += dz;}
};

/*
 * Distance que le robot doit parcourir sur l'ensemble
 * arc start, segment ou arc tangent, arc goal
 */
struct Trajet {
    Courbes c;
    float start;
    float tangent;
    float goal;
    Trajet(Courbes c, float start, float tangent, float goal) {
        this->c = c;
        this->start = start;
        this->tangent = tangent;
        this->goal = goal;
    }
    void operator=(const Trajet &t) {
        this->c = t.c;
        this->start = t.start;
        this->tangent = t.tangent;
        this->goal = t.goal;
    }
};

// Données de la fenêtre mainwindow
//taille de la scene
#define SIZE_X 12000
#define SIZE_Y 12000
//position de la fenêtre
#define POS_X  50
#define POS_Y  100
// dimension de la vue
#define WND_X  1200
#define WND_Y  800

// Couleur de fond
#define FOND_COLOR 252,252,214
#define POINT_SIZE 5

#endif // PARAMETRES_H


