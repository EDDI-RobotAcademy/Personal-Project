#define F_CPU       16000000UL

#define      LOW_SPEED        1
#define      MIDDLE_SPEED     2
#define      HIGH_SPEED       3
#define      STOP             4

#define     TURN_START     2
#define     TURN_STOP      3
#define     RESET_MODE     4
#define     RESET          0

#define     MANUAL          1
#define     AUTO            0

#define     MANUAL_MODE     1
#define     AUTO_MODE       1

#define     COUNTERCLOCKWISE    5
#define     CLOCKWISE           25


#include "uart.h"
#include "lcd.h"
#include "switch.h"
#include "bldc.h"
#include "servo.h"
#include "temp.h"
#include "phtocell.h"
#include "bluetooht.h"


bool manual_mode_select=0;
bool auto_mode_select=0;
bool manual_mode_run=0;
bool auto_mode_run=0;
volatile int intensity_sw=0;
volatile int action_sw=0;
float duty = 5.0;

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

void switch_mode (void)
{
    if(intensity_sw%2==MANUAL && manual_mode_run==RESET && auto_mode_run==RESET)
    {
     manual_mode_select =1;
     auto_mode_select =0;
     uart_string_trans("Manual Mode\n");
     lcd_write_string("Manual Mode\n");
    }

    else if (intensity_sw%2==AUTO && manual_mode_run==RESET && auto_mode_run==RESET)
    {
        auto_mode_select =1;
        manual_mode_select =0;
        uart_string_trans("Auto Mode\n");
        lcd_write_string("Auto Mode\n");
    }

       if(action_sw==TURN_START)
         {
            duty +=0.1;
            servo_counter_clockwise(duty);

            if(duty>CLOCKWISE)
            {
             for(duty=CLOCKWISE; duty>COUNTERCLOCKWISE; duty-=0.1)
             {
                servo_clockwise(duty);
             }

            }
         }

         if(action_sw==TURN_STOP)
         {
          servo_stop();
         }



   if (manual_mode_select ==MANUAL_MODE)
    {
        manual_mode_run =1;
        uart_string_trans("Manual Mode run\n");
        lcd_write_string("Manual Mode run\n");

       if(intensity_sw==LOW_SPEED)
       {
           bldc_low();
       }

        if(intensity_sw==MIDDLE_SPEED)
        {
           bldc_middle();
         }

          if(intensity_sw==HIGH_SPEED)
          {
            bldc_high();
          }

         if(intensity_sw==STOP)
         {
           bldc_stop();
         }

     }

    else if(auto_mode_select ==AUTO_MODE)
    {
        auto_mode_run =1;
        uart_string_trans("Auto Mode run\n");
        lcd_write_string("Auto Mode run\n");
        temperature_sensor();
        photocell_mode();
    }


      if(action_sw==RESET_MODE && (manual_mode_run==MANUAL_MODE || auto_mode_run==AUTO_MODE))
        {
            auto_mode_run=0;
            auto_mode_select=0;
            manual_mode_run=0;
            manual_mode_select=0;
            intensity_sw=0;
            action_sw=0;
            uart_string_trans("Select Mode\n");
            lcd_write_string("Select Mode\n");
        }



}

ISR(INT2_vect)
{
    intensity_sw ++;

 if(intensity_sw >4)
  {
    intensity_sw=0;
  }
     _delay_ms(10);
     EIFR |= (1 << INTF2);

}

ISR(INT3_vect)
{
    action_sw ++;

  if(action_sw>4)
   {
    action_sw=0;
   }

      _delay_ms(10);
     EIFR |= (1 << INTF3);
}
