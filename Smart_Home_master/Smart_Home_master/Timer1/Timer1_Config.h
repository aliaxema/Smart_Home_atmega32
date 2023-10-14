/*
 * Timer_Config.h
 *
 * Created: 17-Sep-23 11:25:29 AM
 *  Author: lenovo
 */ 


#ifndef TIMER_CONFIG_H_
#define TIMER_CONFIG_H_

/* options for timer mode 
	1-TIMER1_NORMAL_MODE
	2-TIMER1_CTC_MODE
*/



#define TMR1_PRELOAD_VAL	113
#define TIMER1_OVF_COUNTER	977
#define TIMER1_CTC_COUNTER	4999

#define TIMER1_MODE				TIMER1_NORMAL_MODE

#define TIMER1_PWM_MODE			TIMER1_NON_INVERTING_PWM_MODE


#define TMR1_PRESCALER_MODE		PRESCALER_64

#endif /* TIMER_CONFIG_H_ */