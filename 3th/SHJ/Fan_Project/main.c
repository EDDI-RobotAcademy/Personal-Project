//sw1 = PD2
//sw2 = PD3
//bldc = PB5
//servo = PB4
//temp = PF0
//photocell = PF1
//led = PE0


#define F_CPU                           16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile int sw1=0;
volatile int sw2=0;

void sw_init (void)
{

    EICRA |= (1 << ISC21);
    EICRA |= (1 << ISC31);

    EIMSK |= (1 << INT2);
    EIMSK |= (1 << INT3);


    sei();
}


int main(void)
{
    uart_init();
    sw_init();


    uart_string_trans("Select Mode\n");
    while(1)
    ;
    return 0;
}

ISR(INT2_vect)
{
    sw1++;
    _delay_ms(500);
    if(sw1>4)
    {
     sw1=0;
    }
    switch_mode(sw1, sw2);

}

ISR(INT3_vect)
{
   sw2++;
  _delay_ms(500);
    if(sw2>2)
    {
     sw2=0;
    }

    switch_mode(sw1, sw2);
}

