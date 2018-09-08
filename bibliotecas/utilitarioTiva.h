/*
 * utilitarioTiva.h
 *
 *  Created on: 28 de mai de 2018
 *      Author: jhonathan
 */

#ifndef BIBLIOTECAS_UTILITARIOTIVA_H_
#define BIBLIOTECAS_UTILITARIOTIVA_H_
#include <tm4c123gh6pm.h>
#include <inttypes.h>

extern uint32_t microsAtual;
extern uint32_t millisAtual;

void configurarSysTick(uint32_t reload, uint32_t ctrl);
void delay(uint32_t millis);
void trataST();
uint32_t getMillis();
uint32_t getMicro();

#endif /* BIBLIOTECAS_UTILITARIOTIVA_H_ */
