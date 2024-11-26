#include "pwm_repository.h"
#include "../form/pwm_control_form.h"
#include <stdio.h>
#include <avr/io.h>


void set_compare_output_mode(struct _pwm_request pwm_request){
    compare_output_mode_table[pwm_request.compare_output_value](pwm_request);
}

void set_wave_generation_mode(struct _pwm_request pwm_request){

    // wave_generation_mode_table[pwm_request.wave_generation_value](pwm_request);

    printf("\n[PWM REPOSITORY] Wave Generation Mode : settings...\n");
    if(pwm_request.timer_counter_channel == 1) {
        *(volatile unsigned char*)(pwm_request.hw_pwm_address+TIMER_COUNTER_CONTROL_REGISTER_A) |= \
                                                        (pwm_request.wave_generation_value & 0x3);
        *(volatile unsigned char*)(pwm_request.hw_pwm_address+TIMER_COUNTER_CONTROL_REGISTER_B) |= \
                                                        (((pwm_request.wave_generation_value>>2) & 0x3)<<3);

    }
    else if(pwm_request.timer_counter_channel == 2){
        *(volatile unsigned char*)(pwm_request.hw_pwm_address+TIMER_COUNTER_CONTROL_REGISTER_A) |= \
                                                        (pwm_request.wave_generation_value & 0x3);
        *(volatile unsigned char*)(pwm_request.hw_pwm_address+TIMER_COUNTER_CONTROL_REGISTER_B) |= \
                                                        (((pwm_request.wave_generation_value>>2) & 0x1)<<3);

    }
    else {

    }

    printf("[PWM REPOSITORY] TCCR%dA = 0x%x\n",pwm_request.timer_counter_channel,*(volatile unsigned char*)(pwm_request.hw_pwm_address+TIMER_COUNTER_CONTROL_REGISTER_A));
    printf("[PWM REPOSITORY] TCCR%dB = 0x%x\n",pwm_request.timer_counter_channel,*(volatile unsigned char*)(pwm_request.hw_pwm_address+TIMER_COUNTER_CONTROL_REGISTER_B));
    printf("[PWM REPOSITORY] Wave Generation Mode : Settings is done!\n");

}

void set_prescale(struct _pwm_request pwm_request){
    // prescale_mode_table[pwm_request.pwm_prescale_value](pwm_request);
    printf("\n[PWM REPOSITORY] Presale Mode settings...\n");

    if(pwm_request.timer_counter_channel == 1){
        *(volatile unsigned char*)(pwm_request.hw_pwm_address + TIMER_COUNTER_CONTROL_REGISTER_B) |= \
                                                        pwm_request.pwm_prescale_value;

    }
    else if(pwm_request.timer_counter_channel == 2){
        *(volatile unsigned char*)(pwm_request.hw_pwm_address + TIMER_COUNTER_CONTROL_REGISTER_B) |= \
                                                        pwm_request.pwm_prescale_value;
    }
    else{

    }

    printf("[PWM REPOSITORY] TCCR%dB = 0x%x\n", pwm_request.timer_counter_channel,*(volatile unsigned char*)(pwm_request.hw_pwm_address + TIMER_COUNTER_CONTROL_REGISTER_B));
    printf("[PWM REPOSITORY] Presale Mode settings is done!\n");
}

void set_pwm_spec_for_sg90_servo_motor(struct _pwm_request pwm_request){

    set_compare_output_mode(pwm_request);
    set_wave_generation_mode(pwm_request);
    set_prescale(pwm_request);

    ICR1 = SG90_PWM_PERIOD_TIME_20MS; // 20ms period
}

void set_pwm_spec_for_rotate_sg90_90_degree_cw(struct _pwm_request pwm_request){
    printf("[PWM REPOSITORY] ROTATE SG90 MOTOR 90 DEGREE CW\n");
    OCR1A = 1000;
}

