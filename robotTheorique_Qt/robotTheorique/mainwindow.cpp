#include "mainwindow.h"
#include <math.h>
#include <iomanip>
#include <iostream>
using namespace std;

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

    /* IHM */
    statusBar = new QStatusBar;
    setStatusBar(statusBar);

    createMoveActions();
    createActions();
    createMenu();
    createToolBar();

    cout << fixed << setprecision(2);

    /* fenêtre d'affichage des calculs */
    calculs = new Calculs;
    calculs->show();

    /* timer de simulation de position théorique */
    timer1 = NULL;

    /* initialisation du robot */
    Position *start = new Position(-241, 100, PI/2.0);
    Position *goal = new Position(40, 3, 1.24);

    robot = new Robot(RAYON);
    robot->setPositions(start, goal);
    robot->setVitesse((float) 0.5);
    robot->setRayon((const float) 96.0);


    //robot->calcTrajet(RSR);
    // ou
    robot->plusCourt();

    affRobot();
    affCourbe();
    affDistance(); // statusbar
    robot->tempsTrajet();
    affTempsTrajet();

    /* mise à jour de la scene */
    scene->setupPositions(robot->start, robot->goal);
    scene->addCourbe(robot->courbe);

    /* mise à jour de la toolbar */
    chkCourbes[robot->courbe->c]->setChecked(true);
    spnVitesse->setValue(robot->vitesse/robot->vitesse_max*100);
    spnRayon->setValue(robot->rayon);

    startStop = false;
}

MainWindow::~MainWindow() {}

void MainWindow::createActions() {
    actExit = new QAction(tr("E&xit"), this);
    actExit->setShortcut(QKeySequence::Quit);
    connect(actExit, SIGNAL(triggered()), this, SLOT(close()));

    actZoomIn = new QAction(tr("Zoom In"), this);
    actZoomIn->setShortcut(Qt::Key_Plus);
    connect(actZoomIn, SIGNAL(triggered()), vue, SLOT(zoomIn()));

    actZoomOut = new QAction(tr("Zoom Out"), this);
    actZoomOut->setShortcut(Qt::Key_Minus);
    connect(actZoomOut, SIGNAL(triggered()), vue, SLOT(zoomOut()));

    actStartStop = new QAction("Space", this);
    actStartStop->setShortcut(Qt::Key_Space);
    actStartStop->setCheckable(true);
    actStartStop->setChecked(true);
    connect(actStartStop, SIGNAL(toggled(bool)), this, SLOT(on_startStop(bool)));
    addAction(actStartStop);
}

