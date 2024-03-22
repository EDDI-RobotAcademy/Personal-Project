#ifndef __PIN_H__
#define __PIN_H__

enum PIN_MAP
{
	// PORTB	00000 ~ 00111
	PIN_PB0=0,
	PIN_PB1=1,
	PIN_PB2=2,
	PIN_PB3=3,
	PIN_PB4=4,
	PIN_PB5=5,
	PIN_PB6=6,
	PIN_PB7=7,

	// PORTC	01000 ~ 01110
	PIN_PC0=8,
	PIN_PC1=9,
	PIN_PC2=10,
	PIN_PC3=11,
	PIN_PC4=12,
	PIN_PC5=13,
	PIN_PC6=14,

	// PORTD	10000 ~ 10111
	PIN_PD0=16,
	PIN_PD1=17,
	PIN_PD2=18,
	PIN_PD3=19,
	PIN_PD4=20,
	PIN_PD5=21,
	PIN_PD6=22,
	PIN_PD7=23,
	
	PIN_END
};

enum PIN_INPUT_OUTPUT_MODE
{
    GPIO_SET_INPUT_MODE=0,
    GPIO_SET_OUTPUT_MODE=1
};

void request_pin_config(int8_t pin_num, int8_t gpio_direction);

#endif
