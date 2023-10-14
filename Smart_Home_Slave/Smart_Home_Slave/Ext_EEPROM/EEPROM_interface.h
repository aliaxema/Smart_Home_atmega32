

#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

#include "../STD_TYPES.h"

#define EEPROM_FIXED_ADDRESS          0x50

void EEPROM_voidInit     (void);
void EEPROM_voidWriteByte(u16 Copy_u16WordAddress, u8 Copy_u8Data);
void EEPROM_voidReadByte (u16 Copy_u16WordAddress, u8* Copy_pu8RxData);
void EEPROM_voidWritePage(u16 Copy_u16WordAddress, u8* data_arr, u8 arr_size);
void EEPROM_voidReadPage(u16 Copy_u16WordAddress, u8* data_arr, u8 arr_size);

	 
	 
#endif /* EEPROM_INTERFACE_H_ */