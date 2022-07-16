#ifndef __LCD_H__
#define __LCD_H__

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void lcd_pulse_enable (void);
void lcd_write_data (uint8_t lcd_data);
void lcd_write_command (uint8_t command);
void lcd_clear (void);
void lcd_init (void);
void lcd_write_string (char *lcd_string);
void lcd_goto_xy (uint8_t row, uint8_t col);


#endif

