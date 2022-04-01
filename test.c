#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>

#include "include/io.h"
#include "include/temperature.h"
#include "include/protocol.h"
#include "include/serial.h"

#define MY_NODE '1'

void set_buffer(void);
void parse_data(void);




int main() {

    init_pins();
    init_temperature();

    serial_init();
    serial_reset();

    set_tx_flow();

    set_led1();
    _delay_ms(1200);
    clear_led1();

    sei();
    
    
    while(1) {

        txBuffer[0] = RX_START_CHAR;
        txBuffer[1] = MY_NODE;
        txBuffer[2] = '1';
        txBuffer[3] = '1';
        txBuffer[4] = END_CHAR;
        set_led1();
        serial_tx(5);
        _delay_ms(1000);

        txBuffer[0] = RX_START_CHAR;
        txBuffer[1] = MY_NODE;
        txBuffer[2] = '1';
        txBuffer[3] = '0';
        txBuffer[4] = END_CHAR;
        clear_led1();
        serial_tx(5);
        _delay_ms(1000);

        txBuffer[0] = RX_START_CHAR;
        txBuffer[1] = MY_NODE;
        txBuffer[2] = '2';
        txBuffer[3] = '1';
        txBuffer[4] = END_CHAR;
        set_led2();
        serial_tx(5);
        _delay_ms(1000);

        txBuffer[0] = RX_START_CHAR;
        txBuffer[1] = MY_NODE;
        txBuffer[2] = '2';
        txBuffer[3] = '0';
        txBuffer[4] = END_CHAR;
        clear_led2();
        serial_tx(5);
        _delay_ms(1000);
    }

    return 0;
}