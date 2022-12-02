/*
 * mainwindow est l'interface IHM
 * le mieux est de l'utiliser au clavier :
 *  1..6 sélectionnent les courbes RSR..LRL
 *  0 choisit la courbe la plus courte
 *  Maj -> position de départ
 *      -> Maj + flèche (Haut, bas, droite, gauche) déplace la position de départ
 *         Maj + (PgUp ou PgDown) tourne la position de départ
 * Ctrl -> position d'arrivée, même flèches
 * la touche "A" affiche/cache la construction
 * la touche "Q" Quitte
 * scene et vue affichent le graph, classe héritée de QGraphicsItem
 * les touches "-" et "+" zooment, les flèches déplacent le centre
 */
#include "mainwindow.h"
#include <math.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    /*
     * Définition et positionnement de la scene, de la vue
     */
    setWindowTitle(tr("Courbes de L. Dubins"));
    resize(WND_X, WND_Y);
    move(POS_X, POS_Y);

    scene = new Scene;
    vue = new Vue;
    vue->setScene(scene);
    setCentralWidget(vue);
    scene->repereXY();

    // IHM
    createActions();
    createMoveActions();
    createMenu();
    createToolBar();

    /**/
    statusBar = new QStatusBar;
    setStatusBar(statusBar);

    /* calcul courbe */
    start = new Position(0,0,0);
    goal = new Position(0,0,0);
    courbe = new Courbe(RSR);
    courbe->setup(start, goal, RAYON);

    /* mise à jour toolbar */
    chkCourbes[courbe->c]->setChecked(true);

    /* affichage courbe */
    scene->setupPositions(start, goal);
    scene->addCourbe(courbe, actJustCourbe->isChecked());
    affDistance();

}

MainWindow::~MainWindow() {}

void MainWindow::createActions() {
    actExit = new QAction(tr("&Quitter"), this);
    actExit->setShortcut(QKeySequence::Quit);
    connect(actExit, SIGNAL(triggered()), this, SLOT(close()));

    actJustCourbe = new QAction(tr("&Affiche Juste la Courbe"), this);
    actJustCourbe->setCheckable(true);
    actJustCourbe->setChecked(false);
    actJustCourbe->setShortcut(Qt::Key_A);
    connect(actJustCourbe, SIGNAL(changed()), SLOT(on_justCourbe()));

    actZoomIn = new QAction(tr("Zoom In"), this);
    actZoomIn->setShortcut(Qt::Key_Plus);
    connect(actZoomIn, SIGNAL(triggered()), vue, SLOT(zoomIn()));

    actZoomOut = new QAction(tr("Zoom Out"), this);
    actZoomOut->setShortcut(Qt::Key_Minus);
    connect(actZoomOut, SIGNAL(triggered()), vue, SLOT(zoomOut()));

    /**/
    actRSR = new QAction(tr("Courbe RSR"), this);
    actRSR->setShortcut(Qt::Key_1);
    connect(actRSR, SIGNAL(triggered()), SLOT(on_rsr()));

    actRSL = new QAction(tr("Courbe RSL"), this);
    actRSL->setShortcut(Qt::Key_2);
    connect(actRSL, SIGNAL(triggered()), SLOT(on_rsl()));

    actLSR = new QAction(tr("Courbe LSR"), this);
    actLSR->setShortcut(Qt::Key_3);
    connect(actLSR, SIGNAL(triggered()), SLOT(on_lsr()));

    actLSL = new QAction(tr("Courbe LSL"), this);
    actLSL->setShortcut(Qt::Key_4);
    connect(actLSL, SIGNAL(triggered()), SLOT(on_lsl()));

    actRLR = new QAction(tr("Courbe RLR"), this);
    actRLR->setShortcut(Qt::Key_5);
    connect(actRLR, SIGNAL(triggered()), SLOT(on_rlr()));

    actLRL = new QAction(tr("Courbe LRL"), this);
    actLRL->setShortcut(Qt::Key_6);
    connect(actLRL, SIGNAL(triggered()), SLOT(on_lrl()));
}