void MainWindow::createMoveActions() {
    actGo = new QAction(tr("&Théorique"), this);
    actGo->setShortcut(Qt::Key_T);
    connect(actGo, SIGNAL(triggered()), this, SLOT(on_moveTheorique()));

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
    mnuAfficher->addAction(actZoomIn);
    mnuAfficher->addAction(actZoomOut);

    mnuMouvement = new QMenu(tr("&Mouvement"), this);
    mnuMouvement->addAction(actGo);
    mnuMouvement->addSeparator();
    mnuMouvement->addAction(actStartX_Right);
    mnuMouvement->addAction(actStartX_Left);
    mnuMouvement->addAction(actStartY_Up);
    mnuMouvement->addAction(actStartY_Down);
    mnuMouvement->addAction(actStartZ_Right);
    mnuMouvement->addAction(actStartZ_Left);
    mnuMouvement->addSeparator();
    mnuMouvement->addAction(actGoalX_Right);
    mnuMouvement->addAction(actGoalX_Left);
    mnuMouvement->addAction(actGoalY_Up);
    mnuMouvement->addAction(actGoalY_Down);
    mnuMouvement->addAction(actGoalZ_Right);
    mnuMouvement->addAction(actGoalZ_Left);

    menuBar()->addMenu(mnuFichiers);
    menuBar()->addMenu(mnuAfficher);
    menuBar()->addMenu(mnuMouvement);
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
        chkCourbes[i]->setShortcut(Qt::Key_1+i);
        toolBar->addWidget(chkCourbes[i]);
        buttonsCourbes->setId(chkCourbes[i], i);
    }
    chkCourbes[6]->setShortcut(Qt::Key_0);
    connect(buttonsCourbes, SIGNAL(buttonClicked(int)), this, SLOT(on_courbesPressed(int)));

    /* changement de la vitesse exprimé en % de la vitesse max */
    toolBar->addWidget(new QLabel(QString(" -- Vitesse")));
    spnVitesse  = new QDoubleSpinBox;
    spnVitesse->setAlignment(Qt::AlignRight);
    spnVitesse->setRange(10.0, 100.0);
    spnVitesse->setDecimals(0);
    spnVitesse->setSingleStep(1.0);
    toolBar->addWidget(spnVitesse);
    toolBar->addWidget(new QLabel(QString("  % v_max")));
    connect(spnVitesse, SIGNAL(valueChanged(double)), this, SLOT(on_vitesseChanged(double)));

    /* Période pour calculer le rayon */
    toolBar->addWidget(new QLabel(tr(" -  - Rayon ")));
    spnRayon = new QDoubleSpinBox;
    spnRayon->setAlignment(Qt::AlignRight);
    spnRayon->setRange(ENTRAXE * 2.25, ENTRAXE * 300.0);
    spnRayon->setDecimals(0);
    spnRayon->setSingleStep(1.0);
    toolBar->addWidget(spnRayon);
    toolBar->addWidget(new QLabel(" cm"));
    connect(spnRayon, SIGNAL(valueChanged(double)), this, SLOT(on_rayonChanged(double)));

}

/* pour attendre la fin de simulation du trajet */
void MainWindow::enableIHM(bool b) {
    mnuAfficher->setEnabled(b);
    mnuMouvement->setEnabled(b);
    toolBar->setEnabled(b);
}

/* à chaque modification de position */
void MainWindow::changeCourbe(Courbes c) {
    if (c <= LRL)
        robot->calcTrajet((Courbes) c);
    else
        robot->plusCourt();
    affDistance();
    robot->tempsTrajet();

    chkCourbes[robot->courbe->c]->setChecked(true);
    scene->setupPositions(robot->start, robot->goal);
    scene->addCourbe(robot->courbe);
}

/* modifications de position */
void MainWindow::changePosition() {
    Courbes c = robot->courbe->c;
    changeCourbe(c);
}

void MainWindow::onStartX_Right() {
    robot->start->deltaX(DELTA_X);
    changePosition();
}

void MainWindow::onStartX_Left() {
    robot->start->deltaX(-DELTA_X);
    changePosition();
}

void MainWindow::onStartY_Up() {
    robot->start->deltaY(DELTA_Y);
    changePosition();
}

void MainWindow::onStartY_Down() {
    robot->start->deltaY(-DELTA_Y);
    changePosition();
}

void MainWindow::onStartZ_Right() {
    robot->start->deltaZ(-DELTA_Z);
    changePosition();
}

void MainWindow::onStartZ_Left() {
    robot->start->deltaZ(DELTA_Z);
    changePosition();
}

void MainWindow::onGoalX_Right() {
    robot->goal->deltaX(DELTA_X);
    changePosition();
}

void MainWindow::onGoalX_Left() {
    robot->goal->deltaX(-DELTA_X);
    changePosition();
}

void MainWindow::onGoalY_Up() {
    robot->goal->deltaY(DELTA_Y);
    changePosition();
}

void MainWindow::onGoalY_Down() {
    robot->goal->deltaY(-DELTA_Y);
    changePosition();
}

void MainWindow::onGoalZ_Right() {
    robot->goal->deltaZ(-DELTA_Z);
    changePosition();
}

