/*
 * eeprom.c
 *
 *  Created on: 7 de set de 2018
 *      Author: jhonathan
 */
#include "eeprom.h"

int startEeprom()
{
    SYSCTL_RCGCEEPROM_R = 0x01; //Ligar o clock da EEprom
    int aux;
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
    if(((EEPROM_EESUPP_R & 0x08) == 0x08) || ((EEPROM_EESUPP_R & 0x04) == 0x04))
    {
        return(EEPROM_INIT_ERROR);
    }

    return EEPROM_INIT_OK;

}

uint32_t EEPROM_read(uint8_t block, uint8_t offset){
    while(((EEPROM_EEDONE_R&0x20)==0x20) || ((EEPROM_EEDONE_R&0x08)==0x08) || ((EEPROM_EEDONE_R&0x04)==0x04)){}
    while (EEPROM_EEDONE_R != 0){}
    EEPROM_EEBLOCK_R = (uint8_t)(1<<block);
    EEPROM_EEOFFSET_R = (uint8_t)offset;
    return (uint32_t)EEPROM_EERDWR_R;
}

void EEPROM_write(uint8_t block, uint8_t offset, uint32_t word) {
    while(((EEPROM_EEDONE_R&0x20)==0x20) || ((EEPROM_EEDONE_R&0x08)==0x08) || ((EEPROM_EEDONE_R&0x04)==0x04)){}
    while (EEPROM_EEDONE_R != 0){}
    EEPROM_EEBLOCK_R =  (uint8_t)(1<<block);
    EEPROM_EEOFFSET_R = (uint8_t)offset;
    EEPROM_EERDWR_R = (uint32_t)word;
}

