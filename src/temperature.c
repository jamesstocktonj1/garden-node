#include <avr/io.h>
#include "../include/temperature.h"


void init_temperature() {

    //set pin to input
    DDRC &=  ~_BV(PC0);

    //set ADC source to 1.1V (mux set to ADC0)
    ADMUX = 0;
    ADMUX |= _BV(REFS0) | _BV(REFS1);
    //ADMUX |= _BV(ADLAR);

    //enable ADC
    ADCSRA |= _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);
 
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