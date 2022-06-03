#include <avr/io.h>
#include <avr/interrupt.h>


volatile int sw1;
volatile int sw2;
volatile int manual_flag;
volatile int auto_flag;

int sw_init (void)
{

    DDRD = (1 << PORT0);
    DDRD = (1 << PORT1);

    PCICR |= (1 << PCIE0);

    PCMSK0 |= (1 << PCINT0);

    PCICR |= (1 << PCIE1);

    PCMSK0 |= (1 << PCINT4);

    sei();
}

int manual_mode (void)
{
  manual_BLDC(sw1, manual_flag);
  manual_servo(sw2, manual_flag);
}

void auto_mode (void)
{
    temp_mode(auto_flag);
    photocell_mode(auto_flag);
}

void switch_mode (void)
{
   if (sw1 == 1 && sw2 == 1)
    {
        sw1 = 0;
        sw2 = 0;
        manual_flag = 1;
        auto_flag = 0;
        manual_mode();
    }
    else if(sw1 ==2 && sw2 ==1)
    {
        sw1 = 0;
        sw2 = 0;
        auto_flag = 1;
        manual_flag = 0;
        auto_mode();
    }

}

ISR (INT0_vect)
{
    sw1++;

}

ISR (INT1_vect)
{
    sw2++;

}

