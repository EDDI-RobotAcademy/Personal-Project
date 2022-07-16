#define F_CPU          16000000UL

#define LOW_MIN      32
#define LOW_MAX      34
#define MIDDLE_MIN   34
#define MIDDLE_MAX   36
#define HIGH_MIN     36
#define STOP_MIN     32
#define CELSIUS      0.488 //5*100/1024


#include "lcd.h"
#include "uart.h"
#include "temp.h"
#include "bldc.h"



void temp_init (void)
{
    /*ADMUX |= (1 << REFS0);
    ADCSRA |= (1 << ADEN);
    ADCSRA |= (1 << ADPS2);
    ADCSRA |= (1 << ADPS0);
    ADCSRA |= (1 << ADIF);
    ADCSRA |= (1 << ADSC);*/
    ADMUX |= (1 << REFS0);
    ADMUX |= (1 << MUX0);
    ADCSRA |= (1 << ADEN);
    ADCSRA |= (1 << ADPS2);
    ADCSRA |= (1 << ADPS0);
    ADCSRA |= (1 << ADIF);
    ADCSRA |= (1 << ADSC);

    DDRF = (1 << PORT0);
}

int read_temp (void)
{
    while (!(ADCSRA & 0x10))
    {
        ;
    }

    return ADC;
}

void temp_tring (int n, char *buf)
{
    sprintf(buf, "%04d", n);
    buf[4] = '\0';
}

void temperature_sensor (void)
{

    int read;
    char buf[5];


       read = read_temp() * CELSIUS;
        temp_tring(read, buf);
        uart_string_trans(buf);
        uart_string_trans("\n");

         if (read<STOP_MIN)
         {
           bldc_stop();
         }

         else if (read > LOW_MIN && read < LOW_MAX )
         {
            bldc_low();
         }
        else if (read > MIDDLE_MIN && read < MIDDLE_MAX)
         {
            bldc_middle();
         }
        else if (read > HIGH_MIN)
         {
            bldc_high();
         }

}








