#define F_CPU          16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "uart.h"

void photocell_init (void)
{

    ADMUX |= (1 << REFS0);
    ADMUX |= (1 << MUX0);
    ADCSRA |= (1 << ADEN);
    ADCSRA |= (1 << ADPS2);
    ADCSRA |= (1 << ADPS0);
    ADCSRA |= (1 << ADIF);
    ADCSRA |= (1 << ADSC);

    DDRF |= (1 << PORT1);
    DDRE |= (1 << PORT0);
}

int read_photocell (void)
{
    while (!(ADCSRA & 0x10))
    {
        ;
    }

    return ADC;
}

void photocell_string (int n, char *buf)
{
    sprintf(buf, "%04d", n);
    buf[4] = '\0';
}

int photocell_mode (void)
{
    int read;
    char buf[5];

   // uart_init();
    photocell_init();


    while(1)
    {
        read = read_photocell();
        photocell_string(read, buf);
        //uart_string_trans(buf);
        //uart_string_trans("\n");

        if (read > 600)
        {
            PORTE |= (1 << PORT0);
        }
        else
        {
            PORTE &= ~(1 << PORT0);
        }

        _delay_ms(500);
    }
}