void MainWindow::createMoveActions() {
    actStartX_Right = new QAction(QString(tr("Start Right")), this);
    actStartX_Right->setShortcut(Qt::SHIFT + Qt::Key_Right);
    connect(actStartX_Right, SIGNAL(triggered()), SLOT(onStartX_Right()));

    actStartX_Left = new QAction(QString(tr("Start Left")), this);
    actStartX_Left->setShortcut(Qt::SHIFT + Qt::Key_Left);
    connect(actStartX_Left, SIGNAL(triggered()), SLOT(onStartX_Left()));

    actStartY_Up = new QAction(QString(tr("Start Up")), this);
    actStartY_Up->setShortcut(Qt::SHIFT + Qt::Key_Up);
    connect(actStartY_Up, SIGNAL(triggered()), SLOT(onStartY_Up()));

    actStartY_Down = new QAction(QString(tr("Start Down")), this);
    actStartY_Down->setShortcut(Qt::SHIFT + Qt::Key_Down);
    connect(actStartY_Down, SIGNAL(triggered()), SLOT(onStartY_Down()));

    actStartZ_Right = new QAction(QString(tr("Start Angle Right")), this);
    actStartZ_Right->setShortcut(Qt::SHIFT + Qt::Key_PageUp);
    connect(actStartZ_Right, SIGNAL(triggered()), SLOT(onStartZ_Right()));

    actStartZ_Left = new QAction(QString(tr("Start Angle Left")), this);
    actStartZ_Left->setShortcut(Qt::SHIFT + Qt::Key_PageDown);
    connect(actStartZ_Left, SIGNAL(triggered()), SLOT(onStartZ_Left()));

    actGoalX_Right = new QAction(QString(tr("Goal Right")), this);
    actGoalX_Right->setShortcut(Qt::CTRL + Qt::Key_Right);
    connect(actGoalX_Right, SIGNAL(triggered()), SLOT(onGoalX_Right()));

    actGoalX_Left = new QAction(QString(tr("Goal Left")), this);
    actGoalX_Left->setShortcut(Qt::CTRL + Qt::Key_Left);
    connect(actGoalX_Left, SIGNAL(triggered()), SLOT(onGoalX_Left()));

    actGoalY_Up = new QAction(QString(tr("Goal Up")), this);
    actGoalY_Up->setShortcut(Qt::CTRL + Qt::Key_Up);
    connect(actGoalY_Up, SIGNAL(triggered()), SLOT(onGoalY_Up()));

    actGoalY_Down = new QAction(QString(tr("Goal Down")), this);
    actGoalY_Down->setShortcut(Qt::CTRL + Qt::Key_Down);
    connect(actGoalY_Down, SIGNAL(triggered()), SLOT(onGoalY_Down()));

    actGoalZ_Right = new QAction(QString(tr("Goal Angle Right")), this);
    actGoalZ_Right->setShortcut(Qt::CTRL + Qt::Key_PageUp);
    connect(actGoalZ_Right, SIGNAL(triggered()), SLOT(onGoalZ_Right()));

    actGoalZ_Left = new QAction(QString(tr("Goal Angle Left")), this);
    actGoalZ_Left->setShortcut(Qt::CTRL + Qt::Key_PageDown);
    connect(actGoalZ_Left, SIGNAL(triggered()), SLOT(onGoalZ_Left()));
}

void MainWindow::createMenu() {
    mnuFichiers = new QMenu(tr("&Fichiers"), this);
    mnuFichiers->addAction(actExit);

    mnuAfficher = new QMenu(tr("&Afficher"), this);
    mnuAfficher->addAction(actJustCourbe);
    mnuAfficher->addSeparator();

    mnuAfficher->addAction(actRSR);
    mnuAfficher->addAction(actRSL);
    mnuAfficher->addAction(actLSR);
    mnuAfficher->addAction(actLSL);
    mnuAfficher->addAction(actRLR);
    mnuAfficher->addAction(actLRL);
    mnuAfficher->addSeparator();

    mnuAfficher->addAction(actZoomIn);
    mnuAfficher->addAction(actZoomOut);

    mnuMove = new QMenu(QString("&Mouvements"), this);
    mnuMove->addAction(actStartX_Right);
    mnuMove->addAction(actStartX_Left);
    mnuMove->addAction(actStartY_Up);
    mnuMove->addAction(actStartY_Down);
    mnuMove->addAction(actStartZ_Right);
    mnuMove->addAction(actStartZ_Left);
    mnuMove->addSeparator();
    mnuMove->addAction(actGoalX_Right);
    mnuMove->addAction(actGoalX_Left);
    mnuMove->addAction(actGoalY_Up);
    mnuMove->addAction(actGoalY_Down);
    mnuMove->addAction(actGoalZ_Right);
    mnuMove->addAction(actGoalZ_Left);

    menuBar()->addMenu(mnuFichiers);
    menuBar()->addMenu(mnuAfficher);
    menuBar()->addMenu(mnuMove);
}

