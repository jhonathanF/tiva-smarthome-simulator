/*
 * gpioUtils.h
 *
 *  Created on: 28 de mai de 2018
 *      Author: jhonathan
 */

#ifndef BIBLIOTECAS_GPIOUTILS_H_
#define BIBLIOTECAS_GPIOUTILS_H_
#include <tm4c123gh6pm.h>
#include <inttypes.h>

#define RCGC_PORT_A 0
#define RCGC_PORT_B 1
#define RCGC_PORT_C 2
#define RCGC_PORT_D 3
#define RCGC_PORT_E 4
#define RCGC_PORT_F 5

#define OUTPUT 1
#define INPUT 0

#define PINO0 0
#define PINO1 1
#define PINO2 2
#define PINO3 3
#define PINO4 4
#define PINO5 5
#define PINO6 6
#define PINO7 7

#define HIGH 1
#define LOW 0

void ativarRCGC(int port);
void ativarADC(int ADC);
int lerBit(volatile uint32_t *registrador, int bit);
void setarBit(volatile uint32_t *registrador, int bit, int valor);
void inverterBit(volatile uint32_t *registrador, int bit);
void configurarPino(volatile uint32_t *portDir, volatile uint32_t *portDen, int pino, int valor);
void configurarInterrupcao(volatile uint32_t *IS, volatile uint32_t *IEV, volatile uint32_t *IBE, volatile uint32_t *IM, int pino, int sensibilidade, int subidaDescida, int port);
void habilitarADCPorts(volatile uint32_t *AFSEL , volatile uint32_t *AMSEL ,int pino);
void configurarADC0(uint32_t EMUX, uint32_t SSMUX, uint32_t SSCTL, uint32_t SS, uint32_t ctrl,  int fila);
void configurarFilaADC0(uint32_t SSMUX, uint32_t SSCTL, int fila);
void configurarADC1(uint32_t EMUX, uint32_t SSMUX, uint32_t SSCTL, uint32_t SS, uint32_t ctrl,  int fila);
void configurarFilaADC1(uint32_t SSMUX, uint32_t SSCTL, int fila);
void configurarUART0(uint32_t RCGcUART,volatile uint32_t *AFSEL,volatile uint32_t *PCTL, int IBDR, int FBRD, uint32_t LCRH, uint32_t CC, uint32_t CTL);
void escreverUART0(unsigned char data);
#endif /* BIBLIOTECAS_GPIOUTILS_H_ */
