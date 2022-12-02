#include <avr/io.h>
#include <avr/interrupt.h>
#include <cercle.h>
#include <parametres.h>
#include <courbe.h>
#include "timer1.h"
#include "pwm.h"

Position *start;
Position *goal;

/* les paramètres sont en exemple, mais correspondent à ceux de mainwindow.cpp */
void setupRobot() {
  /* initialisation du robot */
  start = new Position(-241, 100, PI / 2.0);
  goal = new Position(40, 3, 1.24);

  robot = new Robot(RAYON);
  robot->setPositions(start, goal);
  robot->setVitesse((float) 0.5);
  robot->setRayon((const float) 96.0);
  
  robot->calcTrajet(RSR);
  // ou
  //robot->plusCourt();

  robot->tempsTrajet();
  robot->setVitesseRoues();
  for (int i=0; i<3; ++i) {
    Serial.print("Phase ");
    Serial.print(i);
    Serial.print(" - OCR0A ");
    Serial.print(robot->vitessesRoues[i].ocr0A);
    Serial.print(" - OCR2A ");
    Serial.println(robot->vitessesRoues[i].ocr2A);    
  }
  Serial.println("");
}

void setupStart() {
  phase = START;
  tempsMouvement = robot->courbe->trajet[phase];
  robot->theorique = new Position(*robot->start);

  OCR0A = robot->vitessesRoues[phase].ocr0A;
  OCR2A = robot->vitessesRoues[phase].ocr2A;
  OCR0B = 0;
  OCR2B = 0;
  timer1_counter = 0;
}

/*
   Le PORTB1:2 porte les broches en1 et en2 du L298
*/
void setupL298() {
  // PB1 PB2 en sortie, ON
  DDRB |= (1 << DDB1) | (1 << DDB2);
  PORTB |= (1 << PB1) | (1 << PB2);  
} 
/*
   broches en1 et en2 du L298 à 0
*/
void stop() {
  PORTB &= ~0 ^ ((1<<PB1) | (1<<PB2)); // PB1 PB2 OFF
}

void affPosition() {
  // to0_2PI pour l'affichage, sinon perte de temps
  to0_2PI(robot->theorique->z);
  Serial.print("Position x ");
  Serial.print(robot->theorique->x);
  Serial.print(" y ");
  Serial.print(robot->theorique->y);
  Serial.print(" z ");
  Serial.print(robot->theorique->z * 180.0 / PI);
  Serial.print("° Phase ");
  Serial.print(phase);
  Serial.print(" Temps mouvement ");
  Serial.print(tempsMouvement);
  Serial.print(" Pas ");
  Serial.println(pasMouvement+1.0);
  Serial.flush();
}

void setup() {
  Serial.begin(9600);
  while (!Serial);
  setupTimer0_FastPWM_3();
  setupTimer2_FastPWM_3();
  setupRobot();
  setupStart();
  setupL298();
  cli();
  setupTimer1_CTC();
  sei();
}

void loop() {
  if (calcTheorique == true) {
    affPosition();
    robot->moveTheorique(phase, pasMouvement);
    calcTheorique = false;
  }
  if (stopRobot) {
    stop();
    cli();
  }
}
