/*
 * LCD.c
 *
 * Created: 10-Sep-23 10:23:06 AM
 *  Author: lenovo
 */ 
#include "LCD_int.h"

 uint8 Character0[] = { 0x00, 0x0A, 0x15, 0x11, 0x0A, 0x04, 0x00, 0x00 };
 uint8 Character1[] = { 0x04, 0x1F, 0x11, 0x11, 0x1F, 0x1F, 0x1F, 0x1F };
 uint8 Character2[] = { 0x04, 0x0E, 0x0E, 0x0E, 0x1F, 0x00, 0x04, 0x00 };
 uint8 Character3[] = { 0x01, 0x03, 0x07, 0x1F, 0x1F, 0x07, 0x03, 0x01 };
 uint8 Character4[] = { 0x01, 0x03, 0x05, 0x09, 0x09, 0x0B, 0x1B, 0x18 };
 uint8 Character5[] = { 0x0A, 0x0A, 0x1F, 0x11, 0x11, 0x0E, 0x04, 0x04 };
 uint8 Character6[] = { 0x00, 0x00, 0x0A, 0x00, 0x04, 0x11, 0x0E, 0x00 };
 uint8 Character7[] = { 0x00, 0x0A, 0x1F, 0x1F, 0x0E, 0x04, 0x00, 0x00 };
	
void LCD_init()
{	
/*
	Dio_SetPinMode(LCD_D0,OutPut_Low);
	Dio_SetPinMode(LCD_D1,OutPut_Low);
	Dio_SetPinMode(LCD_D2,OutPut_Low);
	Dio_SetPinMode(LCD_D3,OutPut_Low);
	Dio_SetPinMode(LCD_EN,OutPut_Low);
	Dio_SetPinMode(LCD_RS,OutPut_Low);*/
	_delay_ms(35);
	DIO_WritePinVal(LCD_RS,LOW);
	Write_Half_Port(0b0010);
	DIO_WritePinVal(LCD_EN,HIGH);
	_delay_ms(1);
	DIO_WritePinVal(LCD_EN,LOW);
	LCD_send_command(0b00101000);
	_delay_us(45);
	LCD_send_command(0b00001111);
	_delay_us(45);
	LCD_send_command(0b00000001);
	_delay_ms(2);
	LCD_send_command(0b00000110);
	
	
}
void LCD_send_command(uint8 command)
{
	DIO_WritePinVal(LCD_RS,LOW);
	Write_Half_Port(command>>4);
	DIO_WritePinVal(LCD_EN,HIGH);
	_delay_ms(1);
	DIO_WritePinVal(LCD_EN,LOW);
	Write_Half_Port(command);
	DIO_WritePinVal(LCD_EN,HIGH);
	_delay_ms(1);
	DIO_WritePinVal(LCD_EN,LOW);
}
void LCD_write_data(uint8 data)
{
	DIO_WritePinVal(LCD_RS,HIGH);
	Write_Half_Port(data>>4);
	DIO_WritePinVal(LCD_EN,HIGH);
	_delay_ms(1);
	DIO_WritePinVal(LCD_EN,LOW);
	//_delay_ms(1);
	Write_Half_Port(data);
	DIO_WritePinVal(LCD_EN,HIGH);
	_delay_ms(1);
	DIO_WritePinVal(LCD_EN,LOW);
	
}
static void Write_Half_Port(uint8 Value)
{
	DIO_WritePinVal(LCD_D4,READBIT(Value,0));
	DIO_WritePinVal(LCD_D5,READBIT(Value,1));
	DIO_WritePinVal(LCD_D6,READBIT(Value,2));
	DIO_WritePinVal(LCD_D7,READBIT(Value,3));
}
void LCD_write_string(uint8 *data)
{
	int i=0;
	while(data[i] != '\0'){
		LCD_write_data(data[i]);
		i++;
	}
	
}
void LCD_Clear(void)
{
	LCD_send_command(0x01);
	LCD_send_command(0x80);
}
void LCD_Shift_Left(void)
{
	LCD_send_command(0x18);
}
void LCD_Shift_Right(void)
{
	LCD_send_command(0x1C);
}
void LCD_Pattern(uint8 loc)
{
	uint8 i;

	switch(loc)
	{
		case 0:
			LCD_send_command(0x40 + (loc*8));	
			for(i=0;i<8;i++)
			LCD_write_data(Character0[i]);
		break;
		case 1:
			LCD_send_command(0x40 + (loc*8));
			for(i=0;i<8;i++)
			LCD_write_data(Character1[i]);
		break;
		
		case 2:
			LCD_send_command(0x40 + (loc*8));
			for(i=0;i<8;i++)
			LCD_write_data(Character2[i]);
		break;
		
		case 3:
		LCD_send_command(0x40 + (loc*8));
		for(i=0;i<8;i++)
		LCD_write_data(Character3[i]);
		break;
		
		case 4:
			LCD_send_command(0x40 + (loc*8));
			for(i=0;i<8;i++)
				LCD_write_data(Character4[i]);
		break;
		
		case 5:
		LCD_send_command(0x40 + (loc*8));
		for(i=0;i<8;i++)
		LCD_write_data(Character5[i]);
		break;
		
		case 6:
		LCD_send_command(0x40 + (loc*8));
		for(i=0;i<8;i++)
		LCD_write_data(Character6[i]);
		break;
		
		case 7:
		LCD_send_command(0x40 + (loc*8));
		for(i=0;i<8;i++)
		LCD_write_data(Character7[i]);
		break;
	}	
	 }
	 
void LCD_Position (char row, char pos)
{
	switch (row)
	{
		case 1:
		if (pos <16)
		{
			LCD_send_command((pos & 0x0F)|0x80);
		}
		break;
		case 2:
		if (pos <16)
		{
			LCD_send_command((pos & 0x0F)|0xC0);
		}
		break;
		case 3:
		if (pos <16)
		{
			LCD_send_command((0x80|0x14)+pos);
		}
		break;
		case 4:
		if (pos <16)
		{
			LCD_send_command((0x80|0x54)+pos);
		}
		break;
	}
	
}

void LCD_write_num_float(float32 float_num)
{
	uint32 int_num = float_num;
	float32 minus=0;
	LCD_write_num(int_num);
	minus = (float_num - int_num)*1000;
	LCD_write_string(".");
	LCD_write_num(minus);
	
}

void LCD_write_num(uint32 num)
{
	uint8 data ;
	if (num >= 10){
		if (num>=100){
			if(num >= 1000){//%0.2f 4.50 0.5  4.5000
				data = (num/1000)%10;//3555->3
				LCD_write_data(data + 0x30);
			}
			data = (num/100)%10;
			LCD_write_data(data + 0x30);
		}
		data = (num/10)%10;//50
		LCD_write_data(data + 0x30);
	}
	data = num %10;//5
	LCD_write_data(data+0x30);
	
}