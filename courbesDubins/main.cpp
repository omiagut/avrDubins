/*
 * Calcul des courbes de Leister Dubins
 * Les classes de calcul sont dans le dossier courbes
 * mainwindow : IHM
 * Scene, Vue, Graph : visualisation interractive des courbes et de leur construction
 *
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
