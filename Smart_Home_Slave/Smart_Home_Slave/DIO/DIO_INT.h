/*
 * DIO_INT.h
 *
 * Created: 08-Sep-23 11:20:42 AM
 *  Author: lenovo
 */ 

#ifndef DIO_INT_H_
#define DIO_INT_H_
#include "DIO_PRV.h"
#include "DIO_CFG.h"

#include "../STD_TYPES.h"
#include "../BIT_MATH.h"

#define LOW			0
#define HIGH		1

typedef enum {
Pin_A0  ,Pin_A1	,Pin_A2	,Pin_A3	,Pin_A4	,Pin_A5	, Pin_A6 ,Pin_A7 ,
Pin_B0	,Pin_B1 ,Pin_B2 ,Pin_B3	,Pin_B4 ,Pin_B5	, Pin_B6 ,Pin_B7 ,
Pin_C0	,Pin_C1	,Pin_C2	,Pin_C3	,Pin_C4	,Pin_C5	, Pin_C6 ,Pin_C7 ,
Pin_D0	,Pin_D1	,Pin_D2	,Pin_D3	,Pin_D4	,Pin_D5	, Pin_D6 ,Pin_D7 ,
}Pin_Type;
typedef enum {
	OutPut_Low,
	OutPut_High,
	Input_Float,
	InPut_PullUp
}PinMode_type;


void DIO_Init(void);
void Dio_SetPinMode(Pin_Type Pin,PinMode_type mode);
void DIO_WritePinVal(Pin_Type Pin, uint8 val);
void DIO_ReadPinVal(Pin_Type Pin,uint8 *BufferPtr);
void DIO_ReadportVal(Pin_Type Pin,uint8 *BufferPtr);



#endif /* DIO_INT_H_ */