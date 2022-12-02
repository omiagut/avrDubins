#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <stdio.h>
#include <math.h>

#include "scene.h"
#include "vue.h"

#include "courbes/courbe.h"
#include "courbes/parametres.h"
#include "robot.h"
#include "calculs.h"

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

    QAction *actGo;

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

    QAction *actStartStop;
    bool startStop;

    /**/
    QMenu *mnuFichiers;
    QMenu *mnuAfficher;
    QMenu *mnuMouvement;

    /**/
    QToolBar *toolBar;
    QButtonGroup *buttonsCourbes;
    QCheckBox *chkCourbes[7];
    QDoubleSpinBox *spnVitesse;
    QDoubleSpinBox *spnRayon;


    /**/
    QStatusBar *statusBar;

    /**/
    QTimer *timer1;

    /**/
    Calculs *calculs;
    void closeEvent(QCloseEvent *);

    void createMoveActions();
    void createActions();
    void createMenu();
    void createToolBar();
    void enableIHM(bool b);

    Robot *robot;
    unsigned int pasMouvement;
    void setPasMouvement();
    float tempsMouvement;
    unsigned int timer1_counter;

    void changeCourbe(Courbes c);
    void changePosition();
    void plusCourte();

    float setupTimer1();
    void affDistance();

    /**/
    void affRobot();
    void affCourbe();
    void affVitesse();
    void affRayon();
    void affTempsTrajet();
    void affTimer(const float periode, const float OCR1A);
    void affPosition(const int phase, const float pasMouvement);
    void affPwmTics();

public slots:
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

    void on_courbesPressed(int);
    void on_vitesseChanged(double);
    void on_rayonChanged(double);
    void moveTheorique();
    void on_moveTheorique();
    void on_startStop(bool);
};

#endif // MAINWINDOW_H
