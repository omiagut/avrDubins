#include <cercle.h>
#include <parametres.h>
#include <courbe.h>
#include "timer1.h"

Position *start;
Position *goal;

/* les paramètres sont en exemple, mais correspondent à ceux de mainwindow.cpp */
void setupRobot() {
  unsigned long deb = micros();
  start = new Position(-241, 100, PI / 2.0);
  goal = new Position(40, 3, 1.24);
  robot = new Robot(RAYON);
  robot->setPositions(start, goal);
  robot->setVitesse((float) 0.5);
  robot->setRayon((const float) 0.5);

  //robot->calcTrajet(RSR);
  // ou
  robot->plusCourt();

  robot->tempsTrajet();
  robot->setVitesseRoues();
  Serial.print("tps setupRobot ");
  Serial.print(micros() - deb);
  Serial.print(" µs\n");
}

void setupStart() {
  unsigned long deb = micros();
  phase = START;

  tempsMouvement = robot->courbe->trajet[phase];
  robot->theorique = new Position(*robot->start);
  timer1_counter = 0;
  Serial.print("tps setupStart ");
  Serial.print(micros() - deb);
  Serial.print(" µs\n");
}

void affTemps() {
  unsigned long deb = micros();
  robot->moveTheorique(phase, pasMouvement);
  Serial.print("temps ");
  Serial.print(micros() - deb);
  Serial.print(" µs\n");
}

void setup() {
  Serial.begin(9600);
  while (!Serial);
  setupRobot();
  setupStart();
  cli();
  setupTimer1_CTC();
  sei();
}

void loop() {
  if (calcTheorique == true) {
    calcTheorique = false;
    affTemps();
  }
  if (stopRobot) {
    cli();
  }
}
