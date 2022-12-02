#ifndef VUE_H
#define VUE_H

#include <QObject>
#include <QGraphicsView>

class Vue : public QGraphicsView
{
    Q_OBJECT
public:
    Vue(QGraphicsView *parent = 0);
    ~Vue();

public slots:
    void zoomIn();
    void zoomOut();

};

#endif // VUE_H
