#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "include/io.h"





int main() {

    init_pins();

    while(1) {

        set_led1();
        _delay_ms(800);

        clear_led1();
        _delay_ms(200);
    }

    return 0;
}