void MainWindow::onGoalZ_Left() {
    robot->goal->deltaZ(DELTA_Z);
    changePosition();
}

/* changement de courbe dans la toolbar */
void MainWindow::on_courbesPressed(int c) {
    if (c <= LRL)
        robot->calcTrajet((Courbes) c);
    else
        robot->plusCourt();
    affDistance();
    affCourbe();
    robot->tempsTrajet();

    chkCourbes[robot->courbe->c]->setChecked(true);
    scene->addCourbe(robot->courbe);

    if (robot->theorique != NULL) {
        delete robot->theorique;
        robot->theorique = new Position(*robot->start);
        scene->addPositionTheorique(robot->theorique);
    }

    vue->setFocus();
}

void MainWindow::on_startStop(bool b) {
    if (b)
        timer1->start();
    else
        timer1->stop();
}

/* choix "?" dans la toolbar */
void MainWindow::plusCourte() {
    Courbes c = RSR;
    robot->plusCourt();
    changeCourbe(c);
}

void MainWindow::on_vitesseChanged(double pc) {
    float prop = pc/100.0;
    robot->setVitesse(prop);
    robot->calcTrajet(robot->courbe->c);
    affDistance();
    robot->tempsTrajet();
    vue->setFocus();
}

void MainWindow::on_rayonChanged(double p) {
    robot->setRayon((float) p);
    changeCourbe(robot->courbe->c);
    vue->setFocus();
}

/* affichage dans la barre de status */
void MainWindow::affDistance() {
    if (robot->courbe->valide) {
        QString strStart = "";
        QString strGoal = "";
        QString strR = "";
        QString str[11];
        to0_2PI(robot->start->z);
        to0_2PI(robot->goal->z);

        strStart +=  "Position " + str[0].setNum(robot->start->x, 'f', 0)
             + " , " + str[1].setNum(robot->start->y, 'f', 0)
             + " , " + str[2].setNum(robot->start->z * 180 / PI, 'f', 2)
             + tr("°");

        strGoal  +=  tr("  à position ") + str[3].setNum(robot->goal->x, 'f', 0)
             + " , " + str[4].setNum(robot->goal->y, 'f', 0)
             + " , " + str[5].setNum(robot->goal->z * 180 / PI, 'f', 2)
             + tr("°");

        strR += "-- Rayon = " + str[10].setNum(robot->rayon, 'f', 2) + "cm -- ";

        str[6] = str[6].setNum(robot->courbe->trajet[START], 'f', 2)
                + " + " + str[7].setNum(robot->courbe->trajet[TANGENT], 'f', 2)
                + " + " + str[8].setNum(robot->courbe->trajet[GOAL], 'f', 2)
                + " = " + str[9].setNum(robot->courbe->trajet[START]+
                                        robot->courbe->trajet[TANGENT]+
                                        robot->courbe->trajet[GOAL], 'f', 2);
        statusBar->showMessage(strStart + strGoal + strR +
                               tr(" -> Distance = ") + str[6] + " pixels");
    }
    else
       statusBar->showMessage("");
}

/*
 * Emulation
 */

// Un calcul / seconde, mais en fin de phase, il faut accorder le pas au temps restant
void MainWindow::setPasMouvement() {
    pasMouvement = 0;
    if (tempsMouvement >= 1000.0)
        pasMouvement = 999;
    else
        if (tempsMouvement > 0.0)
            pasMouvement = (unsigned int) ceil(tempsMouvement - 1);
}

void MainWindow::on_moveTheorique() {
    enableIHM(false);
    robot->setVitesseRoues();

    affRayon();
    affVitesse();
    affTempsTrajet();
    affPwmTics();

    tempsMouvement = robot->courbe->trajet[START];
    setPasMouvement();
    timer1_counter = 0;
    robot->theorique = new Position(*robot->start);
    delete timer1;
    timer1 = new QTimer(this);
    connect(timer1, SIGNAL(timeout()), this, SLOT(moveTheorique()));
    timer1->start(setupTimer1());
}


