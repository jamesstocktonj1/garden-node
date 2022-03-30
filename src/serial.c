#include "../include/serial.h"
#include "../include/io.h"


ISR(USART_RX_vect) {

    //check for buffer overflow (invalid message)
    if(rxBufferIndex >= (MSG_BUF_LEN - 1)) {

        rxBufferReceived = 0;
        rxBufferIndex = 0;
        rxBuffer[0] = 0;
    }

    //read in value to buffer
    rxBuffer[rxBufferIndex] = UDR0;

    //handle start character
    if(rxBuffer[rxBufferIndex] == RX_START_CHAR) {

        //rxBuffer[0] = rxBuffer[rxBufferIndex];
        rxBufferIndex = 1;
    }

    //handle end character
    else if(rxBuffer[rxBufferIndex] == END_CHAR) {
        
        rxBufferReceived = 1;
        rxBufferIndex = 0;

        set_rx_flow();
    }

    //increment buffer index
    else if(rxBufferIndex > 0) {

        rxBufferIndex++;
    }
}


ISR(USART_TX_vect) {

    //if data still to send
    if(txBufferIndex <= txBufferLength) {

        UDR0 = txBuffer[txBufferIndex];
        txBufferIndex++;
    }
    
    //send end character
    else {

        //UDR0 = '\n';

        //disable tx interrupt
        UCSR0B &= ~(_BV(TXCIE0));

        transmitFlag = 0;
    }
}


void serial_init(void) {

    //set baud rate
    UBRR0H = (F_CPU/(SERIAL_BAUD*16L)-1) >> 8;
	UBRR0L = (F_CPU/(SERIAL_BAUD*16L)-1);

    //enable tx and rx
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);

    //enable rx interrupt
    UCSR0B |= _BV(RXCIE0);

    //enable tx interrupt
    //UCSR0B |= _BV(TXCIE0);

    //set to data length to 8 bits
    UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);

    serial_reset();
}

void serial_reset(void) {

    //disable tx interrupt
    UCSR0B &= ~(_BV(TXCIE0));

    //reset tx variables
    txBufferIndex = 0;
    txBufferLength = 0;
    transmitFlag = 0;

    //reset rx variables
    rxBufferIndex = 0;
    rxBufferReceived = 0;

    //set flow control
    //set_rx_flow();
}


void serial_tx(uint8_t bufferSize) {

    //wait for write complete
    while(!(UCSR0A & _BV(UDRE0)));

    
    if(bufferSize <= MSG_BUF_LEN) {
        
        //set flow control
        set_tx_flow();

        txBufferLength = bufferSize;
        transmitFlag = 1;
        txBufferIndex = 1;

        //send first value
        UDR0 = txBuffer[0];

        //enable tx interrupt
        UCSR0B |= _BV(TXCIE0);
    }
}
