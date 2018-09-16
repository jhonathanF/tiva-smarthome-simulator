#ifndef BIBLIOTECAS_EEPROM_H_
#define BIBLIOTECAS_EEPROM_H_
#include <tm4c123gh6pm.h>
#include <inttypes.h>

#define EEPROM_INIT_OK 0
#define EEPROM_INIT_ERROR 2

int startEeprom();
uint32_t EEPROM_read(uint8_t block, uint8_t offset);
void EEPROM_write(uint8_t block, uint8_t offset, uint32_t word);

#endif /* BIBLIOTECAS_UTILITARIOTIVA_H_ */
