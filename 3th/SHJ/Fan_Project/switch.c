#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


unsigned int manual_flag=0;
unsigned int auto_flag=0;


int switch_mode (int sw1, int sw2)
{

   if (sw1 %2 == 1 & sw2 ==1)
    {
      if(manual_flag ==0 & auto_flag==0)
      {
        manual_flag = 1;
        auto_flag = 0;
      }

    }
    else if(sw1 %2 ==0 & sw2 ==1)
    {
      if(auto_flag ==0 & manual_flag==0)
      {
        auto_flag =1;
        manual_flag = 0;
      }
    }

    lcd_mode(sw1, sw2, manual_flag, auto_flag);
}





