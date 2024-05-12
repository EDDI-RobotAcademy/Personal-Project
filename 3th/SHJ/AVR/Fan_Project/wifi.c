#define F_CPU       16000000UL


#include "wifi.h"
#include "uart.h"
#include "bluetooht.h"
#include "bldc.h"
#include "servo.h"
#include "switch.h"
#include "lcd.h"

#define RESET                 '0'
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

#define ANGULAR_SPEED_DUTY      0.1

#define LOW     0
#define MIDDLE  1
#define HIGH    2
#define STOP    3


volatile char wifi_data;
int w_manual_mode_select=0;
int w_auto_mode_select=0;
float w_duty = 5.0;

/*ISR(USART_RX_vect)
{
    wifi_data = UDR0;
}*/



void wifi_mode(void)
{
  wifi_data = uart_recv();
  void (*Fan_Speed[4])(void) = {bldc_low, bldc_middle, bldc_high, bldc_stop};


  if(wifi_data == W_MANUAL_MODE)
    {
     uart_string_trans("Manual Mode\n");
     lcd_write_string("Manual Mode\n");
    }

       if(wifi_data == W_LOW)
        {
           Fan_Speed[LOW]();

        }

        if(wifi_data == W_MIDDLE)
        {
           Fan_Speed[MIDDLE]();

        }

        if(wifi_data==W_HIGH)
        {
            Fan_Speed[HIGH]();

        }

        if(wifi_data==W_STOP)
        {
           Fan_Speed[STOP]();

        }

    if (wifi_data == W_AUTO_MODE)
    {
        uart_string_trans("Auto Mode\n");
        lcd_write_string("Auto Mode\n");
        //temperature_sensor();
        //photocell_mode();
    }

       if(wifi_data==W_SERVO_START)
         {

            w_duty += ANGULAR_SPEED_DUTY;
            servo_counter_clockwise(w_duty);

            if(w_duty>CLOCKWISE)
            {
             for(w_duty=CLOCKWISE; w_duty>COUNTERCLOCKWISE; w_duty -= ANGULAR_SPEED_DUTY)
             {
                servo_clockwise(w_duty);
             }

            }
         }

         if(wifi_data==W_SERVO_STOP)
         {
          servo_stop();
         }


      if(wifi_data==W_RESET)
        {
            wifi_data = RESET;
            reset_mode();

        }


}
