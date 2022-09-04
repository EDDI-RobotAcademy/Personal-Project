//sw1 = PD2
//sw2 = PD3
//bldc = PB5
//servo = PE3
//temp = PF0
//photocell = PF1
//led = PE0
//lcd = PA0~1, PC0~7


#define F_CPU                           16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "bluetooth_uart.h"
#include "lcd.h"
#include "switch.h"
#include "bldc.h"
#include "servo.h"
#include "temp.h"
#include "phtocell.h"
#include "bluetooht.h"
#include "wifi.h"



int main(void)
{
    uart_init();
    lcd_init();
    sw_init();
    BLDC_init();
    servo_init();
    temp_init();
    photocell_init();


    uart_string_trans("Select Mode\n");
    lcd_write_string("Select Mode\n");

    while(1)
    {
      //switch_mode();
      wifi_mode();
     //bluetooth_mode();
     _delay_ms(70);
    }



}



