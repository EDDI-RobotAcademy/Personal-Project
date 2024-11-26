#ifndef __PWM_REPOSITORY_TABLE_H__
#define __PWM_REPOSITORY_TABLE_H__

#include "pwm_repository.h"

typedef void (* pwm_repository_call_ptr_t) (struct _pwm_request);

const pwm_repository_call_ptr_t pwm_repository_call_table[] = {
    set_pwm_spec_for_sg90_servo_motor,
    set_pwm_spec_for_rotate_sg90_90_degree_cw,
    set_pwm_spec_for_rotate_sg90_90_degree_ccw,

    set_pwm_spec_for_dc_motor,
    set_pwm_spec_for_stop_rotating_dc_motor,
    set_pwm_spec_for_rotate_dc_motor_cw,
    set_pwm_spec_for_rotate_dc_motor_ccw
};

#endif