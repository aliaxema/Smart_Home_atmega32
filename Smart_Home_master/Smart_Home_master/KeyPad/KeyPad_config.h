/*
 * KeyPad.h
 *
 * Created: 09-Sep-23 12:09:42 PM
 *  Author: lenovo
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "../STD_TYPES.h"
#include "../BIT_MATH.h"
#include "../DIO/DIO_INT.h"



#define KEY0 READBIT(PIND,3)
#define KEY1 READBIT(PIND,4)
#define KEY2 READBIT(PIND,6)
#define KEY3 READBIT(PIND,7)
#define KEY4(x) if (x==1) SETBIT(PORTC,2);else CLRBIT(PORTC,2);
#define KEY5(x) if (x==1) SETBIT(PORTC,3);else CLRBIT(PORTC,3);
#define KEY6(x) if (x==1) SETBIT(PORTC,4);else CLRBIT(PORTC,4);
#define KEY7(x) if (x==1) SETBIT(PORTC,5);else CLRBIT(PORTC,5);




#endif /* KEYPAD_H_ */