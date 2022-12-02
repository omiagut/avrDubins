#ifndef CALCULS_H
#define CALCULS_H

#include <QWidget>
#include <QTextEdit>

class Calculs : public QWidget
{
    Q_OBJECT
public:
    Calculs(QWidget *parent = 0);
    QTextEdit *texte;
    virtual void resizeEvent ( QResizeEvent *);
};

#endif // CALCULS_H
