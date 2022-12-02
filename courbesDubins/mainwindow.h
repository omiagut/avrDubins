#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <stdio.h>
#include <math.h>

#include "scene.h"
#include "vue.h"

#include "courbes/courbe.h"

#include<iostream>
using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Scene *scene;
    Vue *vue;

    QAction *actExit;
    QAction *actZoomIn;
    QAction *actZoomOut;

    QAction *actRSR;
    QAction *actRSL;
    QAction *actLSR;
    QAction *actLSL;
    QAction *actRLR;
    QAction *actLRL;

    QAction *actJustCourbe;

    QAction *actStartX_Right;     // déplace le robot sur l'axe des x
    QAction *actStartX_Left;
    QAction *actStartY_Up;        // déplace le robot sur l'axe des y
    QAction *actStartY_Down;
    QAction *actStartZ_Right;     // tourne sur l'axe des z
    QAction *actStartZ_Left;

    QAction *actGoalX_Right;     // idem position d'arrivée
    QAction *actGoalX_Left;
    QAction *actGoalY_Up;
    QAction *actGoalY_Down;
    QAction *actGoalZ_Right;
    QAction *actGoalZ_Left;

    /**/
    QMenu *mnuFichiers;
    QMenu *mnuAfficher;
    QMenu *mnuMove;

    /**/
    QToolBar *toolBar;
    QButtonGroup *buttonsCourbes;
    QCheckBox *chkCourbes[7];

    /**/
    /**/
    QStatusBar *statusBar;

    void createActions();
    void createMoveActions();
    void createMenu();
    void createToolBar();

    Position *start;
    Position *goal;
    Courbe *courbe;
    void changeCourbe(Courbes c);
    void changePosition();
    void plusCourte();
    void affDistance();

public slots:
    // changement de courbe
    void on_rsr();
    void on_rsl();
    void on_lsr();
    void on_lsl();
    void on_rlr();
    void on_lrl();
    void on_justCourbe();
    void on_courbesPressed(int);

    // changement de position (menu et clavier)
    void onStartX_Right();
    void onStartX_Left();
    void onStartY_Up();
    void onStartY_Down();
    void onStartZ_Right();
    void onStartZ_Left();
    void onGoalX_Right();
    void onGoalX_Left();
    void onGoalY_Up();
    void onGoalY_Down();
    void onGoalZ_Right();
    void onGoalZ_Left();
};

#endif // MAINWINDOW_H
