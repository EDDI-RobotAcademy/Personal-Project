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

#include "uart.h"

volatile int intensity_sw_flag=0;
volatile int action_sw_flag=0;
int intensity_sw=0;
int action_sw=0;

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
    lcd_init();
    sw_init();
    BLDC_init();
    servo_init();

    uart_string_trans("Select Mode\n");
    lcd_write_string("Select Mode\n");

  while(1)
  {
     if(intensity_sw_flag==true)
    {
        intensity_sw++;

        if(intensity_sw>4)
        {
         intensity_sw=0;
        }

        switch_mode(intensity_sw, action_sw);
        intensity_sw_flag=false;
    }

    if(action_sw_flag==true)
    {
        action_sw++;

        if(action_sw>4)
        {
         action_sw=0;
        }

      switch_mode(intensity_sw, action_sw);
      action_sw_flag=false;
    }

  }

 }

ISR(INT2_vect)
{
    intensity_sw_flag = true;

     _delay_ms(100);
     EIFR |= (1 << INTF2);
}

ISR(INT3_vect)
{
    action_sw_flag = true;
      _delay_ms(100);
     EIFR |= (1 << INTF3);
}

