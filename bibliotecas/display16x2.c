/*
 * display16x2.c
 *
 *  Created on: 18 de set de 2018
 *      Author: jhoul
 */

#include "display16x2.h"
#include "utilitarioTiva.h"

void enablePulso(void){
    GPIO_PORTB_DATA_R = 0b00100000;
    delay(100000);
    GPIO_PORTB_DATA_R = 0b00000000;
}

void configLCD() {
    SYSCTL_RCGCGPIO_R |= 0b00000011;
    GPIO_PORTA_DIR_R = 0b11100000;
    GPIO_PORTA_DATA_R = 0b00000000;
    GPIO_PORTA_DEN_R = 0b11100000;
    GPIO_PORTB_DIR_R = 0b00011011;
    GPIO_PORTB_DEN_R = 0b00011011;
    GPIO_PORTB_DATA_R = 0b00000000;

    delay(20000);
    GPIO_PORTB_DATA_R = 0b00010000;
    GPIO_PORTA_DATA_R = 0b00100000;
    enablePulso();
    delay(5000);
    enablePulso();
    delay(2000);
    enablePulso();
    enablePulso();

    // modo 4 bit
    GPIO_PORTB_DATA_R = 0b00000000;
    GPIO_PORTA_DATA_R = 0b00100000;
    enablePulso();

    // 2linhas - 5x7
    GPIO_PORTB_DATA_R = 0b00000000;
    GPIO_PORTA_DATA_R = 0b00100000;
    enablePulso();
    GPIO_PORTB_DATA_R = 0b00000000;
    GPIO_PORTA_DATA_R = 0b10000000;
    enablePulso();

    // Desliga o Display
    GPIO_PORTB_DATA_R = 0b00000000;
    GPIO_PORTA_DATA_R = 0b00000000;
    enablePulso();
    GPIO_PORTB_DATA_R = 0b00000000;
    GPIO_PORTA_DATA_R = 0b10000000;
    enablePulso();

    // Limpa o Display
    GPIO_PORTB_DATA_R = 0b00000000;
    GPIO_PORTA_DATA_R = 0b00000000;
    enablePulso();
    GPIO_PORTB_DATA_R = 0b00010000;
    GPIO_PORTA_DATA_R = 0b00000000;
    enablePulso();

    // Funcionamento do Display
    GPIO_PORTB_DATA_R = 0b00000000;
    GPIO_PORTA_DATA_R = 0b00000000;
    enablePulso();
    GPIO_PORTB_DATA_R = 0b00000000;
    GPIO_PORTA_DATA_R = 0b01100000;
    enablePulso();
}

void cmdLCD(char data) {
    GPIO_PORTB_DATA_R = data & 0b00010000;
    GPIO_PORTA_DATA_R = data & 0b11100000;
    enablePulso();
    GPIO_PORTB_DATA_R = data << 4 & 0b00010000;
    GPIO_PORTA_DATA_R = data << 4 & 0b11100000;
    enablePulso();
}
