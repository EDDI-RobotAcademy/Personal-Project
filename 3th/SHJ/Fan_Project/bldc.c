#include <avr/io.h>

#define F_CPU       16000000UL
#include <util/delay.h>

#include <avr/interrupt.h>


void BLDC_init(void)
{

    TCCR1A |= (1 << COM1A1);
    TCCR1A |= (1 << COM1B1);
    TCCR1B |= (1 << WGM13);
    TCCR1B |= (1 << WGM12);
    TCCR1A |= (1 << WGM11);
    TCCR1B |= (1 << CS12);

    DDRB = (1 << PORT5);

    ICR1 = 1250-1;
}

void manual_BLDC(int sw1, int manual_flag2)
{
 if(manual_flag2 == 1)
  {
   BLDC_init();
   if(sw1 ==1)
   {
    OCR1A = 0.3 * (1250-1);
   }
   else if (sw1 ==2)
   {
    OCR1A = 0.6 * (1250-1);

   }

    else if (sw1 ==3)
    {
     OCR1A = 0.9 * (1250-1);
    }

    else if (sw1 ==4)
    {
     OCR1A=0;
    }

   }
   else
    {
     OCR1A=0;
    }
  }


void auto_BLDC(int temp, int auto_flag2)
{
   if(auto_flag2 == 1)
  {
   BLDC_init();
   if(temp ==1)
   {
    OCR1A = 0.3 * (1250-1);
   }
   else if (temp ==2)
   {
    OCR1A = 0.6 * (1250-1);

   }

    else if (temp ==3)
    {
     OCR1A = 0.9 * (1250-1);
    }

    else if (temp ==4)
    {
     OCR1A=0;
    }

   }
   else
    {
     OCR1A=0;
    }
  }


