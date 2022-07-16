#ifndef __BLUETOOTH_UART_H__
#define __BLUETOOTH_UART_H__

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void b_uart_init (void);
unsigned char b_uart_recv (void);
void b_uart_trans (char b_uart_data);
void b_uart_string_trans (char *b_uart_str);
void b_uart_print (char *b_name, long b_val);
int b_usart_tx_char (char b_ch, FILE *b_fp);
void b_uart_print_8bit_num (uint8_t);

#endif


