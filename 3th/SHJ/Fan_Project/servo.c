#include <avr/io.h>

#define F_CPU       16000000UL
#include <util/delay.h>
#include <stdbool.h>
#include <avr/interrupt.h>


float duty = 5.0;

void servo_init (void)
{
    TCCR3A |= (1 << COM3A1);
    TCCR3A |= (1 << COM3B1);
    TCCR3A |= (1 << COM3C1);
    TCCR3B |= (1 << WGM33);
    TCCR3B |= (1 << WGM32);
    TCCR3A |= (1 << WGM31);
    TCCR3B |= (1 << CS32);


    DDRE |= (1 << PORT3);

    ICR3 = 1250-1;
    OCR3A = duty * 0.005 * (1250-1);
}

void manual_servo(int sw2, int manual_flag2)
{
   servo_init();

     if(manual_flag2==1)
     {
        while(1)
        {
          if(sw2==1)
          {
            duty += 0.1;
            OCR3A = duty * 0.005 * (1250-1);
            _delay_ms(70);

            if(duty > 25.0)
            {
                for(duty=25.0; duty>5.0; duty -= 0.1)
                {
                    OCR3A = duty * 0.005 * (1250-1);
                    _delay_ms(70);
                }
            }
          }

           if(sw2==2)
           {
             OCR3A=0;
           }
        }
      }
      else
      {
        OCR3A=0;
      }
}






