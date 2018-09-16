/*
 * pwm.c
 *
 *  Created on: 13 de set de 2018
 *      Author: jhoul
 */
#include "pwm.h"

void ativarModulo(int module)
{
    if (module == PWM_MODULO_A)
    {
        SYSCTL_RCGCPWM_R = 0x01;
    }
    else if (module == PWM_MODULO_B)
    {
        //        SYSCTL_RCGC  = 0x01;
    }
}

void setGenerator(int pwmModule, int element, uint32_t mode)
{
    if (pwmModule == PWM_MODULO_A)
    {
        if (element == PWM_ELEMENT_0)
        {
            PWM0_0_GENA_R = mode;
        }
        else if (element == PWM_ELEMENT_1)
        {
            PWM0_1_GENA_R = mode;
        }
        else if (element == PWM_ELEMENT_2)
        {
            PWM0_2_GENA_R = mode;
        }
        else if (element == PWM_ELEMENT_3)
        {
            PWM0_3_GENA_R = mode;
        }

    }
    else if (pwmModule == PWM_MODULO_B)
    {
        if (element == PWM_ELEMENT_0)
        {
            PWM1_0_GENA_R = mode;
        }
        else if (element == PWM_ELEMENT_1)
        {
            PWM1_1_GENA_R = mode;
        }
        else if (element == PWM_ELEMENT_2)
        {
            PWM1_2_GENA_R = mode;
        }
        else if (element == PWM_ELEMENT_3)
        {
            PWM1_3_GENA_R = mode;
        }

    }
}
