#include "calculs.h"

Calculs::Calculs(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Calculs");
    resize(1000, 300);
    move(100, 100);
    texte = new QTextEdit(this);
}

void Calculs::resizeEvent(QResizeEvent *) {
    texte->resize(width(), height());
}

