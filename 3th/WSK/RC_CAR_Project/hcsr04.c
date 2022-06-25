#include "hcsr04.h"

void hcsr04_init(void)
{
    cbi(SREG, 7);
    sbi(DDRB, TRIG);
    cbi(DDRB, ECHO);

    //Pin Change Interrupt Enable
    sbi(PCICR, PCIE0);
    sbi(PCMSK0, PCINT5);

    //Timer Normal mode
    cbi(TCCR0B, WGM02);
    cbi(TCCR0A, WGM01);
    cbi(TCCR0A, WGM00);

    cbi(TCCR0B, CS02 | CS01 | CS00);    //Timer stop

    cbi(TIMSK0, TOIE0); //Timer Overflow Interrupt disable

    sbi(SREG, 7);
}

void trigger_ultrasonic(void)
{
    PORTB |= (1 << TRIG);
    _delay_us(10);
    PORTB |= (1 << TRIG);
}
