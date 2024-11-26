#ifndef __PWM_SERVICE_TABLE_H__
#define __PWM_SERVICE_TABLE_H__

#include "pwm_service.h"

typedef void (* pwm_service_call_ptr_t) (struct _pwm_request);

const pwm_service_call_ptr_t pwm_service_call_table[] = {
    pwm_setting_sg90_servo_motor,
    rotate_sg90_motor_90_degree_cw,
    rotate_sg90_motor_90_degree_ccw,
    pwm_setting_dc_motor,
    stop_rotating_dc_motor,
    rotate_dc_motor_cw,
    rotate_dc_motor_ccw
};

#endif
