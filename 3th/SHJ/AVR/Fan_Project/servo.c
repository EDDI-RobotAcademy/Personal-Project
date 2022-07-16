#define F_CPU       16000000UL
#define RESET       0
#define SERVOR_ANGULAR  6.245   //0.005 * (1250-1)
#define SERVOR_INIT     31.225  //5.0 * 0.005 * (1250-1)


#include "servo.h"
#include "lcd.h"
#include "uart.h"


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
    OCR3A = SERVOR_INIT;
}

void servo_counter_clockwise (float duty)
{
    uart_string_trans("counter clockwise\n");
    lcd_write_string("counter clockwise\n");

    OCR3A = duty * SERVOR_ANGULAR;
}

void servo_clockwise (float duty)
{
  uart_string_trans("clockwise\n");
  lcd_write_string("clockwise\n");

  OCR3A = duty * SERVOR_ANGULAR;
}

void servo_stop (void)
{
  uart_string_trans("TURN STOP\n");
  lcd_write_string("TURN STOP\n");

   OCR3A = RESET;
}





