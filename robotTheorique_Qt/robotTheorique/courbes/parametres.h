#ifndef PARAMETRES_H
#define PARAMETRES_H

#define uint8_t unsigned short
#define uint16_t unsigned int

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

#ifndef PI
    const float PI = 3.14159265358979323846264338327;
#endif
const float TIMON = 30.0;
const float RAYON = 120.0;
const float DELTA_X = 5.0;
const float DELTA_Y = 5.0;
const float DELTA_Z = PI/50.0;

enum Cercles {START, TANGENT, GOAL};
enum Cotes {GAUCHE, DROITE};
enum Courbes {RSR, RSL, LSR, LSL, RLR, LRL};

/*
 * ramène une valeur angulaire
 * pour qu'elle soit entre 0 et 2*PI
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

struct Position {
    float x;
    float y;
    float z;
    Position(const float x, const float y, const float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    Position(const Position &p) {
        x = p.x;
        y = p.y;
        z = p.z;
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


/* Robot */
const float ENTRAXE = 19.0;     // l'essieu en cm
const float DIAMETRE = 8.0;     // diamètre des roues en cm
const float RPM = 110.0;        // tours/minute

typedef struct {
    float roueGauche;           // vitesse théorique des roues en cm/miniute
    float roueDroite;
    uint8_t ocr2A;       // réglage PWM théorique
    uint8_t ocr0A;
    uint16_t ticsGauche;    // nombre de tics que devraient renvoyer par les encodeurs/seconde
    uint16_t ticsDroite;
} tpVitesses;

/* coefficient tel que vitesse en ligne droite = vitesse_max * LIGNE_DROITE */
const float LIGNE_DROITE = 0.85;
const uint16_t TICS = 15;   // tics / tour de roue
#endif // PARAMETRES_H


