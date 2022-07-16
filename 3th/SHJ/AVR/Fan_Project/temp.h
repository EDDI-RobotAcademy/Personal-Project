#ifndef __TEMP_H__
#define __TEMP_H__


#include <avr/io.h>
#include <util/delay.h>

void temp_init (void);
int read_temp (void);
void temp_tring (int n, char *buf);
void temperature_sensor (void);

#endif

