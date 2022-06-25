/*
 */

#include <avr/io.h>
#include "hcsr04.h"

int main(void)
{

    // Insert code
    hcsr04_init();

    while(1)
    {
        trigger_ultrasonic();
        _delay_ms(1000);
        get_distance();
    }


    return 0;
}

ISR(PCINT0_vect)
{
    sbi(PCIFR, PCIF0);  //PCINT0 flag clear
    if((PORTB & ECHO) == 1)
    {
        //Clock select : 16MHz / 8 = 2MHz Timer start
        TCNT0 = 0;
        cbi(TCCR0B, CS02);
        sbi(TCCR0B, CS01);
        cbi(TCCR0B, CS00);
    }
    else if((PORTB & ECHO) == 0)
    {
        duration = TCNT0 * 2; //1 tick에 2us
        cbi(TCCR0B, CS02 | CS01 | CS00);    //Timer stop
    }
}
