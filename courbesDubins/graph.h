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
    bool justCourbe;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setColor(QPainter *painter, const QColor color);
    void affPosition(QPainter *painter, const QColor color, const Position *p);
    void affCercle(QPainter *painter, const QColor color, const Cercle *c);
    void affPoint(QPainter *painter, QColor color, const Point *p);
    void affCourbe(QPainter *painter);
    void affArc(QPainter *painter, const QColor color, const Cercle *c, const float a, const float b);
    void affSegmentTangent(QPainter *painter, const QColor color);
    void affConstruction(QPainter *painter);
    void affSegments(QPainter *painter);

    QLineF segment(const Cercle *c1, const Cercle *c2);
    QLineF segment(const Cercle *c, const Point *p);
    QLineF segment(const Point *p1, const Point *p2);
    QRect rectangle(const Cercle* c);

    void addCourbe(Courbe *courbe, const bool justCourbe);
    void addArcStart(QPainter *painter, QColor color, Position *sg, Cercle *c, Point *tg);
    void addArcGoal(QPainter *painter, QColor color, Position *sg, Cercle *c, Point *tg);
    void addArcTangent(QPainter *painter, QColor color, Cercle *c, Point *ts, Point *tg);

    void setJustCourbe(bool b);
};

#endif // GRAPH_H
