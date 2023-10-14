/*
 * DIO_PROG.c
 *
 * Created: 08-Sep-23 11:21:39 AM
 *  Author: lenovo
 */ 

#include "DIO_INT.h"

uint8 *const ArrPORT[4]={&PORTA,&PORTB,&PORTC,&PORTD};
uint8 *const ArrDDR[4]= {&DDRA,&DDRB,&DDRC,&DDRD};
uint8 *const ArrPIN[4]= {&PINA,&PINB,&PINC,&PIND};

uint8 Dio_PinInitArray[]={     
 Dio_PinA0_init, Dio_PinA1_init, Dio_PinA2_init, Dio_PinA3_init,
 Dio_PinA4_init, Dio_PinA5_init, Dio_PinA6_init, Dio_PinA7_init,
 Dio_PinB0_init, Dio_PinB1_init, Dio_PinB2_init, Dio_PinB3_init,
 Dio_PinB4_init, Dio_PinB5_init, Dio_PinB6_init, Dio_PinB7_init,
 Dio_PinC0_init, Dio_PinC1_init, Dio_PinC2_init, Dio_PinC3_init,
 Dio_PinC4_init, Dio_PinC5_init, Dio_PinC6_init, Dio_PinC7_init,
 Dio_PinD0_init, Dio_PinD1_init, Dio_PinD2_init, Dio_PinD3_init,
 Dio_PinD4_init, Dio_PinD5_init, Dio_PinD6_init, Dio_PinD7_init 
 };	

void DIO_Init(void)
{	
	for(uint8 PinCount=Pin_A0;PinCount<=Pin_D7;PinCount++){
	
		  Dio_SetPinMode(PinCount,Dio_PinInitArray[PinCount]);
	}
	
}

void Dio_SetPinMode(Pin_Type Pin,PinMode_type mode)
{
	Pin_Type PORT,Pin_Val;
	PORT = Pin/8;
	Pin_Val = Pin%8;
	switch(mode)
	{
		case InPut_PullUp:
		CLRBIT(*ArrDDR[PORT],Pin_Val);
		SETBIT(*ArrPORT[PORT],Pin_Val);
		break;
		case Input_Float:
		CLRBIT(*ArrDDR[PORT],Pin_Val);
		break;
		case OutPut_High:
		SETBIT(*ArrDDR[PORT],Pin_Val);
		SETBIT(*ArrPORT[PORT],Pin_Val);
		break;
		case OutPut_Low:
		SETBIT(*ArrDDR[PORT],Pin_Val);
		CLRBIT(*ArrPORT[PORT],Pin_Val);
		break;
	}
	
}



void DIO_WritePinVal(Pin_Type Pin, uint8 val)
{
	Pin_Type PORT,Pin_Val;
	PORT = Pin/8;
	Pin_Val = Pin %8;
	if(val == HIGH)
	{
		SETBIT(*ArrPORT[PORT],Pin_Val);
	}
	else if (val == LOW)
	{
		CLRBIT(*ArrPORT[PORT],Pin_Val);
	}
	
}


void DIO_ReadPinVal(Pin_Type Pin,uint8 *BufferPtr)
{	
	Pin_Type Port,Pin_value;
	Port = Pin/8;
	Pin_value = Pin%8;
	*BufferPtr = READBIT(*ArrPIN[Port],Pin_value);
	
}
void DIO_ReadportVal(Pin_Type Pin,uint8 *BufferPtr)
{
	Pin_Type Port,Pin_value;
	Port = Pin/8;
	Pin_value = Pin%8;
	*BufferPtr = *ArrPORT[Port];
}