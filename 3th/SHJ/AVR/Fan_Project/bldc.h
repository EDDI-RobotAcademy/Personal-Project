#ifndef __BLDC_H__
#define __BLDC_H__

#include <avr/io.h>



void BLDC_init(void);
void bldc_low (void);
void bldc_middle (void);
void bldc_high (void);
void bldc_stop (void);

#endif
