#include <avr/io.h>

#define F_CPU       16000000UL
#include <util/delay.h>

#include <avr/interrupt.h>


volatile float duty = 5.0;

void servo_init (void)
{
    TCCR2A |= (1 << COM1A1);
    TCCR2A |= (1 << COM1B1);
    TCCR2B |= (1 << WGM13);
    TCCR2B |= (1 << WGM12);
    TCCR2A |= (1 << WGM11);
    TCCR2B |= (1 << CS12);


    DDRB |= (1 << PORT4);

    ICR1 = 1250-1;
    OCR2A = duty * 0.005 * (1250-1);
}

void manual_servo(int sw2)
{
    if(sw2==1)
    {
      servo_init();

      while(1)
      {
        duty += 0.1;
        OCR2A = duty * 0.005 * (1250-1);
       _delay_ms(70);

        if(duty > 25.0)
         {
          for(duty=25.0; duty>5.0; duty -= 0.1)
            {
               OCR1A = duty * 0.005 * (1250-1);
              _delay_ms(70);
            }
         }
      }
    }

    else if(sw2==2)
    {
      OCR2A =0;
    }
}






