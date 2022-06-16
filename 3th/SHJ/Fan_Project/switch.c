
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#define      low        1
#define      middle     2
#define      high       3
#define      stop       4

#define     turn_start     2
#define     turn_stop      3

#include "uart.h"


unsigned int manual_mode_select=0;
unsigned int auto_mode_select=0;
unsigned int manual_mode_run=0;
unsigned int auto_mode_run=0;


void switch_mode (int intensity_sw, int action_sw)
{

   if(intensity_sw%2==1 && manual_mode_run==0 && auto_mode_run==0)
    {
     manual_mode_select =1;
     auto_mode_select =0;
     uart_string_trans("Manual Mode\n");
     lcd_write_string("Manual Mode\n");
    }

    else if (intensity_sw%2==0 && manual_mode_run==0 && auto_mode_run==0)
    {
        auto_mode_select =1;
        manual_mode_select =0;
        uart_string_trans("Auto Mode\n");
        lcd_write_string("Auto Mode\n");
    }


   if (action_sw==1 && manual_mode_select ==1)
    {
        manual_mode_run =1;
        uart_string_trans("Manual Mode run\n");
        lcd_write_string("Manual Mode run\n");

    while(1)
    {
     switch(intensity_sw)
       {
         case low : bldc_low(); break;

         case middle : bldc_middle(); break;

         case high : bldc_high(); break;

         case stop :  bldc_stop(); break;
        }
      }
    }


    else if(action_sw==1 && auto_mode_select ==1)
    {
        auto_mode_run =1;
        uart_string_trans("Auto Mode run\n");
        lcd_write_string("Auto Mode run\n");
    }

    switch(action_sw == turn_start)
        {
          case turn_start : servo_start(); break;

          case turn_stop : servo_stop(); break;
        }

      if(action_sw==4 && (manual_mode_run==1 || auto_mode_run==1))
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

