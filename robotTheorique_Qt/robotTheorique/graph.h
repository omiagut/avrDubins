#ifndef GRAPH_H
#define GRAPH_H
#include <QGraphicsItem>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QColor>
#include "./courbes/parametres.h"
#include "./courbes/cercle.h"
#include "./courbes/courbe.h"

class Graph : public QGraphicsItem
{
public:
    Graph(Position *start, Position *goal, QGraphicsItem * parent = 0);
    Graph();
    ~Graph();

    Position *start;
    Position *goal;
    Courbe *courbe;
    Position *positionTheorique;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setColor(QPainter *painter, const QColor color);
    void affPosition(QPainter *painter, const QColor color, const Position *p);
    void affCourbe(QPainter *painter);
    void affArc(QPainter *painter, const QColor color, const Cercle *c, const float a, const float b);
    void affSegmentTangent(QPainter *painter, const QColor color);

    QLineF segment(const Point *p1, const Point *p2);

    QRect rectangle(const Cercle* c);

    void addCourbe(Courbe *courbe);
    void addArcStart(QPainter *painter, QColor color, Position *sg, Cercle *c, Point *tg);
    void addArcGoal(QPainter *painter, QColor color, Position *sg, Cercle *c, Point *tg);
    void addArcTangent(QPainter *painter, QColor color, Cercle *c, Point *ts, Point *tg);

    void addPositionTheorique(Position *position);

};

#endif // GRAPH_H
