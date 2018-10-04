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

#define BOTAO_0 PINO6
#define BOTAO_1 PINO3
#define BOTAO_2 PINO6
#define BOTAO_3 PINO7
#define LED_0 PINO6
#define LED_1 PINO7
#define LED_2 PINO4
#define LED_3 PINO5

void populaStructEeprom();
void populaStructLeds();
void gravaDadosEeprom(int led);
void trataMenu();
void trataST(void);
void trataPortA(void);
void trataPortB(void);
void trataPortC(void);
void trataPortD(void);
void trataPortE(void);
int pcta = 0;
int mudar = 0;

typedef struct
{
    uint32_t block;
    uint32_t offset;
} eepromConfig;

typedef struct
{
    uint32_t modoOperacao;
    uint32_t porcentagem;
    int tempoLigado;
    uint32_t millisCountDown;
    uint32_t alterado;

} ledConfig;

typedef struct
{
    int tela;
    int opcao;
    int alterado;
    int ledSelecionado;
    int porcentagem;
    int tempoLigado;
} menuConfig;

eepromConfig eeprom[4][4];
ledConfig leds[4];
menuConfig menu[1];

void setup()
{

    //-----ATIVAR OS PORTS-----//
    ativarRCGC(RCGC_PORT_A);
    ativarRCGC(RCGC_PORT_B);
    ativarRCGC(RCGC_PORT_C);
    ativarRCGC(RCGC_PORT_D);
    ativarRCGC(RCGC_PORT_E);
    ativarRCGC(RCGC_PORT_F);

    configurarSysTick(4000, 0x03);

    ativarModulo(PWM_MODULO_A);

    //-----CONFIGURAR INTERRUPÇÕES BOTOES-----//
    configurarInterrupcao(&GPIO_PORTD_IS_R, &GPIO_PORTD_IEV_R,
                          &GPIO_PORTD_IBE_R, &GPIO_PORTD_IM_R, BOTAO_0, 0, 1,
                          3); //Botão 0

    configurarInterrupcao(&GPIO_PORTA_IS_R, &GPIO_PORTA_IEV_R,
                          &GPIO_PORTA_IBE_R, &GPIO_PORTA_IM_R, BOTAO_1, 0, 1,
                          0); //Botão 1

    configurarInterrupcao(&GPIO_PORTC_IS_R, &GPIO_PORTC_IEV_R,
                          &GPIO_PORTC_IBE_R, &GPIO_PORTC_IM_R, BOTAO_2, 0, 1,
                          2); //Botão 2

    configurarInterrupcao(&GPIO_PORTC_IS_R, &GPIO_PORTC_IEV_R,
                          &GPIO_PORTC_IBE_R, &GPIO_PORTC_IM_R, BOTAO_3, 0, 1,
                          2); //Botão 3

    //    HABILITAR PWM PINO
    habilitarPWMPorts(&GPIO_PORTB_AFSEL_R, &GPIO_PORTB_PCTL_R, LED_0, 26);
    habilitarPWMPorts(&GPIO_PORTB_AFSEL_R, &GPIO_PORTB_PCTL_R, LED_1, 30);
    habilitarPWMPorts(&GPIO_PORTB_AFSEL_R, &GPIO_PORTB_PCTL_R, LED_2, 18);
    habilitarPWMPorts(&GPIO_PORTB_AFSEL_R, &GPIO_PORTB_PCTL_R, LED_3, 22);

    //-----CONFIGURAR PINOS-----//
    //Botões
    configurarPino(&GPIO_PORTD_DIR_R, &GPIO_PORTD_DEN_R, BOTAO_0, INPUT);
    configurarPino(&GPIO_PORTA_DIR_R, &GPIO_PORTA_DEN_R, BOTAO_1, INPUT);
    configurarPino(&GPIO_PORTC_DIR_R, &GPIO_PORTC_DEN_R, BOTAO_2, INPUT);
    configurarPino(&GPIO_PORTC_DIR_R, &GPIO_PORTC_DEN_R, BOTAO_3, INPUT);
    //LEDs

    configurarPino(&GPIO_PORTB_DIR_R, &GPIO_PORTB_DEN_R, LED_0, OUTPUT);
    configurarPino(&GPIO_PORTB_DIR_R, &GPIO_PORTB_DEN_R, LED_1, OUTPUT);
    configurarPino(&GPIO_PORTB_DIR_R, &GPIO_PORTB_DEN_R, LED_2, OUTPUT);
    configurarPino(&GPIO_PORTB_DIR_R, &GPIO_PORTB_DEN_R, LED_3, OUTPUT);

//    //PWM
    setControle(PWM_MODULO_A, PWM_ELEMENT_0, 0);
    configurarPWM(0, PWM_MODULO_A, PWM_ELEMENT_0, 0xC8, 16000, 0, 0x01);
    configurarPWM(1, PWM_MODULO_A, PWM_ELEMENT_0, 0xC08, 16000, 0, 0x01);
    setControle(PWM_MODULO_A, PWM_ELEMENT_0, 0x01);

    setControle(PWM_MODULO_A, PWM_ELEMENT_1, 0);
    configurarPWM(0, PWM_MODULO_A, PWM_ELEMENT_1, 0xC8, 16000, 0, 0x01);
    configurarPWM(1, PWM_MODULO_A, PWM_ELEMENT_1, 0xC08, 16000, 0, 0x01);
    setControle(PWM_MODULO_A, PWM_ELEMENT_1, 0x01);

    iniciaPwm(PWM_MODULO_A, 0x0F);

    //DISPLAY
    configurarPino(&GPIO_PORTA_DIR_R, &GPIO_PORTA_DEN_R, DSP_RS, OUTPUT);
    configurarPino(&GPIO_PORTA_DIR_R, &GPIO_PORTA_DEN_R, DSP_RW, OUTPUT);
    configurarPino(&GPIO_PORTA_DIR_R, &GPIO_PORTA_DEN_R, DSP_E, OUTPUT);
    configurarPino(&GPIO_PORTE_DIR_R, &GPIO_PORTE_DEN_R, DSP_D0, OUTPUT);
    configurarPino(&GPIO_PORTE_DIR_R, &GPIO_PORTE_DEN_R, DSP_D1, OUTPUT);
    configurarPino(&GPIO_PORTE_DIR_R, &GPIO_PORTE_DEN_R, DSP_D2, OUTPUT);
    configurarPino(&GPIO_PORTE_DIR_R, &GPIO_PORTE_DEN_R, DSP_D3, OUTPUT);
    configurarPino(&GPIO_PORTE_DIR_R, &GPIO_PORTE_DEN_R, DSP_D4, OUTPUT);
    configurarPino(&GPIO_PORTE_DIR_R, &GPIO_PORTE_DEN_R, DSP_D5, OUTPUT);
    configurarPino(&GPIO_PORTD_DIR_R, &GPIO_PORTD_DEN_R, DSP_D6, OUTPUT);
    configurarPino(&GPIO_PORTD_DIR_R, &GPIO_PORTD_DEN_R, DSP_D7, OUTPUT);
//
    inicializa_LCD();
    startEeprom();
}

