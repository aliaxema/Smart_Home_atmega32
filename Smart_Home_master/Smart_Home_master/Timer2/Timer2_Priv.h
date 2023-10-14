/*
 * Timer2_Priv.h
 *
 * Created: 26-Sep-23 1:47:31 PM
 *  Author: lenovo
 */ 


#ifndef TIMER2_PRIV_H_
#define TIMER2_PRIV_H_

/* Timer 2 */
#define OCR2    (*(volatile uint8*)(0x43))
#define TCNT2   (*(volatile uint8*)(0x44))
#define TCCR2   (*(volatile uint8*)(0x45))
#define ASSR    (*(volatile uint8*)(0x42))

/* bits 7-4 reserved */
#define AS2     3
#define TCN2UB  2
#define OCR2UB  1
#define TCR2UB  0

/* TCCR2 */
#define FOC2    7
#define WGM20   6
#define COM21   5
#define COM20   4
#define WGM21   3
#define CS22    2
#define CS21    1
#define CS20    0

#define  TIMSK (*( (volatile uint8 *) 0x59))

#define OCIE2   7
#define TOIE2   6
#define TICIE1  5
#define OCIE1A  4
#define OCIE1B  3
#define TOIE1   2
#define OCIE0   1
#define TOIE0   0

#define TIFR              (*(volatile u8*)0x58)

/* TIFR */
#define OCF2    7
#define TOV2    6
#define ICF1    5
#define OCF1A   4
#define OCF1B   3
#define TOV1    2
#define OCF0    1
#define TOV0    0

#define SFIOR  (*(volatile u8*)0x50)

/* SFIOR */
#define ADTS2   7
#define ADTS1   6
#define ADTS0   5
/* bit 4 reserved */
#define ACME    3
#define PUD     2
#define PSR2    1
#define PSR10   0

#define NULL ((void*)0)


#define TIMER2_NORMAL_MODE				1
#define TIMER2_CTC_MODE					2
#define TIMER2_FAST_PWM_MODE			3

#define TIMER2_NON_INVERTING_PWM_MODE	1
#define TIMER2_INVERTING_PWM_MODE		2

#endif /* TIMER2_PRIV_H_ */