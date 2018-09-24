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

void setLoad(int pwmModule, int element, uint32_t frequencia)
{
    if (pwmModule == PWM_MODULO_A)
    {
        if (element == PWM_ELEMENT_0)
        {
            PWM0_0_LOAD_R = frequencia;
        }
        else if (element == PWM_ELEMENT_1)
        {
            PWM0_1_LOAD_R = frequencia;
        }
        else if (element == PWM_ELEMENT_2)
        {
            PWM0_2_LOAD_R = frequencia;
        }
        else if (element == PWM_ELEMENT_3)
        {
            PWM0_3_LOAD_R = frequencia;
        }
    }
    else if (pwmModule == PWM_MODULO_B)
    {
        if (element == PWM_ELEMENT_0)
        {
            PWM1_0_LOAD_R = frequencia;
        }
        else if (element == PWM_ELEMENT_1)
        {
            PWM1_1_LOAD_R = frequencia;
        }
        else if (element == PWM_ELEMENT_2)
        {
            PWM1_2_LOAD_R = frequencia;
        }
        else if (element == PWM_ELEMENT_3)
        {
            PWM1_3_LOAD_R = frequencia;
        }
    }
}

void setCmpa(int pwmModule, int element, uint32_t frequencia,
             uint32_t porcentagem)
{
    if (pwmModule == PWM_MODULO_A)
    {
        if (element == PWM_ELEMENT_0)
        {
            PWM0_0_CMPA_R = (frequencia * porcentagem) / 100;
        }
        else if (element == PWM_ELEMENT_1)
        {
            PWM0_1_CMPA_R = (frequencia * porcentagem) / 100;
        }
        else if (element == PWM_ELEMENT_2)
        {
            PWM0_2_CMPA_R = (frequencia * porcentagem) / 100;
        }
        else if (element == PWM_ELEMENT_3)
        {
            PWM0_3_CMPA_R = (frequencia * porcentagem) / 100;
        }
    }
    else if (pwmModule == PWM_MODULO_B)
    {
        if (element == PWM_ELEMENT_0)
        {
            PWM1_0_CMPA_R = (frequencia * porcentagem) / 100;
        }
        else if (element == PWM_ELEMENT_1)
        {
            PWM1_1_CMPA_R = (frequencia * porcentagem) / 100;
        }
        else if (element == PWM_ELEMENT_2)
        {
            PWM1_2_CMPA_R = (frequencia * porcentagem) / 100;
        }
        else if (element == PWM_ELEMENT_3)
        {
            PWM1_3_CMPA_R = (frequencia * porcentagem) / 100;
        }
    }
}

void setControle(int pwmModule, int element, uint32_t ctl)
{

    if (pwmModule == PWM_MODULO_A)
    {
        if (element == PWM_ELEMENT_0)
        {
            PWM0_0_CTL_R = ctl;
        }
        else if (element == PWM_ELEMENT_1)
        {
            PWM0_1_CTL_R = ctl;
        }
        else if (element == PWM_ELEMENT_2)
        {
            PWM0_2_CTL_R = ctl;
        }
        else if (element == PWM_ELEMENT_3)
        {
            PWM0_3_CTL_R = ctl;
        }

    }
    else if (pwmModule == PWM_MODULO_B)
    {
        if (element == PWM_ELEMENT_0)
        {
            PWM1_0_CTL_R = ctl;
        }
        else if (element == PWM_ELEMENT_1)
        {
            PWM1_1_CTL_R = ctl;
        }
        else if (element == PWM_ELEMENT_2)
        {
            PWM1_2_CTL_R = ctl;
        }
        else if (element == PWM_ELEMENT_3)
        {
            PWM1_3_CTL_R = ctl;
        }
    }
}

void iniciaPwm(int pwmModule, uint32_t start)
{
    if (pwmModule == PWM_MODULO_A)
    {
        PWM0_ENABLE_R = start;
    }
    else if (pwmModule == PWM_MODULO_B)
    {
        PWM1_ENABLE_R = start;
    }
}
