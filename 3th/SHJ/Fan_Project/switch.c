#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>

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

      if(action_sw==2)
        {
           servo_start();
        }

        if(action_sw==3)
        {
           servo_stop();
        }

   if (action_sw==1 && manual_mode_select ==1)
    {
        manual_mode_run =1;
        uart_string_trans("Manual Mode run\n");
        lcd_write_string("Manual Mode run\n");

       if(intensity_sw==1)
        {
         bldc_low();
        }

       if(intensity_sw==2)
        {
         bldc_middle();
        }

        if(intensity_sw==3)
        {
         bldc_high();
        }

        if(intensity_sw==4)
        {
         bldc_stop();
        }

    }

    else if(action_sw==1 && auto_mode_select ==1)
    {
        auto_mode_run =1;
        uart_string_trans("Auto Mode run\n");
        lcd_write_string("Auto Mode run\n");
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

