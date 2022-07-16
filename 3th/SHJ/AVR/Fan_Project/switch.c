#define F_CPU       16000000UL

//intensity_sw
#define     CURRENT_MODE_DECISION_FACTOR    2
#define      MANUAL           1
#define      AUTO             2
#define      LOW_SPEED        1
#define      MIDDLE_SPEED     2
#define      HIGH_SPEED       3
#define      STOP             4

//action_sw
#define     CURRENT_MODE_RUN    1
#define     TURN_START     2
#define     TURN_STOP      3
#define     RESET_MODE     4
#define     RESET          0



#define     MANUAL_MODE     1
#define     AUTO_MODE       1

#define     COUNTERCLOCKWISE    5
#define     CLOCKWISE           25



#define     ANGULAR_SPEED_DUTY 0.1


#include "uart.h"
#include "lcd.h"
#include "switch.h"
#include "bldc.h"
#include "servo.h"
#include "temp.h"
#include "phtocell.h"
#include "bluetooht.h"
#include "wifi.h"


volatile int auto_manual_alter_intensity_sw=0;
volatile int mode_run_turn_sw=0;
float duty = 5.0;
int current_mode =0;

void sw_init (void)
{

    EICRA |= (1 << ISC21);
    //EICRA |= (1 << ISC20);
    EICRA |= (1 << ISC31);
    //EICRA |= (1 << ISC30);

    EIMSK |= (1 << INT2);
    EIMSK |= (1 << INT3);

    sei();
}

void switch_mode (void)
{
    if(auto_manual_alter_intensity_sw%CURRENT_MODE_DECISION_FACTOR==MANUAL && mode_run_turn_sw==RESET)
    {
     current_mode = MANUAL;
     uart_string_trans("Manual Mode\n");
     lcd_write_string("Manual Mode\n");
    }

    else if (auto_manual_alter_intensity_sw%CURRENT_MODE_DECISION_FACTOR==AUTO && mode_run_turn_sw==RESET)
    {
        current_mode = AUTO;
        uart_string_trans("Auto Mode\n");
        lcd_write_string("Auto Mode\n");
    }

       if(mode_run_turn_sw==TURN_START)
         {
            duty +=ANGULAR_SPEED_DUTY;
            servo_counter_clockwise(duty);

            if(duty>CLOCKWISE)
            {
             for(duty=CLOCKWISE; duty>COUNTERCLOCKWISE; duty-=ANGULAR_SPEED_DUTY)
             {
                servo_clockwise(duty);
             }

            }
         }

         if(mode_run_turn_sw==TURN_STOP)
         {
          servo_stop();
         }



   if (current_mode==MANUAL && mode_run_turn_sw==CURRENT_MODE_RUN)
    {
        uart_string_trans("Manual Mode run\n");
        lcd_write_string("Manual Mode run\n");

       if(auto_manual_alter_intensity_sw==LOW_SPEED)
       {
           bldc_low();
       }

        if(auto_manual_alter_intensity_sw==MIDDLE_SPEED)
        {
           bldc_middle();
         }

          if(auto_manual_alter_intensity_sw==HIGH_SPEED)
          {
            bldc_high();
          }

         if(auto_manual_alter_intensity_sw==STOP)
         {
           bldc_stop();
         }

     }

    else if(current_mode==AUTO && mode_run_turn_sw==CURRENT_MODE_RUN)
    {
        uart_string_trans("Auto Mode run\n");
        lcd_write_string("Auto Mode run\n");
        temperature_sensor();
        photocell_mode();
    }


      if(mode_run_turn_sw==RESET_MODE)
        {
            reset_mode();

        }



}

void reset_mode (void)
{
    OCR1A = RESET;
    OCR3A = RESET;
    uart_string_trans("Select Mode\n");
    lcd_write_string("Select Mode\n");
    auto_manual_alter_intensity_sw=RESET;
    mode_run_turn_sw=RESET;
    current_mode=RESET;

}

ISR(INT2_vect)
{
    auto_manual_alter_intensity_sw ++;

 if(auto_manual_alter_intensity_sw >4)
  {
    auto_manual_alter_intensity_sw=RESET;
  }
     _delay_ms(10);
     EIFR |= (1 << INTF2);

}

ISR(INT3_vect)
{
    mode_run_turn_sw ++;

  if(mode_run_turn_sw>4)
   {
    mode_run_turn_sw=RESET;
   }

      _delay_ms(10);
     EIFR |= (1 << INTF3);
}
