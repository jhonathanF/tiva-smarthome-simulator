#include "gpioUtils.h"

void setarBit(volatile uint32_t *registrador, int bit, int valor)
{
    (valor ? (*registrador |= (1 << bit)) : (*registrador &= ~(1 << bit)));

}

void inverterBit(volatile uint32_t *registrador, int bit)
{
    *registrador ^= (1 << bit);
}

int lerBit(volatile uint32_t *registrador, int bit)
{

    return *registrador & (1 << bit);

}

void configurarPino(volatile uint32_t *portDir, volatile uint32_t *portDen,
                    int pino, int valor)
{
    setarBit(portDir, pino, valor);
    setarBit(portDen, pino, 1);

}

void ativarRCGC(int port)
{
    SYSCTL_RCGCGPIO_R |= (1 << port);

}
void ativarADC(int ADC)
{

    SYSCTL_RCGCADC_R |= (1 << ADC);

}
void configurarInterrupcao(volatile uint32_t *IS, volatile uint32_t *IEV,
                           volatile uint32_t *IBE, volatile uint32_t *IM,
                           int pino, int sensibilidade, int subidaDescidaAmbos,
                           int port)
{
    setarBit(IS, pino, sensibilidade); //Define sensibilidade do botão - 0 borda - 1 sinal continuo
    if (subidaDescidaAmbos < 2)
    {
        setarBit(IEV, pino, subidaDescidaAmbos); //Define evento - 0 descida | baixo - 1 subida | alto
    }
    else
    {
        setarBit(IBE, pino, 0); //Define evento - 0 descida | baixo - 1 subida | alto

    }
    setarBit(IM, pino, 1); //Habilita a interrupção no pino
    setarBit(&NVIC_EN0_R, port, 1);

}

void habilitarADCPorts(volatile uint32_t *AFSEL, volatile uint32_t *AMSEL,
                       int pino)
{

    setarBit(AFSEL, pino, 1); //Função Alternativa
    setarBit(AMSEL, pino, 1); //Modo Analogico
}

void configurarADC0(uint32_t EMUX, uint32_t SSMUX, uint32_t SSCTL, uint32_t SS,
                    uint32_t ctrl, int fila)
{
    ADC0_ACTSS_R = 0x00; //Limpar Sample Sequencer
    ADC0_EMUX_R = EMUX; // Event Multiplexer, Taxa de amostragem, indica qual o trigger para a proxima leitura (Continuo, Timer)
    configurarFilaADC0(SSMUX, SSCTL, fila);
    ADC0_ACTSS_R = SS; //Liga Fila
    ADC0_PSSI_R = ctrl; //Inicializa Fila
}

void configurarFilaADC0(uint32_t SSMUX, uint32_t SSCTL, int fila)
{
    switch (fila)
    {
    case 0:
        ADC0_SSMUX0_R = SSMUX; //SSInput Multiplex, Sequencia a ser lida (Ex.: AIN7, joga valor 7)
        ADC0_SSCTL0_R = SSCTL; //Indica ultima posição da fila
        break;
    case 1:
        ADC0_SSMUX1_R = SSMUX; //SSInput Multiplex, Sequencia a ser lida (Ex.: AIN7, joga valor 7)
        ADC0_SSCTL1_R = SSCTL; //Indica ultima posição da fila
        break;
    case 2:
        ADC0_SSMUX2_R = SSMUX; //SSInput Multiplex, Sequencia a ser lida (Ex.: AIN7, joga valor 7)
        ADC0_SSCTL2_R = SSCTL; //Indica ultima posição da fila
        break;
    case 3:
        ADC0_SSMUX3_R = SSMUX; //SSInput Multiplex, Sequencia a ser lida (Ex.: AIN7, joga valor 7)
        ADC0_SSCTL3_R = SSCTL; //Indica ultima posição da fila
        break;

    }
}
void configurarADC1(uint32_t EMUX, uint32_t SSMUX, uint32_t SSCTL, uint32_t SS,
                    uint32_t ctrl, int fila)
{
    ADC1_ACTSS_R = 0x00; //Limpar Sample Sequencer
    ADC1_EMUX_R = EMUX; // Event Multiplexer, Taxa de amostragem, indica qual o trigger para a proxima leitura (Continuo, Timer)
    configurarFilaADC1(SSMUX, SSCTL, fila);
    ADC1_ACTSS_R = SS; //Liga Fila
    ADC1_PSSI_R = ctrl; //Inicializa Fila
}

void configurarFilaADC1(uint32_t SSMUX, uint32_t SSCTL, int fila)
{
    switch (fila)
    {
    case 0:
        ADC1_SSMUX0_R = SSMUX; //SSInput Multiplex, Sequencia a ser lida (Ex.: AIN7, joga valor 7)
        ADC1_SSCTL0_R = SSCTL; //Indica ultima posição da fila
        break;
    case 1:
        ADC1_SSMUX1_R = SSMUX; //SSInput Multiplex, Sequencia a ser lida (Ex.: AIN7, joga valor 7)
        ADC1_SSCTL1_R = SSCTL; //Indica ultima posição da fila
        break;
    case 2:
        ADC1_SSMUX2_R = SSMUX; //SSInput Multiplex, Sequencia a ser lida (Ex.: AIN7, joga valor 7)
        ADC1_SSCTL2_R = SSCTL; //Indica ultima posição da fila
        break;
    case 3:
        ADC1_SSMUX3_R = SSMUX; //SSInput Multiplex, Sequencia a ser lida (Ex.: AIN7, joga valor 7)
        ADC1_SSCTL3_R = SSCTL; //Indica ultima posição da fila
        break;

    }
}

void configurarUART0(uint32_t RCGcUART, volatile uint32_t *AFSEL,
                     volatile uint32_t *PCTL, int IBDR, int FBRD, uint32_t LCRH,
                     uint32_t CC, uint32_t CTL)
{

    SYSCTL_RCGCUART_R |= RCGcUART;         // Ativa o Clock na uart0
    setarBit(AFSEL, 0, 1);                 //Ativa função alternativa PA-0
    setarBit(AFSEL, 1, 1);                 //Ativa função alternativa PA-1
    GPIO_PORTA_PCTL_R |= 0x11;

    UART0_CTL_R = 0x00;                    // desativa UART p/ Configurar
    UART0_IBRD_R = 8;   // IBRD = int(16.000.000 / (16 * 115.200)) = int(8,6805)
    UART0_FBRD_R = FBRD;                   // FBRD = int(0,6805 * 64 + 0.5) = 44
    UART0_LCRH_R = LCRH;                   // Quantidade de bits, paridade
    UART0_CC_R = CC;
    UART0_CTL_R = CTL;                              // enable UART
    GPIO_PORTA_DEN_R |= 0x03;
}

void escreverUART0(unsigned char data)
{
    while ((UART0_FR_R & UART_FR_TXFF) != 0)
    {
    }
    UART0_DR_R = data;
}
