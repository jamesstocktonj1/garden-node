#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>

//#define msTIMER_RELOAD_VALUE 131
#define msTIMER_RELOAD_VALUE (256-( (F_CPU/64) / 1000) )

volatile extern uint16_t msTimer;
volatile extern uint16_t msCommsTimeout;

void init_timer(void);

#endif// TIMER_H