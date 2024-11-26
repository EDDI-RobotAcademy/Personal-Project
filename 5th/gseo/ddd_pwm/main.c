/*
 */
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>

#include <util/delay.h>
#include <stdio.h>

#include "domain/console/usart_printf.h"

#include "domain/led/entity/led.h"
#include "domain/led/service/led_service_table.h"

#include "domain/led/form/led_control_form.h"

#include "domain/pin/pin_map.h"

#include "domain/pin/form/pin_control_form.h"
#include "domain/pin/service/pin_service_table.h"

#include "domain/pwm/form/pwm_control_form.h"
#include "domain/pwm/service/pwm_service_table.h"

#define F_CPU       16000000L

#define USE_SG90_SERVO_MOTOR    0
#define USE_DC_MOTOR            1


#define DELAY					2000

int main(void)
{
    //  [DDD-PWM-6]
    //  TODO : Add USART0 Initialization for Putty Debug Message.
    usart_initialize();
    stdout = &uart_output;
	_delay_ms(10);

    printf("\n Eddi Robot Academy's Embedded Master LV.1\n1. Project Name    : DDD-PWM\r\n");
    printf("2. Chipset         : ATmega328p\r\n");
    printf("3. Peripheral      : PWM\r\n");
    printf("4. Software Design : Domain-Driven Design.\r\n\n");

/* 240724 SG90 SERVO MOTOR */
#if USE_SG90_SERVO_MOTOR
    // [DDD-PWM-9]
    // TODO : control form에 50Hz PWM 파형을 생성하기 위한
    //        compare output mode, wave generation mode, precale 정보를 전달한다.
    set_pwm_control_form(PWM_TIMER_COUNTER_1, NON_INVERTING_MODE, FAST_PWM_TOP_ICR1, TC1_PRESCALE_8);

    // [DDD-PWM-8]
    // TODO : 개발자는 SG90 서보모터를 동작시키기 위해
    //        PWM를 설정해야 하는데, 이 때 PWM Setting을 Service에 요청하는 코드를 작성한다.
    pwm_service_call_table[PWM_SETTING_SG90_SERVO_MOTOR](
        convert_pwm_control_data(pwm_control_form)
    );

    set_pin_control_form(PIN_PB1, PIN_OUTPUT_MODE);
    pin_service_call_table[PIN_DIRECTION] (
        convert_pin_control_data(pin_control_form)
    );
#endif

/* 240724 DC MOTOR */
#if USE_DC_MOTOR
//  [DDD-PWM-9]
//  TODO : control form에 250KHz PWM 파형을 생성하기 위한
//         compare output mode, wave generation mode, precale 정보를 전달한다.
    set_pwm_control_form(PWM_TIMER_COUNTER_2, OCxB ,NON_INVERTING_MODE, TC2_FAST_PWM_TOP_0xFF, TC2_PRESCALE_64);

// [DDD-PWM-9]
// TODO : 개발자는 DC모터를 동작시키기 위해
//        PWM를 설정해야 하는데, 이 때 PWM Setting 정보들을 Service에 요청하는 코드를 작성한다.
    pwm_service_call_table[PWM_SETTING_DC_MOTOR](
        convert_pwm_control_data(pwm_control_form)
    );

    set_pin_control_form(PIN_PD3, PIN_OUTPUT_MODE);
    pin_service_call_table[PIN_DIRECTION] (
        convert_pin_control_data(pin_control_form)
    );

    set_pin_control_form(PIN_PD4, PIN_OUTPUT_MODE);
    pin_service_call_table[PIN_DIRECTION] (
        convert_pin_control_data(pin_control_form)
    );

    set_pin_control_form(PIN_PD5, PIN_OUTPUT_MODE);
    pin_service_call_table[PIN_DIRECTION] (
        convert_pin_control_data(pin_control_form)
    );
#endif

#if USE_SG90_SERVO_MOTOR
    for(;;)
    {
        if(USE_SG90_SERVO_MOTOR==1){
            pwm_service_call_table[ROTATE_SG90_MOTOR_90_DEGREE_CW](
                convert_pwm_control_data(pwm_control_form)
            );
            _delay_ms(1000);

            pwm_service_call_table[ROTATE_SG90_MOTOR_90_DEGREE_CCW](
                convert_pwm_control_data(pwm_control_form)
            );
            _delay_ms(1000);
        }

        if(USE_DC_MOTOR==1){
            OCR1A = 400;
            _delay_ms(1000);
        }
	}
#endif
// ********************************************************************

#if USE_DC_MOTOR
    while(1)
	{
        pwm_service_call_table[STOP_ROTATING_DC_MOTOR](
            convert_pwm_control_data(pwm_control_form)
        );
        _delay_ms(DELAY);

        pwm_service_call_table[ROTATE_DC_MOTOR_CW](
            convert_pwm_control_data(pwm_control_form)
        );
        _delay_ms(DELAY);

		pwm_service_call_table[STOP_ROTATING_DC_MOTOR](
            convert_pwm_control_data(pwm_control_form)
        );
        _delay_ms(DELAY);

        pwm_service_call_table[ROTATE_DC_MOTOR_CCW](
            convert_pwm_control_data(pwm_control_form)
        );
		_delay_ms(DELAY);

	}
#endif
	return 0;


}