/* simulation de l'interruption ISR(TIMER1_COMPA_vect) pour déplacement */
void MainWindow::moveTheorique() {
    static int phase = START;
    timer1_counter++;
    if (timer1_counter >= pasMouvement) {
        /* affichage */
        affPosition(phase, pasMouvement+1);

        robot->moveTheorique(phase, pasMouvement+1);
        scene->addPositionTheorique(robot->theorique);
        tempsMouvement -= (float) (timer1_counter + 1.0);
        setPasMouvement();
        timer1_counter = 0;

        if (tempsMouvement <= 0.0) {    // changement de phase
            if (phase < GOAL) {
                tempsMouvement = robot->courbe->trajet[++phase];
                setPasMouvement();
                timer1_counter = 0;
            }
            else {  // fin du trajet
                /* affichage */
                affPosition(phase, pasMouvement);
                calculs->texte->append("");
                phase = START;
                timer1->stop();
                enableIHM(true);
            }
        }
    }
}


/*
 * en QT, il suffit de régler le timer à 1 pour 1 milliseconde
 * en AVR, pour un timer 16 bits, pour une interruption / milliseconde avec le prescaler à 1 :
 * période = 16000000 / 65536 / 1 -> une interruption toutes les 4,096 millisecondes
 * en mode CTC, avec OCR1A = 16000, (65536 / 4,096 = 16000) -> une interrution / milliseconde
 */
float MainWindow::setupTimer1() {
    float periode = 1.0 / 16000000.0  * 1.0 * 0xFFFF;
    float OCR1A = 16000.0;
    /* affichage */
    affTimer(periode, OCR1A);

    return periode / 0xFFFF * OCR1A * 1000.0; // (pour 1 interruption / milliseconde , * 1000);
}

/* affichages */

void MainWindow::affRobot() {
    QString st[4];
    QString s = QString("Robot entraxe ") + st[0].setNum(ENTRAXE)
            + QString(" cm -- diametre roues ")
            + st[1].setNum(DIAMETRE) + QString(" cm -- rpm = ")
            + st[2].setNum(RPM) + QString(" tr/minute --> v max = ")
            + st[3].setNum(robot->vitesse_max,'f',2)
            + QString(" cm/minute\n");
    calculs->texte->append(s);
}

void MainWindow::affVitesse() {
    QString st[3];
    float vl, vr;
    if (robot->vitessesRoues[START].roueDroite < robot->vitessesRoues[START].roueGauche) {
        vl = robot->vitessesRoues[START].roueDroite;
        vr = robot->vitessesRoues[START].roueGauche;
    }
    else {
        vl = robot->vitessesRoues[START].roueGauche;
        vr = robot->vitessesRoues[START].roueDroite;
    }
    QString s = QString("Vitesse en courbe ")
            + st[0].setNum(robot->vitesse, 'f', 2)
            + QString(" - roue lente ")
            + st[1].setNum(vl, 'f', 2)
            + QString(" - roue rapide ")
            + st[2].setNum(vr, 'f', 2)
            + QString(" cm/minute");
    calculs->texte->append(s);
}

void MainWindow::affRayon() {
    QString st;
    QString s = QString("\nRayon de courbure ") + st.setNum(robot->rayon, 'f', 2);
    calculs->texte->append(s);
}

void MainWindow::affCourbe() {
    if (robot->courbe->valide == false)
        return;
    QStringList lst;
    lst << "RSR" << "RSL" << "LSR" << "LSL" << "RLR" << "LRL";
    QString st[4];
    QString s;
    s = QString("Distance du trajet courbe ")
            + lst.at(robot->courbe->c) + QString(" = ")
            + st[0].setNum(robot->courbe->trajet[START],'f', 2) + QString(" + ")
            + st[1].setNum(robot->courbe->trajet[TANGENT],'f',2) + QString(" + ")
            + st[2].setNum(robot->courbe->trajet[GOAL], 'f', 2) + QString(" = ")
            + st[3].setNum(robot->courbe->trajet[START] + robot->courbe->trajet[TANGENT] +
                        robot->courbe->trajet[GOAL], 'f', 2) + QString(" cm");

    calculs->texte->append(s);
}

