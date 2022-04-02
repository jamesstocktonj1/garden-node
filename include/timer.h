#ifndef __TIMER_H
#define __TINER_H

#include <avr/io.h>

volatile extern uint16_t msTimer;
volatile extern uint16_t msCommsTimeout;

void ConfigT0_ISR(void);

#endif// __TIMER_H