void set_pwm_spec_for_rotate_sg90_90_degree_ccw(struct _pwm_request pwm_request){
    printf("[PWM REPOSITORY] ROTATE SG90 MOTOR 90 DEGREE CCW\n");
    OCR1A = 3000;
}

void set_pwm_spec_for_dc_motor(struct _pwm_request pwm_request){

    set_compare_output_mode(pwm_request);
    set_wave_generation_mode(pwm_request);
    set_prescale(pwm_request);

}

void set_pwm_spec_for_stop_rotating_dc_motor (struct _pwm_request pwm_request){
    OCR2B = 0;              // 모터정지
    PORTD |= 0b00110000;    // PD4:1 PD5:1  모터 정지
}

void set_pwm_spec_for_rotate_dc_motor_cw (struct _pwm_request pwm_request){
    PORTD &= 0b11011111;       // PD5 : 0
	PORTD |= 0b00010000;       // 정방향 회전 PD4:1  PD5: 0
	OCR2B = 127;               // 0.5ms 되면 비교 일치 발생 될 수 있도록 한다.
}

void set_pwm_spec_for_rotate_dc_motor_ccw (struct _pwm_request pwm_request){
    PORTD &= 0b11101111;
	PORTD |= 0b00100000;       // 역회전 PD4: 0 PD5: 1
	OCR2B = 127;               // 0.5ms 되면 비교 일치 발생 될 수 있도록 한다.
}

const compare_output_mode_handler compare_output_mode_table[] = {
    compare_output_mode_value_0,
    compare_output_mode_value_1,
    compare_output_mode_value_2,
    compare_output_mode_value_3
};

const wave_generation_mode_handler wave_generation_mode_table[] = {
    wave_generation_mode_value_0,
    wave_generation_mode_value_1,
    wave_generation_mode_value_2,
    wave_generation_mode_value_3,
    wave_generation_mode_value_4,
    wave_generation_mode_value_5,
    wave_generation_mode_value_6,
    wave_generation_mode_value_7,
    wave_generation_mode_value_8,
    wave_generation_mode_value_9,
    wave_generation_mode_value_10,
    wave_generation_mode_value_11,
    wave_generation_mode_value_12,
    wave_generation_mode_value_13,
    wave_generation_mode_value_14,
    wave_generation_mode_value_15

};

const prescale_handler tc16_prescale_mode_table[] = {
    prescale_mode_value_0,
    prescale_mode_value_1,
    prescale_mode_value_2,
    prescale_mode_value_3,
    prescale_mode_value_4,
    prescale_mode_value_5,
    prescale_mode_value_6,
    prescale_mode_value_7

};

/* *****************************************************
    ATmega328p Timer/Counter 1 - Compare Output Mode
***************************************************** */

void compare_output_mode_value_0(struct _pwm_request pwm_request){

}
void compare_output_mode_value_1(struct _pwm_request pwm_request){

}
void compare_output_mode_value_2(struct _pwm_request pwm_request){
    printf("[PWM REPOSITORY] Compare Output Mode settings..\n");
    *(volatile unsigned char*)pwm_request.hw_pwm_address |= (pwm_request.compare_output_value<<pwm_request.output_compare_pin);

    printf("[PWM REPOSITORY] TCCR%dA = 0x%x\n", pwm_request.timer_counter_channel,*(volatile unsigned char*)pwm_request.hw_pwm_address);
    printf("[PWM REPOSITORY] Compare Output Mode settings Done!\n");

}
void compare_output_mode_value_3(struct _pwm_request pwm_request){

}

/* *****************************************************
    ATmega328p Timer/Counter 1 - Wave Generation Mode
***************************************************** */