void MainWindow::affTempsTrajet() {
    if (robot->courbe->valide == false)
        return;
    QString st[2];
    QString s = QString("Temps de trajet ");
    for (int i = START; i <= GOAL; ++i) {
        s += st[0].setNum(robot->courbe->trajet[i], 'f', 0);
        if (i < GOAL)
            s += QString(" + ");
        else
            s += QString(" = ");
    }
    s += st[1].setNum(
        (robot->courbe->trajet[START]+robot->courbe->trajet[TANGENT]+robot->courbe->trajet[GOAL]) /1000.0, 'f', 2)
         + QString(" secondes");
    calculs->texte->append(s);
}

void MainWindow::affTimer(const float periode, const float OCR1A) {
    QString s[4];
    s[0] = tr("Période timer 1 ") + s[1].setNum(periode, 'f', 6)+ " s. OCR1A = " +
            s[2].setNum(OCR1A, 'f', 0) + " -> une interruption / " +
            s[3].setNum(periode / 0xFFFF * OCR1A * 1000, 'f', 3) + " milliseconde\n";
    calculs->texte->append(s[0]);
}

void MainWindow::affPosition(const int phase, const float pasMouvement) {
    if (phase == START)
        calculs->texte->setTextColor(QColor(255,0,0));
    else
        if (phase == TANGENT)
           calculs->texte->setTextColor(QColor(0,255,0));
        else
            calculs->texte->setTextColor(QColor(0,0,255));

    // to0_2PI pour l'affichage, sinon perte de temps
    to0_2PI(robot->theorique->z);
    QStringList lst;
    lst << "Start" << "Tangent" << "Goal";
    QString s[9];
    s[0] =  "Position x " + s[1].setNum(robot->theorique->x, 'f', 0) + " , y "
            + s[2].setNum(robot->theorique->y, 'f', 0) + " , z "
            + s[3].setNum(robot->theorique->z * 180.0 / PI, 'f', 2) + tr("° ")
            + " - Temps mouvement " + s[4].setNum(tempsMouvement, 'f', 0)
            + " ms .  Pas " + s[5].setNum(pasMouvement, 'f', 0) + " ms";
    calculs->texte->append(s[0]);
    calculs->texte->setTextColor(QColor(0,0,0));
}

void MainWindow::affPwmTics() {
    QStringList lst;
    lst << "Start" << "Tangent" << "Goal";
    QString s[5];
    calculs->texte->append("");
    for (int i = START; i <= GOAL; ++i) {
        if (i == START)
            calculs->texte->setTextColor(QColor(255,0,0));
        else
            if (i == TANGENT)
               calculs->texte->setTextColor(QColor(0,255,0));
            else
                calculs->texte->setTextColor(QColor(0,0,255));
        s[0] = lst.at(i) + " - Pwm roue droite " + s[1].setNum(robot->vitessesRoues[i].ocr0A)
               + " , roue gauche " + s[2].setNum(robot->vitessesRoues[i].ocr2A)
               + " - Tics roue droite " + s[3].setNum(robot->vitessesRoues[i].ticsDroite)
               +  " , roue gauche " + s[4].setNum(robot->vitessesRoues[i].ticsGauche);
        calculs->texte->append(s[0]);
    }
    calculs->texte->setTextColor(QColor(0,0,0));
    calculs->texte->append("");
}


/**/
void MainWindow::closeEvent(QCloseEvent *) {
    delete timer1;
    calculs->close();
    close();
}




