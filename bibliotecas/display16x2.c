/*
 * display16x2.c
 *
 *  Created on: 18 de set de 2018
 *      Author: jhoul
 */

#include "display16x2.h"
#include "utilitarioTiva.h"
#include "gpioUtils.h"

void pulso_enable()
{
    enable();
    delay(1);
    enable();
}

void enable()
{
    inverterBit(&GPIO_PORTA_DATA_R, DSP_E);
}

void limpaData()
{
    setarBit(&GPIO_PORTE_DATA_R, DSP_D0, 0);
    setarBit(&GPIO_PORTE_DATA_R, DSP_D1, 0);
    setarBit(&GPIO_PORTE_DATA_R, DSP_D2, 0);
    setarBit(&GPIO_PORTE_DATA_R, DSP_D3, 0);
    setarBit(&GPIO_PORTE_DATA_R, DSP_D4, 0);
    setarBit(&GPIO_PORTE_DATA_R, DSP_D5, 0);
    setarBit(&GPIO_PORTD_DATA_R, DSP_D6, 0);
    setarBit(&GPIO_PORTD_DATA_R, DSP_D7, 0);
}

void limpaRWE()
{
    setarBit(&GPIO_PORTA_DATA_R, DSP_RS, 0);
    setarBit(&GPIO_PORTA_DATA_R, DSP_RW, 0);
    setarBit(&GPIO_PORTA_DATA_R, DSP_E, 0);
}

void inicializa_LCD()
{

    delay(605);
    setarBit(&GPIO_PORTE_DATA_R, DSP_D4, 1);
    setarBit(&GPIO_PORTE_DATA_R, DSP_D5, 1);

    delay(100);
    pulso_enable();

    delay(200);
    pulso_enable();

    delay(200);
    pulso_enable();

    setarBit(&GPIO_PORTE_DATA_R, DSP_D2, 1);
    setarBit(&GPIO_PORTE_DATA_R, DSP_D3, 1);
    pulso_enable();

    limpaData();
    setarBit(&GPIO_PORTE_DATA_R, DSP_D3, 1);
    pulso_enable();

    limpaData();
    setarBit(&GPIO_PORTE_DATA_R, DSP_D0, 1);
    pulso_enable();

    setarBit(&GPIO_PORTE_DATA_R, DSP_D1, 1);
    setarBit(&GPIO_PORTE_DATA_R, DSP_D2, 1);
    pulso_enable();

    limpaData();
    setarBit(&GPIO_PORTE_DATA_R, DSP_D2, 1);
    setarBit(&GPIO_PORTE_DATA_R, DSP_D3, 1);
    pulso_enable();

    limpaData();
    setarBit(&GPIO_PORTE_DATA_R, DSP_D1, 1);
    setarBit(&GPIO_PORTE_DATA_R, DSP_D2, 1);
    pulso_enable();

    limpaData();
    setarBit(&GPIO_PORTE_DATA_R, DSP_D0, 1);
    pulso_enable();

    escreve_LCD("TESTEZAO DE TEXTO");

}

void limpaDisplay()
{
    limpaRWE();
    limpaData();
    setarBit(&GPIO_PORTE_DATA_R, DSP_D0, 1);
    pulso_enable();
    limpaData();
    setarBit(&GPIO_PORTE_DATA_R, DSP_D1, 1);
    pulso_enable();
}
void cmd_LCD(unsigned char c, int count)
{
    if (count == 17)
    {
        limpaRWE();
        limpaData();
        delay(4);
        setarBit(&GPIO_PORTD_DATA_R, DSP_D6, 1);
        setarBit(&GPIO_PORTD_DATA_R, DSP_D7, 1);
        pulso_enable();
    }
    limpaRWE();

    setarBit(&GPIO_PORTA_DATA_R, DSP_RS, 1);

    delay(1);
    limpaData();
    GPIO_PORTE_DATA_R = c;
    if (((c & 0x40) == 0x40))
    {
        setarBit(&GPIO_PORTD_DATA_R, DSP_D6, 1);
    }

    if (((c & 0x80) == 0x80))
    {
        setarBit(&GPIO_PORTD_DATA_R, DSP_D7, 1);
    }
    pulso_enable();

}

void escreve_LCD(char *c)
{
    int count = 0;
    for (; *c != 0; c++)
    {
        count++;
        cmd_LCD(*c, count);

    }
}

void menuUm()
{
    limpaDisplay();
    escreve_LCD("Selecione o Led   1   2   3   4");
}

void menuDois()
{
    limpaDisplay();
    escreve_LCD("Modo de operacao           1   2");
}

void menuTres(int porcentagem)
{
    char numero[32];
    char texto[64];
    if (porcentagem < 10)
    {
        strcpy(texto, "PWM(0-100)                     ");
    }
    else
    {
        strcpy(texto, "PWM(0-100)                    ");
    }

    itoa(porcentagem, numero, 10);
    strcat(texto, numero);
    limpaDisplay();
    escreve_LCD(texto);
}
void menuQuatro(int tempo)
{
    char numero[32];
    char texto[64];
    if (tempo < 10)
    {
        strcpy(texto, "Tempo Ligado                  ");
    }
    else
    {
        strcpy(texto, "Tempo Ligado                 ");
    }

    itoa(tempo, numero, 10);
    strcat(texto, numero);
    strcat(texto, "s");
    limpaDisplay();
    escreve_LCD(texto);
}
