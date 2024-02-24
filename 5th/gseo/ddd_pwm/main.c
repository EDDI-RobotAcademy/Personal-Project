/*
 */

#include <avr/io.h>
#include <avr/sfr_defs.h>

#include <util/delay.h>
#include <stdio.h>

#include "usart_printf.h"

#define F_CPU       16000000L

void LED_Toggle(void)
{
    PORTB = 0x00;
    _delay_ms(500);
    PORTB = 0x20;
    _delay_ms(500);
}

int main(void)
{

    // Insert code
    DDRB = 0x20;

    // TODO : USART0 Initialization for Putty Debug Message [DDD-PWM-6]
    usart_initialize();
    stdout = &uart_output;
	_delay_ms(10);

    for(;;)
    {
		printf("Hello AVR printf\n");
		_delay_ms(1000);
	}

    return 0;
}