int main(void)
{
    setup();
    populaStructEeprom();
    populaStructLeds();
    menu[0].alterado = 0;
    menu[0].tela = 0;
    menu[0].opcao = 0;
    menu[0].ledSelecionado = 0;
    menu[0].porcentagem = 0;
    menu[0].tempoLigado = 0;
    menuUm();

    while (1)
    {
        trataMenu();
        int i = 0;
        for (i = 0; i < 4; i++)
        {
            if (leds[i].alterado)
            {
                if (leds[i].modoOperacao == 0)
                {

                    if (i < 2)
                    {
                        if (i == 0)
                        {
                            setCmpa(PWM_MODULO_A, PWM_ELEMENT_0, 16000,
                                    leds[i].porcentagem);
                        }
                        else
                        {
                            setCmpb(PWM_MODULO_A, PWM_ELEMENT_0, 16000,
                                    leds[i].porcentagem);
                        }
                    }
                    else
                    {

                        if (i == 2)
                        {
                            setCmpa(PWM_MODULO_A, PWM_ELEMENT_1, 16000,
                                    leds[i].porcentagem);
                        }
                        else
                        {
                            setCmpb(PWM_MODULO_A, PWM_ELEMENT_1, 16000,
                                    leds[i].porcentagem);
                        }
                    }

                    leds[i].alterado = 0;

                }
                else
                {
                    if (getMillis() - leds[i].millisCountDown
                            <= (leds[i].tempoLigado * 1000))
                    {
                        if (i < 2)
                        {
                            if (i == 0)
                            {
                                setCmpa(PWM_MODULO_A, PWM_ELEMENT_0, 16000, 99);
                            }
                            else
                            {
                                setCmpb(PWM_MODULO_A, PWM_ELEMENT_0, 16000, 99);
                            }
                        }
                        else
                        {

                            if (i == 2)
                            {
                                setCmpa(PWM_MODULO_A, PWM_ELEMENT_1, 16000, 99);
                            }
                            else
                            {
                                setCmpb(PWM_MODULO_A, PWM_ELEMENT_1, 16000, 99);
                            }
                        }
                    }
                    else
                    {
                        if (i < 2)
                        {
                            if (i == 0)
                            {
                                setCmpa(PWM_MODULO_A, PWM_ELEMENT_0, 16000, 0);
                            }
                            else
                            {
                                setCmpb(PWM_MODULO_A, PWM_ELEMENT_0, 16000, 0);
                            }
                        }
                        else
                        {

                            if (i == 2)
                            {
                                setCmpa(PWM_MODULO_A, PWM_ELEMENT_1, 16000, 0);
                            }
                            else
                            {
                                setCmpb(PWM_MODULO_A, PWM_ELEMENT_1, 16000, 0);
                            }
                        }
                        leds[i].alterado = 0;

                    }
                }
            }
        }
    }
}
void populaStructEeprom()
{
    int i = 0;
    for (i = 0; i < 4; i++)
    {
        if (i == 0)
        {
            eeprom[i][0].block = 0;
            eeprom[i][0].offset = 0;
            eeprom[i][1].block = 0;
            eeprom[i][1].offset = 1;
            eeprom[i][2].block = 1;
            eeprom[i][2].offset = 0;
            eeprom[i][3].block = 1;
            eeprom[i][3].offset = 1;
        }
        else if (i == 1)
        {
            eeprom[i][0].block = 2;
            eeprom[i][0].offset = 0;
            eeprom[i][1].block = 2;
            eeprom[i][1].offset = 1;
            eeprom[i][2].block = 3;
            eeprom[i][2].offset = 0;
            eeprom[i][3].block = 3;
            eeprom[i][3].offset = 1;
        }
        else if (i == 2)
        {
            eeprom[i][0].block = 4;
            eeprom[i][0].offset = 0;
            eeprom[i][1].block = 4;
            eeprom[i][1].offset = 1;
            eeprom[i][2].block = 5;
            eeprom[i][2].offset = 0;
            eeprom[i][3].block = 5;
            eeprom[i][3].offset = 1;
        }
        else
        {
            eeprom[i][0].block = 6;
            eeprom[i][0].offset = 0;
            eeprom[i][1].block = 6;
            eeprom[i][1].offset = 1;
            eeprom[i][2].block = 7;
            eeprom[i][2].offset = 0;
            eeprom[i][3].block = 7;
            eeprom[i][3].offset = 1;
        }
    }
}
void populaStructLeds()
{
    int i = 0;
    for (i = 0; i < 4; i++)
    {
        leds[i].modoOperacao = EEPROM_read(eeprom[i][0].block,
                                           eeprom[i][0].offset);

        leds[i].porcentagem = EEPROM_read(eeprom[i][1].block,
                                          eeprom[i][1].offset);

        leds[i].tempoLigado = EEPROM_read(eeprom[i][2].block,
                                          eeprom[i][2].offset);

        leds[i].alterado = EEPROM_read(eeprom[i][3].block, eeprom[i][3].offset);

        leds[i].millisCountDown = getMillis();

    }
}

