#define F_CPU       16000000UL


#include "bluetooth_uart.h"
#include "uart.h"
#include "bluetooht.h"
#include "bldc.h"
#include "servo.h"
#include "switch.h"


#define B_MANUAL_MODE         1
#define B_AUTO_MODE           2
#define B_SERVO_START         3
#define B_SERVO_STOP          4
#define B_LOW                 5
#define B_MIDDLE              6
#define B_HIGH                7
#define B_STOP                8
#define b_RESET               9
#define RESET                 0

#define CLOCKWISE               25
#define COUNTERCLOCKWISE        5

#define MANUAL_MODE             1
#define AUTO_MODE               1

#define ANGULAR_SPEED_DUTY      0.1


volatile int bluetooth_data;
float b_duty = 5.0;

ISR(USART3_RX_vect)
{
    bluetooth_data = UDR3;
}

void bluetooth_mode(void)
{
  if(bluetooth_data == B_MANUAL_MODE)
    {
     uart_string_trans("Manual Mode\n");
     lcd_write_string("Manual Mode\n");
    }

        if(bluetooth_data == B_LOW)
        {
           bldc_low();
        }

        if(bluetooth_data == B_MIDDLE)
        {
           bldc_middle();
        }

        if(bluetooth_data==B_HIGH)
        {
            bldc_high();
        }

        if(bluetooth_data==B_STOP)
        {
           bldc_stop();
        }


    if (bluetooth_data == B_AUTO_MODE)
    {
        uart_string_trans("Auto Mode\n");
        lcd_write_string("Auto Mode\n");
        //temperature_sensor();
        //photocell_mode();
    }

       if(bluetooth_data==B_SERVO_START)
         {
            b_duty +=ANGULAR_SPEED_DUTY;
            servo_counter_clockwise(b_duty);

            if(b_duty>CLOCKWISE)
            {
             for(b_duty=CLOCKWISE; b_duty>COUNTERCLOCKWISE; b_duty-=ANGULAR_SPEED_DUTY)
             {
                servo_clockwise(b_duty);
             }

            }
         }

         if(bluetooth_data==B_SERVO_STOP)
         {
          servo_stop();
         }


      if(bluetooth_data==b_RESET)
        {
            bluetooth_data=RESET;
            reset_mode();
        }

}
