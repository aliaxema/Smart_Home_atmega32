/*
 * SRVM_Program.c
 *
 *  Created on: Sep 21, 2023
 *      Author: alaae
 */


#include "../STD_TYPES.h"
#include "../BIT_MATH.h"

/* MCAL */
#include "SRVM_Interface.h"
#include "SRVM_Private.h"


void SRVM_voidOn(u8 Copy_u8Angle)
{
	/* TMR1 init at pwm mode 14 */
	 CLEAR_BIT(TCCR1A,WGM10);
	  SET_BIT(TCCR1A,WGM11);
	  SET_BIT(TCCR1B,WGM12);
	  SET_BIT(TCCR1B,WGM13);

	// Select Non Inverting Mode
     CLEAR_BIT(TCCR1A,COM1A0);
     SET_BIT(TCCR1A,COM1A1);


	/* Set pwm fre. = 50 */
	ICR1_u16 = 4999;

	/* Set pwm duty cycle between 5 : 10
	 depend on desired angle[0 : 180]
	 Angle 0   -> position -90
	 Angle 90  -> position 0
	 Angle 280 -> position 90 */
    f32 dutyCycle = ((f32)Copy_u8Angle * 5) / 180 + 5;
    OCR1A_u16 = ((f32)((dutyCycle * ICR1_u16) / 100));

	/* TMR1 start */
	// SET PRESCALER  64
    SET_BIT(TCCR1B,CS10);
    SET_BIT(TCCR1B,CS11);
    CLEAR_BIT(TCCR1B,CS12);

}


void SRVM_voidOff(void)
{
	/* TMR1 stop */
	 CLEAR_BIT(TCCR1B,CS10);
     CLEAR_BIT(TCCR1B,CS11);
     CLEAR_BIT(TCCR1B,CS12);
}
