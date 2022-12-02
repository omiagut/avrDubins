#include "scene.h"
#include "./courbes/parametres.h"
#include <iostream>
#include <iomanip>
using namespace std;

Scene::Scene(QObject *parent) : QGraphicsScene(parent)  
{
    graph = NULL;
}

Scene::~Scene() {
}

/**/
void Scene::repereXY() {
    QGraphicsLineItem *abcisse = new QGraphicsLineItem;
    abcisse->setLine(QLineF(-SIZE_X/2, 0, SIZE_X/2, 0));
    QGraphicsLineItem *ordonnee = new QGraphicsLineItem;
    ordonnee->setLine(QLineF(0, -SIZE_Y/2, 0, SIZE_Y/2));
    addItem(abcisse);
    addItem(ordonnee);
}

void Scene::setupPositions(Position *start, Position *goal) {
    if (graph != NULL)
        delete graph;
    graph = new Graph(start, goal);
    addItem(graph);
}

void Scene::addCourbe(Courbe *courbe) {
    graph->addCourbe(courbe);
    update();
}

void Scene::addPositionTheorique(Position *position) {
    graph->addPositionTheorique(position);
}






