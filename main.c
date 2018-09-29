#include "bibliotecas/utilitarioTiva.h"
#include "bibliotecas/gpioUtils.h"
#include "bibliotecas/eeprom.h"
#include "bibliotecas/pwm.h"
#include "bibliotecas/display16x2.h"
#include <tm4c123gh6pm.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOTAO_0 PINO3
#define BOTAO_1 PINO5
#define BOTAO_2 PINO4
#define BOTAO_3 PINO7
#define LED_0 PINO6
#define LED_1 PINO7
#define LED_2 PINO4
#define LED_3 PINO5

void trataST(void);
void trataPortA(void);
void trataPortB(void);
void trataPortC(void);
void trataPortD(void);
void trataPortE(void);

void setup()
{

    //-----ATIVAR OS PORTS-----//
    ativarRCGC(RCGC_PORT_A);
    ativarRCGC(RCGC_PORT_B);
    ativarRCGC(RCGC_PORT_C);
    ativarRCGC(RCGC_PORT_D);
    ativarRCGC(RCGC_PORT_E);
    ativarRCGC(RCGC_PORT_F);

    configurarSysTick(16, 0x03);

    ativarModulo(PWM_MODULO_A);

    //-----CONFIGURAR INTERRUPÇÕES BOTOES-----//
    configurarInterrupcao(&GPIO_PORTB_IS_R, &GPIO_PORTB_IEV_R,
                          &GPIO_PORTB_IBE_R, &GPIO_PORTB_IM_R, BOTAO_0, 0, 1,
                          1); //Botão 0

    configurarInterrupcao(&GPIO_PORTC_IS_R, &GPIO_PORTC_IEV_R,
                          &GPIO_PORTC_IBE_R, &GPIO_PORTC_IM_R, BOTAO_1, 0, 1,
                          2); //Botão 1

    configurarInterrupcao(&GPIO_PORTC_IS_R, &GPIO_PORTC_IEV_R,
                          &GPIO_PORTC_IBE_R, &GPIO_PORTC_IM_R, BOTAO_2, 0, 1,
                          2); //Botão 2

    configurarInterrupcao(&GPIO_PORTC_IS_R, &GPIO_PORTC_IEV_R,
                          &GPIO_PORTC_IBE_R, &GPIO_PORTC_IM_R, BOTAO_3, 0, 1,
                          2); //Botão 3

    habilitarPWMPorts(&GPIO_PORTB_AFSEL_R, &GPIO_PORTB_PCTL_R, LED_0, 26);
    habilitarPWMPorts(&GPIO_PORTB_AFSEL_R, &GPIO_PORTB_PCTL_R, LED_1, 30);
    habilitarPWMPorts(&GPIO_PORTB_AFSEL_R, &GPIO_PORTB_PCTL_R, LED_2,18);
    habilitarPWMPorts(&GPIO_PORTB_AFSEL_R, &GPIO_PORTB_PCTL_R, LED_3,22);

    //-----CONFIGURAR PINOS-----//
    //Botões
    configurarPino(&GPIO_PORTB_DIR_R, &GPIO_PORTB_DEN_R, BOTAO_0, INPUT);
    configurarPino(&GPIO_PORTC_DIR_R, &GPIO_PORTC_DEN_R, BOTAO_1, INPUT);
    configurarPino(&GPIO_PORTC_DIR_R, &GPIO_PORTC_DEN_R, BOTAO_2, INPUT);
    configurarPino(&GPIO_PORTC_DIR_R, &GPIO_PORTC_DEN_R, BOTAO_3, INPUT);
    //LEDs

    configurarPino(&GPIO_PORTB_DIR_R, &GPIO_PORTB_DEN_R, LED_0, OUTPUT);
    configurarPino(&GPIO_PORTB_DIR_R, &GPIO_PORTB_DEN_R, LED_1, OUTPUT);
    configurarPino(&GPIO_PORTB_DIR_R, &GPIO_PORTB_DEN_R, LED_2, OUTPUT);
    configurarPino(&GPIO_PORTB_DIR_R, &GPIO_PORTB_DEN_R, LED_3, OUTPUT);

    //PWM
    setControle(PWM_MODULO_A, PWM_ELEMENT_0, 0);
    configurarPWM(0, PWM_MODULO_A, PWM_ELEMENT_0, 0xC8, 16000, 99, 0x01);
    configurarPWM(1, PWM_MODULO_A, PWM_ELEMENT_0, 0xC08, 16000, 50, 0x01);
    setControle(PWM_MODULO_A, PWM_ELEMENT_0, 0x01);

    setControle(PWM_MODULO_A, PWM_ELEMENT_1, 0);
    configurarPWM(0, PWM_MODULO_A, PWM_ELEMENT_1, 0xC8, 16000, 99, 0x01);
    configurarPWM(1, PWM_MODULO_A, PWM_ELEMENT_1, 0xC08, 16000, 50, 0x01);
    setControle(PWM_MODULO_A, PWM_ELEMENT_1, 0x01);

    iniciaPwm(PWM_MODULO_A, 0x0F);
}
int main(void)
{
//    //Ligar o PortB
//        SYSCTL_RCGCGPIO_R = 0x02;
//        SYSCTL_RCGCPWM_R = 0x01;
//        //Habilitar função alternativa do PB6
//        GPIO_PORTB_AFSEL_R = 0x40;
//        //Definir que a função alternativa do PB6 é PWM
//        GPIO_PORTB_PCTL_R = 0x04000000;
//        //Habilita PB6 digitalmente
//        GPIO_PORTB_DEN_R = 0x40;
//
//        //Ativa o modulo de PWM 0
//
//        //Nivel baixo em LOAD / Nivel alto em CMPA
//        PWM0_0_GENA_R = 0xC8;
//        //Valor de frequencia do PWM, em ciclos de clock
//        PWM0_0_LOAD_R = 16000;
//        //Valor de porcentagem do PWM, em ciclos de clock
//        PWM0_0_CMPA_R =3200;
//        //Ativa o controle do elemento 0 do PWM0
//        PWM0_0_CTL_R = 0x01;
//        //Inicializa o PWM0 - Gerador
//        PWM0_ENABLE_R = 0x01;
    setup();
    while (1)
    {
        __asm("WFI");
    }
}

void trataPortA()
{
    getMillis();
}

void trataPortB()
{
    if (lerBit(&GPIO_PORTB_RIS_R, BOTAO_0))
    {
        setarBit(&GPIO_PORTB_ICR_R, BOTAO_0, 1);
    }
}

void trataPortC()
{
    if (lerBit(&GPIO_PORTC_RIS_R, BOTAO_1)) //Verificação de qual pino gerou a inten
    {
        setarBit(&GPIO_PORTC_ICR_R, BOTAO_1, 1); //Limpa flag de int do pino que gerou a inten
    }
    else if (lerBit(&GPIO_PORTC_RIS_R, BOTAO_2))
    {
        setarBit(&GPIO_PORTC_ICR_R, BOTAO_2, 1);
    }
    else if (lerBit(&GPIO_PORTC_RIS_R, BOTAO_3))
    {
        setarBit(&GPIO_PORTC_ICR_R, BOTAO_3, 1);
    }
}

void trataPortD()
{
    getMillis();
}

void trataPortE()
{
    getMillis();
}

void trataPortF()
{
    getMillis();
}