void wave_generation_mode_value_0(struct _pwm_request pwm_request){

}
void wave_generation_mode_value_1(struct _pwm_request pwm_request){

}
void wave_generation_mode_value_2(struct _pwm_request pwm_request){

}
void wave_generation_mode_value_3(struct _pwm_request pwm_request){

}
void wave_generation_mode_value_4(struct _pwm_request pwm_request){

}
void wave_generation_mode_value_5(struct _pwm_request pwm_request){

}
void wave_generation_mode_value_6(struct _pwm_request pwm_request){

}
void wave_generation_mode_value_7(struct _pwm_request pwm_request){

}
void wave_generation_mode_value_8(struct _pwm_request pwm_request){

}
void wave_generation_mode_value_9(struct _pwm_request pwm_request){

}
void wave_generation_mode_value_10(struct _pwm_request pwm_request){

}
void wave_generation_mode_value_11(struct _pwm_request pwm_request){

}
void wave_generation_mode_value_12(struct _pwm_request pwm_request){

}
void wave_generation_mode_value_13(struct _pwm_request pwm_request){

}
void wave_generation_mode_value_14(struct _pwm_request pwm_request){
    printf("[PWM REPOSITORY] Wave Generation Mode : settings...\n");
    if(pwm_request.timer_counter_channel == 1) {
        *(volatile unsigned char*)(pwm_request.hw_pwm_address+TIMER_COUNTER_CONTROL_REGISTER_A) |= \
                                                        (pwm_request.wave_generation_value & 0x3);
        *(volatile unsigned char*)(pwm_request.hw_pwm_address+TIMER_COUNTER_CONTROL_REGISTER_B) |= \
                                                        (((pwm_request.wave_generation_value>>2) & 0x3)<<3);

    }
    else if(pwm_request.timer_counter_channel == 2){
        *(volatile unsigned char*)(pwm_request.hw_pwm_address+TIMER_COUNTER_CONTROL_REGISTER_A) |= \
                                                        (pwm_request.wave_generation_value & 0x3);
        *(volatile unsigned char*)(pwm_request.hw_pwm_address+TIMER_COUNTER_CONTROL_REGISTER_B) |= \
                                                        (((pwm_request.wave_generation_value>>2) & 0x1)<<3);

    }
    else {

    }

    printf(" Done!\n");
    printf("[PWM REPOSITORY] TCCR%dA = 0x%x\n",pwm_request.timer_counter_channel,*(volatile unsigned char*)(pwm_request.hw_pwm_address+TIMER_COUNTER_CONTROL_REGISTER_A));
    printf("[PWM REPOSITORY] TCCR%dB = 0x%x\n",pwm_request.timer_counter_channel,*(volatile unsigned char*)(pwm_request.hw_pwm_address+TIMER_COUNTER_CONTROL_REGISTER_B));
}
void wave_generation_mode_value_15(struct _pwm_request pwm_request){

}

/* ***********************************************
    ATmega328p Timer/Counter 1 - Prescale Mode
*********************************************** */

void prescale_mode_value_0(struct _pwm_request pwm_request){

}
void prescale_mode_value_1(struct _pwm_request pwm_request){

}
void prescale_mode_value_2(struct _pwm_request pwm_request){

    if(pwm_request.timer_counter_channel == 1){
        printf("[PWM REPOSITORY] Presale value : 8 (2MHz) settings...");
        *(volatile unsigned char*)(pwm_request.hw_pwm_address + TIMER_COUNTER_CONTROL_REGISTER_B) |= \
                                                        pwm_request.pwm_prescale_value;

        printf(" Done!\n");
        printf("[PWM REPOSITORY] TCCR1B = 0x%x\n", TCCR1B);
    }
    else if(pwm_request.timer_counter_channel == 2){

    }
    else{

    }
}
void prescale_mode_value_3(struct _pwm_request pwm_request){

}
void prescale_mode_value_4(struct _pwm_request pwm_request){

}
void prescale_mode_value_5(struct _pwm_request pwm_request){

}
void prescale_mode_value_6(struct _pwm_request pwm_request){

}
void prescale_mode_value_7(struct _pwm_request pwm_request){

}
