#ifndef __PWM_MODE_H__
#define __PWM_MODE_H__

    // [DDD-PWM-1]
    // TODO : Developer can setup the PWM mode.

#define DEBUG_MESSAGE   1

typedef enum _PWM_TIMER_COUNTER_NUMBER PWM_TIMER_COUNTER_NUMBER;
enum _PWM_TIMER_COUNTER_NUMBER
{
    PWM_TIMER_COUNTER_0       =   0,
    PWM_TIMER_COUNTER_1       =   1,
    PWM_TIMER_COUNTER_2       =   2,

    PWM_CHANNEL_END
};

typedef enum _OUTPUT_COMPARE_PIN OUTPUT_COMPARE_PIN;
enum _OUTPUT_COMPARE_PIN
{
    OCxA    =   6,
    OCxB    =   4
};

typedef enum _COMPARE_OUTPUT_MODE COMPARE_OUTPUT_MODE;
enum _COMPARE_OUTPUT_MODE
{
    NORMAL_PORT_OPERATION          =   0,
    TOGGLE_ON_MATCH_NORMAL         =   1,
    NON_INVERTING_MODE             =   2,
    INVERTING_MODE                 =   3,
    
    COMPARE_OUTPUT_MODE_END
};

typedef enum _TC1_WAVE_GENERATION_MODE TC1_WAVE_GENERATION_MODE;
enum TC1_WAVE_GENERATION_MODE
{
    TC1_NORMAL_TOP_0xFFFF                   =   0,
    TC1_PHASE_CORRECT_8BIT_TOP_0x00FF       =   1,
    TC1_PHASE_CORRECT_9BIT_TOP_0x01FF       =   2,
    TC1_PHASE_CORRECT_10BIT_TOP_0x01FF      =   3,
    TC1_CTC_TOP_OCR1A                       =   4,
    TC1_FAST_PWM_8BIT_TOP_0x00FF            =   5,
    TC1_FAST_PWM_9BIT_TOP_0x01FF            =   6,
    TC1_FAST_PWM_10BIT_TOP_0x03FF           =   7,
    TC1_PHASE_AND_FREQ_CORRECT_TOP_ICR1     =   8,
    TC1_PHASE_AND_FREQ_CORRECT_TOP_OCR1A    =   9,
    TC1_PHASE_CORRECT_TOP_ICR1              =   10,
    TC1_PHASE_CORRECT_TOP_OCR1A             =   11,
    TC1_CTC_TOP_ICR1                        =   12,
    TC1_RESERVED                            =   13,
    TC1_FAST_PWM_TOP_ICR1                   =   14,
    TC1_FAST_PWM_TOP_OCR1A                  =   15,   

    TC1_WAVE_GENERATION_MODE_END
};

typedef enum _TC2_WAVE_GENERATION_MODE TC2_WAVE_GENERATION_MODE;
enum TC2_WAVE_GENERATION_MODE
{
    TC2_NORMAL_TOP_0xFF                   =   0,
    TC2_PHASE_CORRECT_TOP_0xFF            =   1,
    TC2_CTC_TOP_OCRA                      =   2,
    TC2_FAST_PWM_TOP_0xFF                 =   3,
    TC2_RESERVED_0                        =   4,
    TC2_PHASE_CORRECT_TOP_OCRA            =   5,
    TC2_RESERVED_1                        =   6,
    TC2_FAST_PWM_TOP_OCR1A                =   7,   

    TC2_WAVE_GENERATION_MODE_END
};

typedef enum _TC1_SELECT_PRESCALE_VALUE TC1_SELECT_PRESCALE_VALUE;
enum TC1_SELECT_PRESCALE_VALUE
{                                               
    TC1_NO_CLOCK_SOURCE                     =   0,  
    TC1_PRESCALE_1                          =   1,  
    TC1_PRESCALE_8                          =   2,
    TC1_PRESCALE_64                         =   3,
    TC1_PRESCALE_256                        =   4,
    TC1_PRESCALE_1024                       =   5,
    TC1_EXTERNAL_CLOCK_SOURCE_T1_RISISNG    =   6,
    TC1_EXTERNAL_CLOCK_SOURCE_T1_FALLING    =   7,

    PRESCALE_SELECT_BIT_END
};

typedef enum _TC2_SELECT_PRESCALE_VALUE TC2_SELECT_PRESCALE_VALUE;
enum TC2_SELECT_PRESCALE_VALUE
{
    TC2_NO_CLOCK_SOURCE                     =   0,
    TC2_PRESCALE_1                          =   1,
    TC2_PRESCALE_8                          =   2,
    TC2_PRESCALE_32                         =   3,
    TC2_PRESCALE_64                         =   4,
    TC2_PRESCALE_128                        =   5,
    TC2_PRESCALE_256                        =   6,
    TC2_PRESCALE_1024                       =   7,

    TC2_PRESCALE_SELECT_BIT_END
};
#endif