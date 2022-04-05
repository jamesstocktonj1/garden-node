#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>

#include "include/io.h"
#include "include/temperature.h"
#include "include/protocol.h"
#include "include/serial.h"
#include "include/timer.h"
#include "include/eeprom.h"

void set_buffer(void);
void parse_data(void);

void acknowledge_data(void);
void check_timeout(void);

MyInfo Me;

int main() {

    //read ID values from eeprom
    Me.My_Node_Num = eeprom_get_node_id();
    Me.My_Zone = eeprom_get_node_group();
    Me.My_Node_Def = eeprom_get_node_type();

    //initialise periferals
    init_pins();
    init_temperature();

    //initialise serial
    serial_init();
    serial_reset();

    //initialise timers
    init_timer();

    set_rx_flow();

    set_led1();
    _delay_ms(1200);
    clear_led1();

    //enable interrupts
    sei();    
    
    while(1) {

        //check for new buffer data then parse data
        if(rxBufferReceived) {

            parse_data();
        }

        //check for variable timeouts
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

    uint16_t temp;
    uint8_t tempUpper, tempLower;

    //create local copy (frees up for incomming messages)
    memcpy(localBuffer, rxBuffer, MSG_BUF_LEN);

    //reset buffer flag
    rxBufferReceived = 0;


    //handle local node data
    if(localBuffer[PROT_POS_NODEID] == Me.My_Node_Num) {

        switch(localBuffer[PROT_POS_ITEM]) {

            case PROT_ITEM_LED1:
                if(localBuffer[PROT_POS_DATA1] == '1') {
                    set_led1();
                }
                else {
                    clear_led1();
                }
                acknowledge_data();
                msCommsTimeout = COMMS_TIMEOUT_ms;
                break;

            case PROT_ITEM_LED2:
                if(localBuffer[PROT_POS_DATA1] == '1') {
                    set_led2();
                }
                else {
                    clear_led2();
                }
                acknowledge_data();
                msCommsTimeout = COMMS_TIMEOUT_ms;
                break;

            case PROT_ITEM_RELAY1:
                if ( (localBuffer[PROT_POS_DATA1] == '1') && (localBuffer[PROT_POS_NODEID] == Me.My_Node_Num) ){
                    //Relay can onlt be set at targetted Node, not a broadcast
                    set_relay();
                }
                else {
                    //But can clear a relay from a broadcast
                    clear_relay();
                }
                acknowledge_data();
                msCommsTimeout = COMMS_TIMEOUT_ms;
                break;

            case PROT_ITEM_RELAY2:
                if ( (localBuffer[PROT_POS_DATA1] == '1') && (localBuffer[PROT_POS_NODEID] == Me.My_Node_Num) ){
                    //Relay can onlt be set at targetted Node, not a broadcast
                    set_relay();
                }
                else {
                    //But can clear a relay from a broadcast
                    clear_relay();
                }
                acknowledge_data();
                msCommsTimeout = COMMS_TIMEOUT_ms;
                break;

            case PROT_ITEM_READ_TEMP:
                temp = get_buffer_temperature();
                tempLower = temp & 0x00ff;
                tempUpper = temp >> 8;

                //reply with temperature
                txBuffer[0] = REPLY_START_CHAR;
                txBuffer[1] = Me.My_Node_Num;
                txBuffer[2] = PROT_ITEM_READ_TEMP;
                txBuffer[3] = tempLower;
                txBuffer[4] = tempUpper;
                txBuffer[5] = END_CHAR;

                _delay_ms(REPLY_DELAY);

                serial_tx(6);
                break;

            default:
                break;
        }
    }

    //handle broadcast data
    else if(localBuffer[PROT_POS_NODEID] == BDCAST_CHAR) {

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

            default:
                break;
        }
    }
}



void acknowledge_data() {

    _delay_ms(REPLY_DELAY);

    txBuffer[PROT_POS_START] = REPLY_START_CHAR;
    txBuffer[PROT_POS_NODEID] = Me.My_Node_Num;
    txBuffer[PROT_POS_ACK] = REPLAY_ACK;
    txBuffer[3] = END_CHAR;
    txBuffer[4] = '\n';

    //set comms 

    serial_tx(5);
}


void check_timeout() {

    if ( (Me.My_Node_Def == NODE_DEF_WATER ) && (0 == msCommsTimeout) ){

        //no comms - reset water ports only at this point
        clear_relay();
    }

    if(msADCTimeout == 0) {
        
        buffer_temperature();
        msADCTimeout = ADC_TIMEOUT_ms;
    }
}