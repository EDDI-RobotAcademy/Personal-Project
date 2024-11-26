#ifndef __PWM_SERVICE_H__
#define __PWM_SERVICE_H__

#include "request/pwm_request.h"

enum _pwm_domain_service{
    PWM_SETTING_SG90_SERVO_MOTOR,
    ROTATE_SG90_MOTOR_90_DEGREE_CW,
    ROTATE_SG90_MOTOR_90_DEGREE_CCW,
    PWM_SETTING_DC_MOTOR,
    STOP_ROTATING_DC_MOTOR,
    ROTATE_DC_MOTOR_CW,
    ROTATE_DC_MOTOR_CCW
};

void pwm_setting_sg90_servo_motor (struct _pwm_request);
void rotate_sg90_motor_90_degree_cw (struct _pwm_request);
void rotate_sg90_motor_90_degree_ccw (struct _pwm_request);

void pwm_setting_dc_motor (struct _pwm_request);
void stop_rotating_dc_motor (struct _pwm_request);
void rotate_dc_motor_cw (struct _pwm_request);
void rotate_dc_motor_ccw (struct _pwm_request);



#endif