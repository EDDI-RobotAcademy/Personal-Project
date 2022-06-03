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

void manual_BLDC(sw1, manual_flag)
{
 if(manual_flag == 1)
  {
   BLDC_init();
   switch (sw1)
   {
    case 1:
           OCR1A = 0.3 * (1250-1);
           break;
    case 2:
           OCR1A = 0.6 * (1250-1);
           break;
    case 3:
           OCR1A = 0.9 * (1250-1);
           break;
    case 4:
           sw1=0;
           OCR1A=0;
           break;
   }
  }

}

void auto_BLDC(temp, auto_flag)
{
   if(auto_flag == 1)
  {
   BLDC_init();
   switch (temp)
   {
    case 1:
           OCR1A = 0.3 * (1250-1);
           break;
    case 2:
           OCR1A = 0.6 * (1250-1);
           break;
    case 3:
           OCR1A = 0.9 * (1250-1);
           break;

   }
  }
}


