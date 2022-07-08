#define F_CPU       16000000UL

#define      low_speed        1
#define      middle_speed     2
#define      high_speed       3
#define      stop             4

#define     turn_start     2
#define     turn_stop      3
#define     reset_mode     4
#define     reset          0

#define     manual          1
#define     auto            0

#define     manual_mode     1
#define     auto_mode       1

#define     counterclockwise    5
#define     clockwise           25


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
    if(intensity_sw%2==manual && manual_mode_run==reset && auto_mode_run==reset)
    {
     manual_mode_select =1;
     auto_mode_select =0;
     uart_string_trans("Manual Mode\n");
     lcd_write_string("Manual Mode\n");
    }

    else if (intensity_sw%2==auto && manual_mode_run==reset && auto_mode_run==reset)
    {
        auto_mode_select =1;
        manual_mode_select =0;
        uart_string_trans("Auto Mode\n");
        lcd_write_string("Auto Mode\n");
    }

       if(action_sw==turn_start)
         {
            duty +=0.1;
            servo_counter_clockwise(duty);

            if(duty>clockwise)
            {
             for(duty=clockwise; duty>counterclockwise; duty-=0.1)
             {
                servo_clockwise(duty);
             }

            }
         }

         if(action_sw==turn_stop)
         {
          servo_stop();
         }



   if (manual_mode_select ==manual_mode)
    {
        manual_mode_run =1;
        uart_string_trans("Manual Mode run\n");
        lcd_write_string("Manual Mode run\n");

       if(intensity_sw==low_speed)
       {
           bldc_low();
       }

        if(intensity_sw==middle_speed)
        {
           bldc_middle();
         }

          if(intensity_sw==high_speed)
          {
            bldc_high();
          }

         if(intensity_sw==stop)
         {
           bldc_stop();
         }

     }

    else if(auto_mode_select ==auto_mode)
    {
        auto_mode_run =1;
        uart_string_trans("Auto Mode run\n");
        lcd_write_string("Auto Mode run\n");
        temperature_sensor();
        photocell_mode();
    }


      if(action_sw==reset_mode && (manual_mode_run==manual_mode || auto_mode_run==auto_mode))
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


         if(action_sw==turn_stop)
         {
          servo_stop();
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
