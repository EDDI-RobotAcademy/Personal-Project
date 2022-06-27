#define F_CPU       16000000UL


#include "wifi.h"
#include "uart.h"
#include "bluetooht.h"
#include "bldc.h"
#include "servo.h"


#define w_manual_mode         '1'
#define w_auto_mode           '2'
#define w_servo_start         '3'
#define w_servo_stop          '4'
#define w_low                 '5'
#define w_middle              '6'
#define w_high                '7'
#define w_stop                '8'
#define w_reset               '9'


volatile char wifi_data;
int w_manual_mode_select=0;
int w_auto_mode_select=0;
float w_duty = 5.0;

/*ISR(USART3_RX_vect)
{
    wifi_data = UDR3;
}*/

void wifi_mode(void)
{
  wifi_data = uart_recv();
  if(wifi_data == w_manual_mode)
    {
     w_manual_mode_select =1;
     w_auto_mode_select =0;
     uart_string_trans("Manual Mode\n");
     lcd_write_string("Manual Mode\n");
    }
       if(wifi_data == w_low)
        {
           bldc_low();
        }

        if(wifi_data == w_middle)
        {
           bldc_middle();
        }

        if(wifi_data==w_high)
        {
            bldc_high();
        }

        if(wifi_data==w_stop)
        {
           bldc_stop();
        }

    if (wifi_data == w_auto_mode)
    {
        w_auto_mode_select =1;
        w_manual_mode_select =0;
        uart_string_trans("Auto Mode\n");
        lcd_write_string("Auto Mode\n");
        //temperature_sensor();
        //photocell_mode();
    }

       if(wifi_data==w_servo_start)
         {
            w_duty +=0.1;
            servo_counter_clockwise(w_duty);

            if(w_duty>25.0)
            {
             for(w_duty=25.0; w_duty>5.0; w_duty-=0.1)
             {
                servo_clockwise(w_duty);
             }

            }
         }

         if(wifi_data==w_servo_stop)
         {
          servo_stop();
         }


      if(wifi_data==w_reset && (w_manual_mode_select==1 || w_auto_mode_select==1))
        {
            w_auto_mode_select=0;
            w_manual_mode_select=0;
            uart_string_trans("Select Mode\n");
            lcd_write_string("Select Mode\n");
        }

}
