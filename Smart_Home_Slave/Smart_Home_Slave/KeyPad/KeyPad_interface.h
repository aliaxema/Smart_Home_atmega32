/*
 * KeyPad_interface.h
 *
 * Created: 09-Sep-23 12:18:26 PM
 *  Author: lenovo
 */ 


#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_
#include "KeyPad_config.h"
#include "../LCD/LCD_int.h"

void KEYPAD_init(void);
uint8 KEYPAD_read(void);



#endif /* KEYPAD_INTERFACE_H_ */