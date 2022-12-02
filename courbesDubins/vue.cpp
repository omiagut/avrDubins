#include "vue.h"
#include <QBrush>
#include "./courbes/parametres.h"

Vue::Vue(QGraphicsView *parent) : QGraphicsView (parent) {
    QBrush brush;
    brush.setColor(QColor(FOND_COLOR));
    brush.setStyle(Qt::SolidPattern);
    setBackgroundBrush(brush);
}

Vue::~Vue() {}

/**/
void Vue::zoomIn() {
    scale(1.2, 1.2);
}

void Vue::zoomOut() {
    scale(1/1.2, 1/1.2);
}

