/*
 * Smart_home.c
 *
 * Created: 02-Oct-23 3:08:48 PM
 *  Author: lenovo
 */ 

#include "Smart_Home.h"

uint16 pass = 1234;
static uint8 trials = 3;
uint8 Enter_pass[4];
uint8 flag =0;

uint8 mode_flag=0, menu_flag =0,User_mode = 0;
extern volatile u8 temp_val =0;

uint8 Return_Key_value()
{
	uint8 KeyPad_key = KEYPAD_read();
	while(KeyPad_key == 0)
	{
		KeyPad_key = KEYPAD_read();
	}
	if(KeyPad_key != '=')
	LCD_write_data(KeyPad_key);
	while(KEYPAD_read()==KeyPad_key);
	return KeyPad_key;
}

uint16 convert_To_Int(uint8 *str)
{
	uint16 num=0;
	uint8 i=0;
	while(str[i] != '\0')
	{
		num = (num * 10) + (str[i] - 48);
		i++ ;
	}
	return num;
}


void Automated_Door_Lock(void)
{

	uint8 i=0;
	uint16 num=0;
	Enter_pass[i] = Return_Key_value();
	i++;
	while(1)
	{
		Enter_pass[i] = Return_Key_value();

		if(Enter_pass[i] == '=')
		{
			Enter_pass[i]='\0';
			break;
		}
		if (i==4)
		{
			LCD_Clear();
			LCD_write_string("Enter the password:");
			LCD_Position(2,0);
			i=0;
		}
		i++;
	}
	num = convert_To_Int(Enter_pass);
	if(num == pass)
	{
		LCD_Clear();
		LCD_write_string("Correct Pass");
		LCD_Position(2,5);
		LCD_write_string("Door Opened");
		SRVM_voidOn(180);
		_delay_ms(1000);
		LCD_Clear();
		LCD_write_string("Enter the password:");
		LCD_Position(2,0);
		flag =0;
		trials=3;
	}
	else
	{
		SRVM_voidOn(90);
		LCD_Clear();
		LCD_write_string("Incorrect Password");
		LCD_Position(2,4);
		LCD_write_string("Try again...");
		LCD_Position(3,0);
		LCD_write_string("Trials left:");
		LCD_write_num(--trials);
		_delay_ms(1000);
		LCD_Clear();
		LCD_write_string("Enter the password:");
		LCD_Position(2,0);
		flag ++;
	}
	if (flag == 3)
	{
		Dio_SetPinMode(Pin_A0,OutPut_High);
		DIO_WritePinVal(Pin_A1,HIGH);
		LCD_Clear();
		LCD_write_string("Incorrect!!");
		LCD_Position(2,5);
		LCD_write_string("Buzzer ON");
	}
}

void LCD_First_Write_Pass(void)
{
	LCD_write_string("Enter the password:");
	LCD_Position(2,0);
}



void Control_Led (u8 Duty_Cycle)
{
	TIMER0_voidSetDutyCycleFastPWM(Duty_Cycle);
}


u8 Read_Temperature(void) {

	uint16 ADC_Value = ADC_ReadSingleChannel(ADC1);
	//ADC_ReadScanGroup(ScanGroup1, &ADC_Value); // Read from ADC channel 0

	// Calculate temperature value in degrees Celsius
	u16 mV_Value = (ADC_Value * 5000UL) / 1023UL;
	u8 temperature_value = mV_Value / 10;


	return temperature_value  ;
}

void check_temp(void)
{
		temp_val = Read_Temperature();
		if(temp_val > 28)
		{
			DIO_WritePinVal(Pin_A4,HIGH);
		}
		else
		{
			DIO_WritePinVal(Pin_A4,LOW);
		}

}
void convert_To_String(uint8 str[], uint32 num)
{
	sint32 len=0, temp1, i, rem;
	
	temp1 = num;
	
	while(temp1 != 0)                 //finding length of the number
	{
		len++;
		temp1 /= 10;
	}

	for(i=0; i<len; i++)             //converting numbers to equivalent char
	{
		rem = num % 10;
		num = num / 10;
		str[len - (i+1)] = rem + '0';
	}
	str[len] = '\0';
}
