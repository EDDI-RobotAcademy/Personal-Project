#define F_CPU       16000000UL

#include "bluetooth_uart.h"


#define UART_BUF                (10)


void b_uart_init (void)
{

    UCSR3A |= (1 << U2X3);


    UBRR3H = 0x00;
    UBRR3L = 207;


    UCSR3C |= (1 << UCSZ30);
    UCSR3C |= (1 << UCSZ31);


    UCSR3B |= (1 << RXEN3);
    UCSR3B |= (1 << TXEN3);

}

unsigned char b_uart_recv (void)
{
    while (!(UCSR3A & (1 << RXC3)))
    {
        ;
    }

    return UDR3;
}

void b_uart_trans (char b_uart_data)
{

    while (!(UCSR3A & (1 << UDRE3)))
    {
        ;
    }


    UDR3 = b_uart_data;
}

void b_uart_string_trans (char *b_uart_str)
{
    while (*b_uart_str != '\0')
    {
        b_uart_trans(*b_uart_str);
        b_uart_str++;
    }
}

void b_uart_print (char *b_name, long b_val)
{
    char b_debug_buf[UART_BUF] = { '\0' };

    b_uart_string_trans(b_name);
    b_uart_string_trans(" = ");

    itoa((b_val), b_debug_buf, UART_BUF);
    b_uart_string_trans(b_debug_buf);
    b_uart_string_trans("\n");
}

int b_usart_tx_char (char b_ch, FILE *b_fp)
{
    return 0;
}

void b_uart_print_8bit_num (uint8_t b_no)
{
    char b_num_string[4] = "0";
    int i, b_index = 0;

    if (b_no > 0)
    {
        for (i = 0; b_no != 0; i++)
        {
            b_num_string[i] = b_no % 10 + '0';
            b_no = b_no / 10;
        }

        b_num_string[i] = '\0';
        b_index = i - 1;
    }

    for (i = b_index; i >= 0; i--)
    {
        b_uart_trans(b_num_string[i]);
    }
}