void gravaDadosEeprom(int led)
{
    EEPROM_write(eeprom[led][0].block, eeprom[led][0].offset,
                 leds[led].modoOperacao);

    EEPROM_write(eeprom[led][1].block, eeprom[led][1].offset,
                 leds[led].porcentagem);

    EEPROM_write(eeprom[led][2].block, eeprom[led][2].offset,
                 leds[led].tempoLigado);

    EEPROM_write(eeprom[led][3].block, eeprom[led][3].offset, leds[led].alterado);
}

void trataMenu()
{
    if (menu[0].alterado)
    {

        if (menu[0].tela == 0)
        {
            menu[0].tela = 1;
            menu[0].ledSelecionado = menu[0].opcao;
            menuDois();
        }
        else if (menu[0].tela == 1)
        {
            if (menu[0].opcao == 0) //Modo 1
            {
                menu[0].tela = 2;
                menu[0].porcentagem = leds[menu[0].ledSelecionado].porcentagem;
                menuTres(menu[0].porcentagem);
            }
            else if (menu[0].opcao == 1) //Modo 2
            {
                menu[0].tela = 3;
                menu[0].tempoLigado = leds[menu[0].ledSelecionado].tempoLigado;
                menuQuatro(menu[0].tempoLigado);
            }
            else
            {
                menu[0].tela = 0;
                menuUm();
            }
        }
        else if (menu[0].tela == 2)
        {
            if (menu[0].opcao == 0)
            {
                if (menu[0].porcentagem > 0)
                {
                    menu[0].porcentagem--;
                }
                else
                {
                    menu[0].porcentagem = 99;
                }
                menuTres(menu[0].porcentagem);
            }
            else if (menu[0].opcao == 1)
            {
                if (menu[0].porcentagem < 99)
                {
                    menu[0].porcentagem++;
                }
                else
                {
                    menu[0].porcentagem = 0;
                }
                menuTres(menu[0].porcentagem);
            }
            else if (menu[0].opcao == 2)
            {
                leds[menu[0].ledSelecionado].modoOperacao = 0;
                leds[menu[0].ledSelecionado].porcentagem = menu[0].porcentagem;
                leds[menu[0].ledSelecionado].alterado = 1;
                gravaDadosEeprom(menu[0].ledSelecionado);
                menu[0].tela = 0;
                menu[0].porcentagem = 0;
                menuUm();
            }
        }
        else if (menu[0].tela == 3)
        {
            if (menu[0].opcao == 0)
            {
                if (menu[0].tempoLigado > 0)
                {
                    menu[0].tempoLigado--;
                }
                else
                {
                    menu[0].tempoLigado = 60;
                }
                menuQuatro(menu[0].tempoLigado);
            }
            else if (menu[0].opcao == 1)
            {
                if (menu[0].tempoLigado < 60)
                {
                    menu[0].tempoLigado++;
                }
                else
                {
                    menu[0].tempoLigado = 0;
                }
                menuQuatro(menu[0].tempoLigado);
            }
            else if (menu[0].opcao == 2)
            {
                leds[menu[0].ledSelecionado].modoOperacao = 1;
                leds[menu[0].ledSelecionado].tempoLigado = menu[0].tempoLigado;
                leds[menu[0].ledSelecionado].millisCountDown = getMillis();
                leds[menu[0].ledSelecionado].alterado = 1;
                gravaDadosEeprom(menu[0].ledSelecionado);
                menu[0].tela = 0;
                menu[0].tempoLigado = 0;
                menuUm();
            }
        }
        menu[0].alterado = 0;
    }
}

