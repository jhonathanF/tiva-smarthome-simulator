/*
 * eeprom.c
 *
 *  Created on: 7 de set de 2018
 *      Author: jhonathan
 */
#include "eeprom.h"

void startEeprom()
{
    SYSCTL_RCGCEEPROM_R = 0x01; //Ligar o clock da EEprom
    for (aux = 0; aux < 2; aux++){} //Simular um delay de 6 ciclos
    while ((EEPROM_EEDONE_R & 0x01) == 0x01){} //Verificar se a eeprom terminou o trabalho

    if (((EEPROM_EESUPP_R & 0x08) == 0x08)
            || ((EEPROM_EESUPP_R & 0x04) == 0x04))//Caso tenha dado algum erro;
    {
        return (EEPROM_INIT_ERROR);
    }

    SYSCTL_SREEPROM_R = 0x01;
    SYSCTL_SREEPROM_R = 0x00;
    for (aux = 0; aux < 2; aux++){}
    while ((EEPROM_EEDONE_R & 0x01) == 0x01){}
    if((EEPROM_EESUPP_R & 0x08) == 0x08) || ((EEPROM_EESUPP_R & 0x04) == 0x04))
    {
        return(EEPROM_INIT_ERROR);
    }

    return (EEPROM_INIT_OK);

}

