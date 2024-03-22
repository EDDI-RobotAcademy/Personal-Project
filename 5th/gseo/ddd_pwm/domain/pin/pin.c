#include <stdio.h>
#include <avr/io.h>
#include "pin.h"

static unsigned char get_pin_address[3] ={
	(unsigned char) 0x24,
	(unsigned char) 0x27,
	(unsigned char) 0x2a
};

void request_pin_config(int8_t pin_num, int8_t gpio_mode){
	printf("pin_num = %d, gpio_mode = %d\n", pin_num, gpio_mode);

	int pin_port = 0;
	volatile unsigned char pin_address = 0;
	/*
	pin_port = 0, DDRB (0x24)
	pin_port = 1, DDRC (0x27)
	pin_port = 2, DDRD (0x2a)
	*/
	pin_port = pin_num >> 3;

	pin_address = get_pin_address[pin_port];

	printf("pin_address = 0x%x\n", pin_address);



	(*(volatile unsigned char *)pin_address) = 0x20;
}
