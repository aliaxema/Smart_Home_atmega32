/*
 * KeyPad.c
 *
 * Created: 09-Sep-23 12:09:27 PM
 *  Author: lenovo
 */ 
#include "KeyPad_interface.h"


const uint8 keypad_matrix[] =
{	'+', '-', '*', '/',
	'=', '3', '6', '9',
	'0', '2', '5', '8',
	'c', '1', '4', '7'
};

void KEYPAD_init(void)
{
	Dio_SetPinMode(PD7,InPut_PullUp);
	Dio_SetPinMode(PD6,InPut_PullUp);
	Dio_SetPinMode(PD5,InPut_PullUp);
	Dio_SetPinMode(PD3,InPut_PullUp);
	Dio_SetPinMode(PC5,OutPut_Low);
	Dio_SetPinMode(PC4,OutPut_Low);
	Dio_SetPinMode(PC3,OutPut_Low);
	Dio_SetPinMode(PC2,OutPut_Low);
	

}
uint8 KEYPAD_read(void)
{
	KEY4(0); KEY5(1); KEY6(1); KEY7(1);
	if(KEY0 == 0) return keypad_matrix[0];
	if(KEY1 == 0) return keypad_matrix[4];
	if(KEY2 == 0) return keypad_matrix[8];
	if(KEY3 == 0) return keypad_matrix[12];
	_delay_ms(1);
	
	KEY4(1); KEY5(0); KEY6(1); KEY7(1);
	if(KEY0 == 0) return keypad_matrix[1];
	if(KEY1 == 0) return keypad_matrix[5];
	if(KEY2 == 0) return keypad_matrix[9];
	if(KEY3 == 0) return keypad_matrix[13];
	_delay_ms(1);
	
	KEY4(1); KEY5(1); KEY6(0); KEY7(1);
	if(KEY0 == 0) return keypad_matrix[2];
	if(KEY1 == 0) return keypad_matrix[6];
	if(KEY2 == 0) return keypad_matrix[10];
	if(KEY3 == 0) return keypad_matrix[14];
	_delay_ms(1);
	
	KEY4(1); KEY5(1); KEY6(1); KEY7(0);
	if(KEY0 == 0) return keypad_matrix[3];
	if(KEY1 == 0) return keypad_matrix[7];
	if(KEY2 == 0) return keypad_matrix[11];
	if(KEY3 == 0) return keypad_matrix[15];
	_delay_ms(1);
	
	
	return 0;
}

