#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>



//Catchall for setting up bad interrupt
#if 0
    https://www.nongnu.org/avr-libc/user-manual/group__avr__interrupts.html
    ADC_vect, ANALOG_COMP_vect
    EE_READY_vect
    INT0_vect,     INT1_vect
    PCINT0_vect,     PCINT1_vect,     PCINT2_vect,
    SPI_STC_vect
    SPM_READY_vect
    TIMER0,1,2 _COMPA_vect, TIMER0_COMPB_vect, TIMER0_OVF_vect,
    TWI_vect
    USART_RX_vect, USART_TX_vectm USART_UDRE_vect
    WDT_vect

#endif
ISR(BADISR_vect)
{
    // user code here
}



//Setting us a ms interrupt
ISR(TIMER0_OVF_vect) {
    /* this ISR is called when TIMER0 overflows */
    TCNT0 = msTIMER_RELOAD_VALUE;

    if (msTimer) {

        msTimer --;
    }
    
    if (msCommsTimeout) {
        
        msCommsTimeout --;
    }
}

void init_timer() {
    //8-bit Timer Counter

    /*
    * set up cpu clock divider. the TIMER0 overflow ISR toggles the
    * output port after enough interrupts have happened.
    * 8MHz (FCPU) / 64 (CS0 = 3) -> 125,000 incr/sec
    * for overflow every 1ms, reload (256-125) = 131
    */

    // Port to normal operation, no capture compare or PWM
    TCCR0A = 0;

    //Clock source CS02..0 = 011 clkIO/64
    //1MHz/256 = 31,250/second
    TCCR0B |=  _BV(CS01) | _BV(CS00);

    //set timer to ~1ms
    TCNT0 = msTIMER_RELOAD_VALUE; 
    
    /* Enable Timer Overflow Interrupts */
    TIMSK0 |= _BV(TOIE0);

    //initialise variables
    msTimer = 0;
    msCommsTimeout = 0;    
}
