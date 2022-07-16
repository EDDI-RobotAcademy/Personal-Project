#ifndef __SWITCH_H__
#define __SWITCH_H__

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>

void sw_init (void);
void switch_mode (void);
void reset_mode (void);

#endif
