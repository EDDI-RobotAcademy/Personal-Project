#ifndef __PHTOCELL_H__
#define __PHTOCELL_H__

#include <avr/io.h>
#include <util/delay.h>


void photocell_init (void);
int read_photocell (void);
void photocell_string (int n, char *buf);
int photocell_mode ();

#endif
