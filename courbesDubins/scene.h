#ifndef SCENE_H
#define SCENE_H
#include <QtGui>
#include "./courbes/parametres.h"
#include "./courbes/cercle.h"
#include "./courbes/courbe.h"
#include "graph.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    Scene(QObject *parent = 0);
    ~Scene();
    Graph *graph;
    void repereXY();
    void setupPositions(Position *start, Position *goal);
    void addCourbe(Courbe *courbe, bool justCourbe);
    void setJustCourbe(bool b);
};

#endif // SCENE_H
