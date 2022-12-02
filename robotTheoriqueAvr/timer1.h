/*
   Le timer 1 est réglé à une interruption par milliseconde.
   La milliseconde est aussi l'unité du temps de mouvement.
   Le timer1 ne fait pas de calcul. Il positionne calcTheorique à 1
   pour que loop() les fasse. Il indique aussi la fin du parcours
*/
#ifndef TIMER1_H
#define TIMER1_H
#include <avr/io.h>
#include <avr/interrupt.h>
#include "robot.h"

Robot *robot;

volatile uint32_t timer1_counter;
volatile bool calcTheorique = true;
volatile bool stopRobot = false;
volatile uint8_t phase;
volatile float tempsMouvement;
volatile uint16_t pasMouvement;

/* 
 * Un calcul / seconde, mais en fin de phase, il faut accorder le pas au temps restant
 */
void setPasMouvement() {
  pasMouvement = 0;
  if (tempsMouvement >= 1000.0)
    pasMouvement = 999;
  else
    if (tempsMouvement > 0.0)
      pasMouvement = (uint16_t) ceil(tempsMouvement - 1);  
}

/*
   Timer 1 en mode CTC (mode 4)
*/
void setupTimer1_CTC() {
  TCCR1B |= (1 << WGM12); 	// CTC
  TCCR1B |= (1 << CS10);  	// prescaler à 1 -> 1 interruption / 4096 ms
  OCR1A = 16000;          	// 4096 / 65536 * 16000 = 1000 -> 1 interruption par milliseconde
  TIMSK1 |= (1 << OCIE1A); 	// interruption sur COMPA
}

ISR(TIMER1_COMPA_vect) {
  timer1_counter++;
  if (timer1_counter >= pasMouvement) {
    calcTheorique = true;
    tempsMouvement -= ((float)timer1_counter + 1.0);
    setPasMouvement();
    timer1_counter = 0;
    if (tempsMouvement <= 0.0) {    // changement de phase
      if (phase < GOAL) {
        tempsMouvement = robot->courbe->trajet[++phase];
        setPasMouvement();
        OCR0A = robot->vitessesRoues[phase].ocr0A;
        OCR2A = robot->vitessesRoues[phase].ocr2A;        
      }
      else {  // fin du trajet
        stopRobot = true;
      }
    }
  }
}
#endif