void MainWindow::createToolBar() {
    toolBar = addToolBar(tr("Courbes"));
    buttonsCourbes = new QButtonGroup;
    chkCourbes[RSR] = new QCheckBox("RSR");
    chkCourbes[RSL] = new QCheckBox("RSL");
    chkCourbes[LSR] = new QCheckBox("LSR");
    chkCourbes[LSL] = new QCheckBox("LSL");
    chkCourbes[RLR] = new QCheckBox("RLR");
    chkCourbes[LRL] = new QCheckBox("LRL");
    chkCourbes[6] = new QCheckBox(" ? ");
    for (int i = 0; i<7; ++i) {
        buttonsCourbes->addButton(chkCourbes[i]);
        toolBar->addWidget(chkCourbes[i]);
        buttonsCourbes->setId(chkCourbes[i], i);
    }
    chkCourbes[6]->setShortcut(Qt::Key_0);
    connect(buttonsCourbes, SIGNAL(buttonClicked(int)), this, SLOT(on_courbesPressed(int)));
}

void MainWindow::changeCourbe(Courbes c) {
    // conserve la valeur du rayon de courbure
    float r = courbe->courbureStart->r;

    // calcul
    delete courbe;
    courbe = new Courbe(c);
    courbe->setup(start, goal, r);
    chkCourbes[courbe->c]->setChecked(true);

    // affichage
    scene->setupPositions(start, goal);
    scene->addCourbe(courbe, actJustCourbe->isChecked());
    affDistance();
}

void MainWindow::plusCourte() {
    float distance = INFINITY;
    Courbes c = RSR;
    Trajet t = courbe->plusCourte(start, goal, RAYON, distance, c);
    changeCourbe(c);
}

void MainWindow::affDistance() {
    QString strStart = "";
    QString strGoal = "";
    QString str[10];
    to0_2PI(start->z);
    to0_2PI(goal->z);

    strStart +=  str[0].setNum(start->x, 'f', 0)
             + " , " + str[1].setNum(start->y, 'f', 0)
             + " , " + str[2].setNum(start->z * 180 / PI, 'f', 2)
             + tr("°");

    strGoal  +=  str[3].setNum(goal->x, 'f', 0)
             + " , " + str[4].setNum(goal->y, 'f', 0)
             + " , " + str[5].setNum(goal->z * 180 / PI, 'f', 2)
             + tr("°");

    if (courbe->valide) {
        Trajet t = courbe->distance(start, goal);
        str[6] = str[6].setNum(t.start, 'f', 2)
                + " + " + str[7].setNum(t.tangent, 'f', 2)
                + " + " + str[8].setNum(t.goal, 'f', 2)
                + " = " + str[9].setNum(t.start+t.tangent+t.goal, 'f', 2);
    }
    else
        str[6] ="";
    statusBar->showMessage(strStart + " to " + strGoal + tr(" -> Distance = ") + str[6] + " pixels");
}

void MainWindow::on_rsr() {
    changeCourbe(RSR);
}

void MainWindow::on_rsl() {
    changeCourbe(RSL);
}

void MainWindow::on_lsr() {
    changeCourbe(LSR);
}

void MainWindow::on_lsl() {
    changeCourbe(LSL);
}

void MainWindow::on_rlr() {
    changeCourbe(RLR);
}

void MainWindow::on_lrl() {
    changeCourbe(LRL);
}

void MainWindow::on_justCourbe() {
    if (actJustCourbe->isChecked())
        scene->setJustCourbe(false);
    else
        scene->setJustCourbe(true);
    changeCourbe(courbe->c);
}

void MainWindow::on_courbesPressed(int c) {
    if (c <= LRL)
        changeCourbe((Courbes) c);
    else
        plusCourte();
    vue->setFocus();
}

/**/

void MainWindow::changePosition() {
    Courbes c = courbe->c;
    changeCourbe(c);
}

void MainWindow::onStartX_Right() {
    start->deltaX(DELTA_X);
    changePosition();
}

void MainWindow::onStartX_Left() {
    start->deltaX(-DELTA_X);
    changePosition();
}

void MainWindow::onStartY_Up() {
    start->deltaY(DELTA_Y);
    changePosition();
}

void MainWindow::onStartY_Down() {
    start->deltaY(-DELTA_Y);
    changePosition();
}

void MainWindow::onStartZ_Right() {
    start->deltaZ(DELTA_Z);
    changePosition();
}

void MainWindow::onStartZ_Left() {
    start->deltaZ(-DELTA_Z);
    changePosition();
}

void MainWindow::onGoalX_Right() {
    goal->deltaX(DELTA_X);
    changePosition();
}

void MainWindow::onGoalX_Left() {
    goal->deltaX(-DELTA_X);
    changePosition();
}

void MainWindow::onGoalY_Up() {
    goal->deltaY(DELTA_Y);
    changePosition();
}

void MainWindow::onGoalY_Down() {
    goal->deltaY(-DELTA_Y);
    changePosition();
}

void MainWindow::onGoalZ_Right() {
    goal->deltaZ(DELTA_Z);
    changePosition();
}

void MainWindow::onGoalZ_Left() {
    goal->deltaZ(-DELTA_Z);
    changePosition();
}





