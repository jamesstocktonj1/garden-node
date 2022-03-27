#ifndef IO_H
#define IO_H

#include <avr/io.h>


//pin definitions

//leds
#define LED1_DDR    DDRD
#define LED1_PORT   PORTD
#define LED1_PIN    PD5

#define LED2_DDR    DDRD
#define LED2_PORT   PORTD
#define LED2_PIN    PD6

//relay
#define RELAY_DDR    DDRC
#define RELAY_PORT   PORTC
#define RELAY_PIN    PC2

//flow control
#define FLOW_DDR    DDRB
#define FLOW_PORT   PORTB
#define TX_PIN      PB0
#define RX_PIN      PB1



void init_pins(void);

void set_led1(void);
void clear_led1(void);

void set_led2(void);
void clear_led2(void);

void set_tx_flow(void);
void set_rx_flow(void);

#endif