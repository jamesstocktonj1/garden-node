#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "include/io.h"
#include "include/temperature.h"
#include "include/protocol.h"
#include "include/serial.h"

void set_buffer(void);


int main() {

    init_pins();
    init_temperature();

    serial_init();
    sei();
    
    set_buffer();
    serial_tx(8);

    while(1) {
        
        //clear_led1();

        //set_led1();
        _delay_ms(800);

        clear_led1();
        _delay_ms(200);
    }

    return 0;
}


void set_buffer() {

    txBuffer[0] = 'H';
    txBuffer[1] = 'e';
    txBuffer[2] = 'l';
    txBuffer[3] = 'l';
    txBuffer[4] = 'o';
    txBuffer[5] = 'N';
    txBuffer[6] = 'o';
    txBuffer[7] = 'd';
    txBuffer[8] = 'e';
    //txBuffer[9] = '!';
}