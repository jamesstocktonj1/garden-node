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
    sei();
    
    
    while(1) {

        if(rxBufferReceived) {

            parse_data();
        }
    }

    return 0;
}


void set_buffer() {

    //set buffer to "HelloNode!"
    txBuffer[0] = 'H';
    txBuffer[1] = 'e';
    txBuffer[2] = 'l';
    txBuffer[3] = 'l';
    txBuffer[4] = 'o';
    txBuffer[5] = 'N';
    txBuffer[6] = 'o';
    txBuffer[7] = 'd';
    txBuffer[8] = 'e';
    txBuffer[9] = '!';
    txBuffer[10] = '\n';
}



void parse_data() {

    char localBuffer[MSG_BUF_LEN];

    //create local copy (frees up for incomming messages)
    memcpy(localBuffer, rxBuffer, MSG_BUF_LEN);

    //reset buffer flag
    rxBufferReceived = 0;

    //handle data sent to node
    if(localBuffer[PROT_POS_NODEID] == MY_NODE) {
        
        switch(localBuffer[PROT_POS_ITEM]) {

            case PROT_ITEM_LED1:
                if(localBuffer[PROT_POS_DATA1] == '1') {
                    set_led1();
                }
                else {
                    clear_led1();
                }
                break;

            case PROT_ITEM_LED2:
                if(localBuffer[PROT_POS_DATA1] == '1') {
                    set_led2();
                }
                else {
                    clear_led2();
                }
                break;

            case PROT_ITEM_RELAY:
                if(localBuffer[PROT_POS_DATA1] == '1') {
                    set_relay();
                }
                else {
                    clear_relay();
                }
                break;

            default:
                break;
        }

        //simple response
        txBuffer[0] = REPLY_START_CHAR;
        txBuffer[1] = 'A';
        txBuffer[2] = END_CHAR;
        txBuffer[3] = '\n';

        serial_tx(4);
    }

    //handle global broadcast
    else if(localBuffer[PROT_POS_NODEID] == BDCAST_CHAR) {
        //handle broadcast data
    }

}