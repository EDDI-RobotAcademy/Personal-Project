#ifndef __PWM_REQUEST_H__
#define __PWM_REQUEST_H__

#include "stdint.h"

struct _pwm_request
{
    volatile unsigned char *hw_pwm_address;
    uint8_t timer_counter_channel;
    uint8_t output_compare_pin;
    uint8_t compare_output_value;
    uint8_t wave_generation_value;
    uint8_t pwm_prescale_value;
};

struct _pwm_request pwm_request;

#endif