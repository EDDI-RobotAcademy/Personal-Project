#define F_CPU       16000000UL

#include <avr/io.h>
#include <util/delay.h>
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

void servo_start (void)
{
  uart_string_trans("Turn Start\n");
  lcd_write_string("Turn Start\n");

  while(1)
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
}

void servo_stop (void)
{
  uart_string_trans("Turn Stop\n");
  lcd_write_string("Turn Stop\n");
  while(1)
  {
   OCR3A = 0;
  }

}





