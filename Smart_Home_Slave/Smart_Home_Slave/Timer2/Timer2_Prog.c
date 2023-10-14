/*
 * Timer2_Prog.c
 *
 * Created: 26-Sep-23 1:47:18 PM
 *  Author: lenovo
 */ 
#include "Timer2_Inter.h"

static void (*private_ptr_CallBack_OVF2)(void) = NULL;

static void (*private_ptr_CallBack_CTC2)(void) = NULL;

uint16 private_CTC_counter2=0;

void Timer2_Init(void)
{
	#if (TIMER2_MODE == TIMER2_NORMAL_MODE)
	CLRBIT(TCCR2,WGM20);
	CLRBIT(TCCR2,WGM21);
	TCNT2 = TMR2_PRELOAD_VAL;
	SETBIT(TIMSK,TOIE2);
	#elif (TIMER2_MODE == TIMER2_CTC_MODE)
	CLRBIT(TCCR2,WGM20);
	SETBIT(TCCR2,WGM21);
	SETBIT(TIMSK,OCIE2);
	#elif (TIMER2_MODE == TIMER2_FAST_PWM_MODE)
	SETBIT(TCCR2,WGM20);
	SETBIT(TCCR2,WGM21);
	CLRBIT(TCCR2,FOC2);
		#if (TIMER2_PWM_MODE == TIMER2_NON_INVERTING_PWM_MODE)
		CLRBIT(TCCR2,COM20);
		SETBIT(TCCR2,COM21);
		#elif (TIMER2_PWM_MODE == TIMER2_INVERTING_PWM_MODE)
		SETBIT(TCCR2,COM20);
		SETBIT(TCCR2,COM21);
		#endif
	#endif
}
void Timer2_Start(void)
{
	SETBIT(TCCR2,CS20);
	SETBIT(TCCR2,CS21);
	CLRBIT(TCCR2,CS22);
}
void Timer2_Stop(void)
{
	CLRBIT(TCCR2,CS20);
	CLRBIT(TCCR2,CS21);
	CLRBIT(TCCR2,CS22);
}
void Timer2_SetCallBack(void(*ptr_to_Func)(void))
{
		if(ptr_to_Func != NULL)
		private_ptr_CallBack_OVF2 = ptr_to_Func ;
}
void Timer2_Set_Comp_Match(uint8 copy_u9_compare_val)
{
	OCR2 = copy_u9_compare_val;
}
void Timer2_Set_delay_ms_CTC(uint16 delay_ms)
{
		//Restriction under condition tick time is 4 usec
		OCR2 = 249;
		//the real equation id --> (delay_ms*1000)/(OCR2+1)*4us(or it could be changed))
		private_CTC_counter2 = delay_ms;
}
void Timer2_PWM_Set_Duty(uint8 Duty)
{
	#if (TIMER2_PWM_MODE == TIMER2_NON_INVERTING_PWM_MODE)
	if (Duty <=100)
	{
		OCR2 = (((uint16)Duty * 256)/100 ) - 1;
	}
	#elif (TIMER2_PWM_MODE == TIMER2_INVERTING_PWM_MODE)
	if (Duty <=100){
	OCR2 = 100 - ((((uint16)Duty * 256)/100 ) - 1);}
	#endif
}

void __vector_5(void) __attribute__ ((signal));
void __vector_5(void)
{
	static uint16 counter = 0;
	counter++;
	if (counter == TIMER2_OVF_COUNTER)
	{
		counter = 0;
		TCNT2 = TMR2_PRELOAD_VAL;
		
		//Call Action
		if(private_ptr_CallBack_OVF2 != NULL)
		{
			private_ptr_CallBack_OVF2();
		}
		
	}
}

void __vector_4(void) __attribute__ ((signal));
void __vector_4(void)
{
	static uint16 counter = 0;
	counter++;
	if (counter == private_CTC_counter2)
	{
		counter = 0;
		
		//Call Action
		if(private_ptr_CallBack_CTC2 != NULL)
		{
			private_ptr_CallBack_CTC2();
		}
		
	}
}