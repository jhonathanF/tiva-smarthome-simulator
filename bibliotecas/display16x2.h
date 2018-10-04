/*
 * display16x2.h
 *
 *  Created on: 18 de set de 2018
 *      Author: jhoul
 */

#ifndef BIBLIOTECAS_DISPLAY16X2_H_
#define BIBLIOTECAS_DISPLAY16X2_H_
#include <tm4c123gh6pm.h>
#include <inttypes.h>

#define DSP_RS PINO5
#define DSP_RW PINO7
#define DSP_E PINO6
#define DSP_D0 PINO0
#define DSP_D1 PINO1
#define DSP_D2 PINO2
#define DSP_D3 PINO3
#define DSP_D4 PINO4
#define DSP_D5 PINO5
#define DSP_D6 PINO2
#define DSP_D7 PINO3

void pulso_enable();
void inicializa_LCD();
void cmd_LCD(unsigned char c, int count);
void escreve_LCD(char *c);
void limpaData();
void limpaRWE();
void enable();
void limpaDisplay();
void menuUm();
void menuDois();
void menuTres();
void menuQuatro();

#endif /* BIBLIOTECAS_DISPLAY16X2_H_ */
