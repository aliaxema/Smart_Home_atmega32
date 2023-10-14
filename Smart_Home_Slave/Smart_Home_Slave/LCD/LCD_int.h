/*
 * LCD.h
 *
 * Created: 10-Sep-23 10:22:11 AM
 *  Author: lenovo
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "../STD_TYPES.h"
#include "../BIT_MATH.h"

#include "../DIO/DIO_INT.h"

#include "LCD_config.h"
#include "LCD_private.h"


void LCD_init();
void LCD_send_command(uint8 command);
void LCD_write_data(uint8 data);

void LCD_write_string(uint8 *data);
void LCD_Clear(void);
void LCD_Shift_Right(void);
void LCD_Shift_Left(void);
void LCD_Pattern(uint8 loc);
void LCD_Position (char row, char pos);
void LCD_write_num(uint32 num);
void LCD_write_num_float(float32 num);

#endif /* LCD_H_ */