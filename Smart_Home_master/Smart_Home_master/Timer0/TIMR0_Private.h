/*
 * TIMR0_Private.h
 *
 *  Created on: Sep 17, 2023
 *      Author: alaae
 */

#ifndef TIMR0_PRIVATE_H_
#define TIMR0_PRIVATE_H_


#define TCCR0	                      (*(volatile u8 * )0x53)
#define TCNT0	                      (*(volatile u8 * )0x52)
#define TIMSK	                      (*(volatile u8 * )0x59)
#define OCR0 	                      (*(volatile u8 * )0x5C)
#define TIFR	                      (*(volatile u8 * )0x58)

//TCCR0 register bits
#define CS00                    0
#define CS01                    1
#define CS02                    2
#define WGM01                   3
#define COM00                   4
#define COM01                   5
#define WGM00                   6
#define FOC0                    7

//TIMSK register bits
#define TOIE0                   0
#define OCIE0                   1

//TIFR register bits
#define TOV0                     0
#define OCF0                     1


#define TIMER0_NORMAL 		          1
#define TIMER0_CTC 			          2
#define TIMER0_FAST_PWM 	          3
#define TIMER0_PHASE_PWM 	          4


#define NON_INVERTING_MODE            1
#define INVERTING_MODE                2

#define TIMER0_DIV_BY_1			      1
#define TIMER0_DIV_BY_8			      5
#define TIMER0_DIV_BY_64		      8
#define TIMER0_DIV_BY_256		      10
#define TIMER0_DIV_BY_1024		      15


#define TIMER0_NO_ACTION	           100
#define TIMER0_TOGGLE		           12
#define TIMER0_SET			           20
#define TIMER0_CLEAR		           25



#endif /* TIMR0_PRIVATE_H_ */
