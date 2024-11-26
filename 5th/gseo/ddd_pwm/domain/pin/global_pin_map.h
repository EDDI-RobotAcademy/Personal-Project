#ifndef __GLOBAL_PIN_MAP_H__
#define __GLOBAL_PIN_MAP_H__

static unsigned char *pin_map_address_vo[3] = {
	(unsigned char *)0x24,	// DDRB
	(unsigned char *)0x27,	// DDRC
	(unsigned char *)0x2a	// DDRD
};

static unsigned char *pin_map_port_vo[3] = {
	(unsigned char *)0x25, // PORTB
	(unsigned char *)0x28, // PORTC
	(unsigned char *)0x2b  // PORTD	 
};

static unsigned char *pwm_map_address_vo[3] = {
	(unsigned char *)0x40,	//	Timer/Counter 0
	(unsigned char *)0x80,	//	Timer/Counter 1
	(unsigned char *)0xb0,	//	Timer/Counter 2

};

#endif