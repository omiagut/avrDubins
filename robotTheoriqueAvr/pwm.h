/*
   Fast PWM des roues
*/
#ifndef PWM_H
#define PWM_H

#include <avr/io.h>

// droite
void setupTimer0_FastPWM_3() {
  DDRD |= ((1 << DDD6) | (1 << DDD5));
  // Set the Timer 0 Mode to PWM fast
  TCCR0A |= ((1 << WGM01) | (1 << WGM00));
  // OC0A connecté en sortie
  TCCR0A |= (1 << COM0A1);
  // prescaler 64
  TCCR0B |= ((1 << CS01) | (1 << CS00));
  
  // enable L298
  DDRB |= (1 << DDB1);
  PORTB |= (1 << PB1);
  //PORTB &= ~(1 << PB1);
}

// gauche
void setupTimer2_FastPWM_3() {
  DDRD |= (1 << DDD3); 
  DDRB |= (1 << DDB3);
  
  TCCR2A |= ((1 << WGM21) | (1 << WGM20));
  TCCR2A |= (1 << COM2A1); 
  TCCR2B |= ((1 << CS21) | (1 << CS20));
    
  // enable L298
  DDRB |= (1 << DDB2);
  PORTB |= (1 << PB2);
  //PORTB &= ~(1 << PB2);
}
#endif
