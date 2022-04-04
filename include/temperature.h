#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <avr/io.h>


#define TEMP_CONVERSION 0.1075
#define BUFFER_SIZE 16

extern uint8_t buffer_pointer;
extern uint16_t temperature_buffer[BUFFER_SIZE];

void init_temperature(void);
uint16_t get_temperature(void);

void buffer_temperature(void);
uint16_t get_buffer_temperature(void);


#endif