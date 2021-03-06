#ifndef SERIAL_H
#define SERIAL_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "protocol.h"
#include "timer.h"

#define SERIAL_BAUD 9600

//timings
#define TX_START_DELAY 1
#define END_DELAY 0

#define REPLY_DELAY 1

#define COMMS_TIMEOUT_ms 5000


//tx variables
volatile uint8_t txBuffer[MSG_BUF_LEN];
volatile uint8_t txBufferIndex;
volatile uint8_t txBufferLength;
volatile uint8_t transmitFlag;

//rx variables
uint8_t rxBuffer[MSG_BUF_LEN];
volatile uint8_t rxBufferIndex;
volatile uint8_t rxBufferReceived;

void serial_init(void);
void serial_reset(void);
void serial_tx(uint8_t bufferSize);


#endif