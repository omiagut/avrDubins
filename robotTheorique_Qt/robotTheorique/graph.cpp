#include "graph.h"
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
using namespace std;

Graph::Graph(Position *start, Position *goal, QGraphicsItem *parent) : QGraphicsItem(parent)
{
    this->start = start;
    this->goal = goal;
    courbe = NULL;
    positionTheorique = NULL;
}

Graph::Graph() {}
Graph::~Graph() {}

/**/
QRectF Graph::boundingRect() const {
    return QRectF(-SIZE_X/2.0, -SIZE_Y/2.0, SIZE_X, SIZE_Y);
}

void Graph::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    affPosition(painter, QColor(0,0,255), start);
    affPosition(painter, QColor(255,0,0), goal);

    affCourbe(painter);

    if (positionTheorique != NULL)
        affPosition(painter, QColor(255, 192, 64), positionTheorique);

}

void Graph::setColor(QPainter *painter, const QColor color) {
    QPen pen;
    pen.setColor(color);
    painter->setPen(pen);
    QBrush brush;
    brush.setColor(color);
    brush.setStyle(Qt::SolidPattern);
    painter->setBrush(brush);
}

void Graph::affPosition(QPainter *painter, QColor color, const Position *p) {
    setColor(painter, color);
    painter->drawEllipse(p->x-(POINT_SIZE/2), -p->y-(POINT_SIZE/2), POINT_SIZE, POINT_SIZE);
    float x = p->x + (TIMON * cos(p->z));
    float y = p->y + (TIMON * sin(p->z));
    painter->drawLine(QPointF(p->x, -p->y), QPointF(x, -y));
    QBrush brush;
    brush.setStyle(Qt::NoBrush);
    painter->setBrush(brush);
}

void Graph::affCourbe(QPainter *painter) {
    if (courbe->valide == false)
        return;

    addArcStart(painter, QColor(0, 0,255), start, courbe->courbureStart, courbe->tangenceStart);
    addArcGoal(painter, QColor(255,0,0), goal, courbe->courbureGoal, courbe->tangenceGoal);
    if (courbe->cercleTangent == NULL)
        affSegmentTangent(painter, QColor(0,255,0));
    else {
        addArcTangent(painter, QColor(0,255,0), courbe->cercleTangent,
                      courbe->tangenceStart, courbe->tangenceGoal);
    }
}

void Graph::addArcStart(QPainter *painter, QColor color, Position *sg, Cercle *c, Point *tg) {
    float alpha = atan2f(sg->y - c->y , sg->x - c->x);

    Point *s = new Point(sg->x, sg->y);
    float arc;
    if (courbe->c == RSR || courbe->c == RSL || courbe->c == RLR)
        arc = -c->radian(s, tg, courbe->isSensTrigo(courbe->c, START));
    else
        arc = c->radian(s, tg, courbe->isSensTrigo(courbe->c, START));

    affArc(painter, color, c, alpha, arc);
}

void Graph::addArcGoal(QPainter *painter, QColor color, Position *sg, Cercle *c, Point *tg) {
    float alpha = atan2f(tg->y - c->y , tg->x - c->x);

    Point *s = new Point(sg->x, sg->y);
    float arc;
    if (courbe->c == RSL || courbe->c == LSL || courbe->c == LRL)
        arc = c->radian(tg, s, courbe->isSensTrigo(courbe->c, GOAL));
    else
        arc = -c->radian(tg, s, courbe->isSensTrigo(courbe->c, GOAL));

    affArc(painter, color, c, alpha, arc);
}

void Graph::addArcTangent(QPainter *painter, QColor color, Cercle *c, Point *ts, Point *tg) {
    float alpha = atan2f(ts->y - c->y , ts->x - c->x);

    float arc;
    if (courbe->c == RLR)
        arc = c->radian(ts, tg, courbe->isSensTrigo(courbe->c, TANGENT));
    else
        arc = -c->radian(ts, tg, courbe->isSensTrigo(courbe->c, TANGENT));

    affArc(painter, color, c, alpha, arc);
}

void Graph::affArc(QPainter *painter, QColor color, const Cercle *c, const float a, const float b) {
    QPen pen;
    pen.setWidth(1);
    pen.setColor(color);
    painter->setPen(pen);
    painter->drawArc(rectangle(c), (int) (a * 180.0 / PI * 16), (int) (b * 180.0 / PI * 16));
}

void Graph::affSegmentTangent(QPainter *painter, const QColor color) {
    QPen pen;
    pen.setWidth(1);
    pen.setColor(color);
    painter->setPen(pen);
    painter->drawLine(QPointF(courbe->tangenceStart->x, -courbe->tangenceStart->y),
                      QPointF(courbe->tangenceGoal->x, -courbe->tangenceGoal->y));
}

QLineF Graph::segment(const Point *p1,const  Point *p2) {
    return QLineF(QPointF(p1->x, -p1->y), QPointF(p2->x, -p2->y));
}

QRect Graph::rectangle(const Cercle *c) {
    return QRect(c->x - c->r, -c->y - c->r, c->r*2, c->r*2);
}

void Graph::addCourbe(Courbe *courbe) {
    this->courbe = courbe;
}

/**/
void Graph::addPositionTheorique(Position *position) {
    positionTheorique = new Position(*position);
    update();
}

