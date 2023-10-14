/*
 * Timer_Priv.h
 *
 * Created: 17-Sep-23 11:25:51 AM
 *  Author: lenovo
 */ 


#ifndef TIMER_PRIV_H_
#define TIMER_PRIV_H_

                       /* TIMER1 REGISTERS*/

                       // Timer/Counter1 Control Register A
#define TCCR1A             (*(volatile uint8*)0x4F)
#define WGM10              0
#define WGM11              1
#define FOC1B              2
#define FOC1A              3
#define COM1B0             4
#define COM1B1             5
#define COM1A0             6
#define COM1A1             7

// Timer/Counter1 Control Register B
#define TCCR1B             (*(volatile uint8*)0x4E)
#define CS10               0
#define CS11               1
#define CS12               2
#define WGM12              3
#define WGM13              4
#define ICES1              6
#define ICNC1              7

// Timer/Counter1
#define TCNT1          (*(volatile uint16*)0x4C)

// Output Compare Register 1 A
#define OCR1A		         (*(volatile uint16*)0x4A)

// Output Compare Register 1 B
#define OCR1B          (*(volatile uint16*)0x48)

// Input Capture Register 1
#define ICR1          (*(volatile uint16*)0x46)

// Timer/Counter Interrupt Mask Register
#define TIMSK              (*(volatile uint8*)0x59)
#define TOIE1              2
#define OCIE1B             3
#define OCIE1A             4
#define TICIE1             5

// Timer/Counter Interrupt Flag Register
#define TIFR              (*(volatile uint8*)0x58)

#define NULL ((void*)0)



#define TIMER1_NORMAL_MODE				1
#define TIMER1_CTC_MODE					2
#define TIMER1_FAST_PWM_MODE_A			3

#define TIMER1_NON_INVERTING_PWM_MODE	1
#define TIMER1_INVERTING_PWM_MODE		2


#define PRESCALER_0		1
#define PRESCALER_8		2
#define PRESCALER_64	3
#define PRESCALER_256	4
#define PRESCALER_1024	5

#endif /* TIMER_PRIV_H_ */