void trataPortA()
{
    if (lerBit(&GPIO_PORTA_RIS_R, BOTAO_1)) //Verificação de qual pino gerou a inten
    {
        menu[0].alterado = 1;
        menu[0].opcao = 1;

        setarBit(&GPIO_PORTA_ICR_R, BOTAO_1, 1); //Limpa flag de int do pino que gerou a inten
    }
}

void trataPortB()
{

}

void trataPortC()
{

    if (lerBit(&GPIO_PORTC_RIS_R, BOTAO_2))
    {
        menu[0].alterado = 1;
        menu[0].opcao = 2;
        setarBit(&GPIO_PORTC_ICR_R, BOTAO_2, 1);
    }
    else if (lerBit(&GPIO_PORTC_RIS_R, BOTAO_3))
    {
        menu[0].alterado = 1;
        menu[0].opcao = 3;
        setarBit(&GPIO_PORTC_ICR_R, BOTAO_3, 1);
    }
}

void trataPortD()
{
    if (lerBit(&GPIO_PORTD_RIS_R, BOTAO_0)) //Verificação de qual pino gerou a inten
    {
        menu[0].alterado = 1;
        menu[0].opcao = 0;
        setarBit(&GPIO_PORTD_ICR_R, BOTAO_0, 1); //Limpa flag de int do pino que gerou a inten
    }

}

void trataPortE()
{
    getMillis();
}

void trataPortF()
{
    getMillis();
}

