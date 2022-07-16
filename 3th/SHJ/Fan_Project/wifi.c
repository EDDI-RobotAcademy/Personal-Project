#define F_CPU       16000000UL


#include "wifi.h"
#include "uart.h"
#include "bluetooht.h"
#include "bldc.h"
#include "servo.h"


#define W_MANUAL_MODE         '1'
#define W_AUTO_MODE           '2'
#define W_SERVO_START         '3'
#define W_SERVO_STOP          '4'
#define W_LOW                 '5'
#define W_MIDDLE              '6'
#define W_HIGH                '7'
#define W_STOP                '8'
#define W_RESET               '9'

#define CLOCKWISE               25
#define COUNTERCLOCKWISE        5

#define MANUAL_MODE             1
#define AUTO_MODE               1


volatile char wifi_data;
int w_manual_mode_select=0;
int w_auto_mode_select=0;
float w_duty = 5.0;

ISR(USART2_RX_vect)
{
    wifi_data = UDR2;
}

void wifi_mode(void)
{

  //wifi_data = uart_recv();

  if(wifi_data == W_MANUAL_MODE)
    {
     w_manual_mode_select =1;
     w_auto_mode_select =0;
     uart_string_trans("Manual Mode\n");
     lcd_write_string("Manual Mode\n");
    }
       if(wifi_data == W_LOW)
        {
           bldc_low();
        }

        if(wifi_data == W_MIDDLE)
        {
           bldc_middle();
        }

        if(wifi_data==W_HIGH)
        {
            bldc_high();
        }

        if(wifi_data==W_STOP)
        {
           bldc_stop();
        }

    if (wifi_data == W_AUTO_MODE)
    {
        w_auto_mode_select =1;
        w_manual_mode_select =0;
        uart_string_trans("Auto Mode\n");
        lcd_write_string("Auto Mode\n");
        //temperature_sensor();
        //photocell_mode();
    }

       if(wifi_data==W_SERVO_START)
         {
            w_duty +=0.1;
            servo_counter_clockwise(w_duty);

            if(w_duty>CLOCKWISE)
            {
             for(w_duty=CLOCKWISE; w_duty>COUNTERCLOCKWISE; w_duty-=0.1)
             {
                servo_clockwise(w_duty);
             }

            }

         }

         if(wifi_data==W_SERVO_STOP)
         {
          servo_stop();
         }


      if(wifi_data==W_RESET && (w_manual_mode_select==MANUAL_MODE || w_auto_mode_select==AUTO_MODE))
        {
            w_auto_mode_select=0;
            w_manual_mode_select=0;
            uart_string_trans("Select Mode\n");
            lcd_write_string("Select Mode\n");
        }




}
