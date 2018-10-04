#include "utilitarioTiva.h"

uint32_t microsAtual = 0;
uint32_t millisAtual = 0;

void configurarSysTick(uint32_t reload, uint32_t ctrl)
{
    NVIC_ST_RELOAD_R = reload; //Pode dividir
    NVIC_ST_CTRL_R = ctrl;
}

void trataST()
{
    millisAtual++;

}

void delay(uint32_t millis)
{
    uint32_t start = getMillis();

    while ((getMillis() - start) <= millis)
    {

    }
}

uint32_t getMillis()
{
    return millisAtual;
}

uint32_t getMicro()
{
    return microsAtual;
}

void itoa(uint32_t value, char* result, int base)
{
// check that the base if valid
    if (base < 2 || base > 36)
    {
        *result = '\0';
    }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do
    {
        tmp_value = value;
        value /= base;
        *ptr++ =
                "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35
                        + (tmp_value - value * base)];
    }
    while (value);

// Apply negative sign
    if (tmp_value < 0)
        *ptr++ = '-';
    *ptr-- = '\0';
    while (ptr1 < ptr)
    {
        tmp_char = *ptr;
        *ptr-- = *ptr1;
        *ptr1++ = tmp_char;
    }
}
