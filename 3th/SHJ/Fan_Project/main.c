//sw1 = PD2
//sw2 = PD3
//bldc = PB5
//servo = PE3
//temp = PF0
//photocell = PF1
//led = PE0
//lcd = PA0~1, PC0~7


#define F_CPU                           16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>

volatile int sw1_flag=0;
volatile int sw2_flag=0;
int sw1=0;
int sw2=0;

void sw_init (void)
{

    EICRA |= (1 << ISC21);
    //EICRA |= (1 << ISC20);
    EICRA |= (1 << ISC31);
    //EICRA |= (1 << ISC30);

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
  {
     if(sw1_flag==true)
    {
        sw1++;

        if(sw1>4)
        {
         sw1=0;
        }

        switch_mode(sw1, sw2);
        sw1_flag=false;
    }

    if(sw2_flag==true)
    {
        sw2++;

        if(sw2>3)
        {
         sw2=0;
        }

      switch_mode(sw1, sw2);
      sw2_flag=false;
    }

  }
 //_delay_ms(500);
 //   EIFR |= (1 << INTF3);
 //   _delay_ms(500);
 //   EIFR |= (1 << INTF2);
 }

ISR(INT2_vect)
{
    sw1_flag = true;
}

ISR(INT3_vect)
{
    sw2_flag = true;
}

