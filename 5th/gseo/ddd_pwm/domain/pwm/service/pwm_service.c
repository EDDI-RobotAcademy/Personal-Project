#include <stdio.h>

#include "pwm_service.h"
#include "../repository/pwm_repository_table.h"


void pwm_setting_sg90_servo_motor (struct _pwm_request pwm_request)
{
    printf("\n[PWM SERVICE] PWM SETTING FOR SG90 SERVO MOTOR\n");
    pwm_repository_call_table[SET_PWM_SPEC_FOR_SG90_SERVO_MOTOR](pwm_request);
}

void rotate_sg90_motor_90_degree_cw (struct _pwm_request pwm_request)
{
    printf("\n[PWM SERVICE] ROTATE SG90 MOTOR 90 DEGREE CW\n");
    pwm_repository_call_table[SET_PWM_SPEC_FOR_ROTATE_SG90_90_DEGREE_CW](pwm_request);
}

void rotate_sg90_motor_90_degree_ccw (struct _pwm_request pwm_request)
{
    printf("\n[PWM SERVICE] ROTATE SG90 MOTOR 90 DEGREE CCW\n");
    pwm_repository_call_table[SET_PWM_SPEC_FOR_ROTATE_SG90_90_DEGREE_CCW](pwm_request);
}

void pwm_setting_dc_motor (struct _pwm_request pwm_request)
{
    printf("\n[PWM SERVICE] PWM SETTING FOR DC MOTOR\n");
    pwm_repository_call_table[SET_PWM_SPEC_FOR_DC_MOTOR](pwm_request);
}

void stop_rotating_dc_motor (struct _pwm_request pwm_request)
{
    printf("\n[PWM SERVICE] STOP ROTATING DC MOTOR\n");
    pwm_repository_call_table[SET_PWM_SPEC_FOR_STOP_ROTATING_DC_MOTOR](pwm_request);
}

void rotate_dc_motor_cw (struct _pwm_request pwm_request)
{
    printf("\n[PWM SERVICE] ROTATE DC MOTOR CW\n");
    pwm_repository_call_table[SET_PWM_SPEC_FOR_ROTATE_DC_MOTOR_CW](pwm_request);
}

void rotate_dc_motor_ccw (struct _pwm_request pwm_request)
{
    printf("\n[PWM SERVICE] ROTATE DC MOTOR CCW\n");
    pwm_repository_call_table[SET_PWM_SPEC_FOR_ROTATE_DC_MOTOR_CCW](pwm_request);
}
