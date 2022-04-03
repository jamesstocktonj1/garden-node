#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>

#include "include/io.h"
#include "include/temperature.h"
#include "include/protocol.h"
#include "include/serial.h"
#include "include/timer.h"

#define MY_NODE_NUM '1'
#define MY_ZONE NODE_ZONE_GREENHOUSE
#define MY_NODE_TYPE NODE_DEF_WATER

void set_buffer(void);
void parse_data(void);

void acknowledge_data(void);
void check_timeout(void);



int main() {

    init_pins();
    init_temperature();

    serial_init();
    serial_reset();

    init_timer();

    set_rx_flow();

    set_led1();
    _delay_ms(1200);
    clear_led1();

    sei();
    
    
    while(1) {

        if(rxBufferReceived) {

            parse_data();
        }

        check_timeout();
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
    if(localBuffer[PROT_POS_NODEID] == MY_NODE_NUM) {
        
        msCommsTimeout = COMMS_TIMEOUT_ms;
        
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

        acknowledge_data();
    }

    //handle global broadcast
    else if(localBuffer[PROT_POS_NODEID] == BDCAST_CHAR) {
        //handle broadcast data
    }
}



void acknowledge_data() {

    _delay_ms(REPLY_DELAY);

    txBuffer[PROT_POS_START] = REPLY_START_CHAR;
    txBuffer[PROT_POS_NODEID] = MY_NODE_NUM;
    txBuffer[PROT_POS_ACK] = REPLAY_ACK;
    txBuffer[3] = END_CHAR;
    txBuffer[4] = '\n';

    //set comms 

    serial_tx(5);
}


void check_timeout() {

    if ( (MY_NODE_TYPE == NODE_DEF_WATER ) && (0 == msCommsTimeout) ){

        //no comms - reset water ports only at this point
        clear_relay();
    }
}