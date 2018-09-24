/*
 * pwm.h
 *
 *  Created on: 13 de set de 2018
 *      Author: jhonathan
 */

#ifndef BIBLIOTECAS_PWM_H_
#define BIBLIOTECAS_PWM_H_
#include <tm4c123gh6pm.h>
#include <inttypes.h>

//---Sessão dos Defines---//
#define PWM_MODULO_A 0
#define PWM_MODULO_B 0
#define PWM_ELEMENT_0 0
#define PWM_ELEMENT_1 1
#define PWM_ELEMENT_2 2
#define PWM_ELEMENT_3 3

//---Funções---//
void ativarModulo(int module);
void setGenerator(int pwmModule, int element, uint32_t mode); //Nivel baixo em LOAD / Nivel alto em CMPA
void setLoad(int pwmModule, int element, uint32_t frequencia); //Valor de frequencia do PWM, em ciclos de clock
void setCmpa(int pwmModule, int element, uint32_t frequencia, uint32_t porcentagem); //Valor de porcentagem do PWM, em ciclos de clock (Freq * porcentagem) / 100;
void setControle(int pwmModule, int element, uint32_t ctl); //Valor de porcentagem do PWM, em ciclos de clock
void iniciaPwm(int pwmModule, uint32_t start);

#endif /* BIBLIOTECAS_PWM_H_ */
