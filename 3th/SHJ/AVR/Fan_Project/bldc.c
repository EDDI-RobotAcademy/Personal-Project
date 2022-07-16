#define F_CPU       16000000UL
#define BLDC_STOP           62.45    //10* 0.005 * (1250-1)
#define BLDC_LOW_SPEED      81.185   //13 * 0.005 * (1250-1)
#define BLDC_MIDDLE_SPEED   99.92  //16 * 0.005 * (1250-1)
#define BLDC_HIGH_SPEED     124.9   //20 * 0.005 * (1250-1)

#include "bldc.h"
#include "lcd.h"
#include "uart.h"


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

    OCR1A = BLDC_LOW_SPEED;
}

void bldc_middle (void)
{
  uart_string_trans("Middle\n");
   lcd_write_string("Middle\n");

   OCR1A = BLDC_MIDDLE_SPEED;
}

void bldc_high (void)
{
 uart_string_trans("High\n");
 lcd_write_string("High\n");

 OCR1A = BLDC_HIGH_SPEED;

}

void bldc_stop (void)
{
  uart_string_trans("Stop\n");
  lcd_write_string("Stop\n");

   OCR1A = BLDC_STOP;
 }








