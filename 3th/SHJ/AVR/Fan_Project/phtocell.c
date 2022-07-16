#define F_CPU          16000000UL


#include "phtocell.h"
#include "lcd.h"
#include "uart.h"

#define LED_ON      600

void photocell_init (void)
{

    ADMUX |= (1 << REFS0);
    ADMUX |= (1 << MUX1);
    ADCSRA |= (1 << ADEN);
    ADCSRA |= (1 << ADPS2);
    ADCSRA |= (1 << ADPS0);
    ADCSRA |= (1 << ADIF);
    ADCSRA |= (1 << ADSC);

    DDRF |= (1 << PORT2);
    DDRH |= (1 << PORT5);
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


        read = read_photocell();
        photocell_string(read, buf);
        uart_string_trans(buf);
        uart_string_trans("\n");

        if (read > LED_ON)
        {
            uart_string_trans("led on\n");
            lcd_write_string("led on\n");
            PORTE |= (1 << PORT0);

        }
        else
        {
            uart_string_trans("led off\n");
            lcd_write_string("led off\n");
            PORTE &= ~(1 << PORT0);

        }

  }





