#include "bibliotecas/utilitarioTiva.h"
#include "bibliotecas/gpioUtils.h"
#include <tm4c123gh6pm.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void trataST(void);
void trataPortA(void);
void trataPortB(void);
void trataPortC(void);
void trataPortD(void);
void trataPortE(void);
uint32_t leituraX;
uint32_t leituraY;
int pausado = 0;
int filaEnvios[20];
int index = 0;
#define UART_FR_TXFF            0x00000020          // UART Transmit FIFO Full
#define UART_FR_RXFE            0x00000010
void setup()
{
    configurarSysTick(400000, 0x03);

    //-----ATIVAR OS PORTS-----//
    ativarRCGC(RCGC_PORT_A);
    ativarRCGC(RCGC_PORT_B);
    ativarRCGC(RCGC_PORT_C);
    ativarRCGC(RCGC_PORT_D);
    ativarRCGC(RCGC_PORT_E);
    ativarRCGC(RCGC_PORT_F);
    SYSCTL_RCGCADC_R |= 0x01;
    SYSCTL_RCGCADC_R |= 0x02;


    //-----CONFIGURAR INTERRUPÇÕES BOTOES-----//
    configurarInterrupcao(&GPIO_PORTA_IS_R, &GPIO_PORTA_IEV_R,
                          &GPIO_PORTA_IBE_R, &GPIO_PORTA_IM_R, 2, 0, 1, 0);

    configurarInterrupcao(&GPIO_PORTA_IS_R, &GPIO_PORTA_IEV_R,
                          &GPIO_PORTA_IBE_R, &GPIO_PORTA_IM_R, 3, 0, 1, 0);


    //-----CONFIGURAR PINOS-----//
    configurarPino(&GPIO_PORTA_DIR_R, &GPIO_PORTA_DEN_R, 2, INPUT);
    configurarPino(&GPIO_PORTA_DIR_R, &GPIO_PORTA_DEN_R, 3, INPUT);

}
int main(void)
{
    setup();
    while (1)
    {

    }
}


void trataPortA()
{

}

void trataPortB()
{

}

void trataPortC()
{

}

void trataPortD()
{

}

void trataPortE()
{
}

void trataPortF()
{

}

