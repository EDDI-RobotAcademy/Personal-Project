#define F_CPU       16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include<stdbool.h>


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

void bldc_low (void)
{

    uart_string_trans("Low\n");
    lcd_write_string("Low\n");

    OCR1A = 0.3 * (1250-1);

}



void bldc_middle (void)
{
 cli();
  uart_string_trans("Middle\n");
  lcd_write_string("Middle\n");

   OCR1A = 0.6 * (1250-1);
}

void bldc_high (void)
{

 uart_string_trans("High\n");
 lcd_write_string("High\n");

 OCR1A = 0.9 * (1250-1);
}

void bldc_stop (void)
{

 uart_string_trans("Stop\n");
 lcd_write_string("Stop\n");

   OCR1A = 0.0 * (1250-1);
}





