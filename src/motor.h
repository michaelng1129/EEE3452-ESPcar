#include <Arduino.h>
#include "pin.h"
#include "driver/mcpwm.h"

void setupMCPWM()
{
    pinMode(MOTOR1_PIN1, OUTPUT);
    pinMode(MOTOR1_PIN2, OUTPUT);
    pinMode(MOTOR2_PIN1, OUTPUT);
    pinMode(MOTOR2_PIN2, OUTPUT);

    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, MOTOR1_PIN1);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0B, MOTOR1_PIN2);

    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM1A, MOTOR2_PIN1);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM1B, MOTOR2_PIN2);

    mcpwm_config_t pwm_config_motor;
    pwm_config_motor.frequency = 500;
    pwm_config_motor.cmpr_a = 0;
    pwm_config_motor.cmpr_b = 0;
    pwm_config_motor.counter_mode = MCPWM_UP_COUNTER;
    pwm_config_motor.duty_mode = MCPWM_DUTY_MODE_0;

    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config_motor);
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_1, &pwm_config_motor);
}

void setMotorSpeed(float duty_cycle)
{
    if (duty_cycle > 0)
    {
        mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, duty_cycle);
        mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, 0);
        mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_A, duty_cycle);
        mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_B, 0);
    }
    else
    {
        mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, 0);
        mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, -duty_cycle);
        mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_A, 0);
        mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_B, -duty_cycle);
    }
}
