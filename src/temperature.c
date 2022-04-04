#include "../include/temperature.h"


uint8_t buffer_pointer;
uint16_t temperature_buffer[BUFFER_SIZE];


void init_temperature() {

    //set pin to input
    DDRC &=  ~_BV(PC0);

    //set ADC source to 1.1V (mux set to ADC0)
    ADMUX = 0;
    ADMUX |= _BV(REFS0) | _BV(REFS1);
    //ADMUX |= _BV(ADLAR);

    //enable ADC
    ADCSRA |= _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);

    //initialise buffer
    buffer_pointer = 0;
}


uint16_t get_temperature() {

    //start conversion
    ADCSRA |= _BV(ADSC);

    //wait for conversion to be complete
    while(ADCSRA & _BV(ADSC));

    //combine upper and lower register values
    uint8_t lowerReg = ADCL;
	uint8_t upperReg = ADCH;

    uint16_t adc = (upperReg << 8) + (lowerReg);

    //return (uint16_t)(((uint8_t)ADCH << 2) + ((uint8_t)ADCL >> 6));
    return adc;
}

void buffer_temperature() {

    //read temperature
    temperature_buffer[buffer_pointer] = get_temperature();
    
    //increment buffer
    buffer_pointer = (buffer_pointer < (BUFFER_SIZE - 2)) ? buffer_pointer + 1 : 0;
}

uint16_t get_buffer_temperature() {

    uint32_t total = 0;
    int i;

    for(i=0; i<BUFFER_SIZE; i++) {
        total += temperature_buffer[i];
    }

    return total / BUFFER_SIZE;
}