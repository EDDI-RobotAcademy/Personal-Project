#ifndef __SERVO_H__
#define __SERVO_H__

#include <avr/io.h>


void servo_init (void);
void servo_counter_clockwise (float duty);
void servo_clockwise (float duty);
void servo_stop (void);

#endif
