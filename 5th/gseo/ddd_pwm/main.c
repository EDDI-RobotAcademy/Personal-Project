/*
 */

#include <avr/io.h>
#include <avr/sfr_defs.h>

#include <util/delay.h>
#include <stdio.h>

#include "domain/console/usart_printf.h"
#include "domain/pin/pin.h"

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

    // PB5 Is wired to LED.
    // DDRB = 0x20;

    //  [DDD-PWM-6]
    //  TODO : Add USART0 Initialization for Putty Debug Message.
    usart_initialize();
    stdout = &uart_output;
	_delay_ms(10);

    //  [DDD-PWM-0]
    //  TODO : 핀 도메인에 원하는 핀의 설정을 요청한다.

	request_pin_config(PIN_PB5, GPIO_SET_OUTPUT_MODE);


    for(;;)
    {
		// printf("Hello AVR printf\n");
		LED_Toggle();
		_delay_ms(500);
	}

    return 0;
}
