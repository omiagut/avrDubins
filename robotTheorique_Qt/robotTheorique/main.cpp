/*
 * Modélisation des courbes de Leister Dubins
 * Dans l'optique d' asservir la position, il faut connaître la position théorique
 * à intervals réguliers.
 * Ici un robot à 2 roues (entraxe, diamètre des roues, RPM des moteurs)
 * suit une courbe de Dubins. Sa position théorique est affichée toutes les secondes
 * - grâce au modèle inverse de calcul de la position
 * - en émulant un timer/counter 16 bits d'un ATMEGA
 */
#include "mainwindow.h"
#include <QString>
#include <QApplication>
#include <QTextCodec>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("Utf-8"));
    cout.precision(2);
    MainWindow w;
    w.show();
    return a.exec();
}
