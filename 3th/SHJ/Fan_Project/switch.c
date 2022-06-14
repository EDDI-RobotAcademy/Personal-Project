#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>


unsigned int manual_flag1=0;
unsigned int auto_flag1=0;
unsigned int manual_flag2=0;
unsigned int auto_flag2=0;
unsigned int reset_timer =0;

int switch_mode (int sw1, int sw2)
{
   if(sw1%2==1 && manual_flag2==0 && auto_flag2==0)
    {
     manual_flag1 =1;
     auto_flag1 =0;

    }

    else if (sw1%2==0 && manual_flag2==0 && auto_flag2==0)
    {
        auto_flag1 =1;
        manual_flag1 =0;

    }

   if (sw2==true && manual_flag1 ==1)
    {
        manual_flag2 =1;
    }
    else if(sw2==true && auto_flag1 ==1)
    {
        auto_flag2 =1;
    }



      if(sw2==3 && manual_flag2==1)
        {
         manual_flag2=0;
         manual_flag1=0;
         sw1=0;
         sw2=0;
         uart_string_trans("Select Mode\n");
        }
       if(sw2==3 && auto_flag2==1 )
        {
         auto_flag2=0;
         auto_flag1=0;
         sw1=0;
         sw2=0;
         uart_string_trans("Select Mode\n");
        }

    lcd_mode1(manual_flag1, auto_flag1);
    lcd_mode2(manual_flag2, auto_flag2);
    fan(sw1, sw2, manual_flag2);
    manual_BLDC(sw1, manual_flag2, auto_flag2);
    manual_servo(sw2, manual_flag2);
    //temp_mode(auto_flag2);
    //photocell_mode(auto_flag2);
}

