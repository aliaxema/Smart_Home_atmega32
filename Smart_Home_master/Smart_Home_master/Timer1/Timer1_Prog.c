/*
 * Timer_Prog.c
 *
 * Created: 17-Sep-23 11:25:14 AM
 *  Author: lenovo
 */ 
#include "Timer1_Inter.h"

static void (*private_ptr_CallBack_OVF)(void) = NULL;

static void (*private_ptr_ICU)(void) = NULL;


uint16 private_CTC_A_counter=0;
void Timer1_Init(void)
{
	#if (TIMER1_MODE == TIMER1_NORMAL_MODE)
		
		CLRBIT(TCCR1B,WGM10);
		CLRBIT(TCCR1B,WGM11);
		TCNT1 = 0;
		SETBIT(TIMSK,TOIE1);
		
	#elif (TIMER1_MODE == TIMER1_CTC_MODE)
		

		
	#elif (TIMER1_MODE == TIMER1_FAST_PWM_MODE_A)
		CLRBIT(TCCR1A,WGM10);
		SETBIT(TCCR1A,WGM11);
		SETBIT(TCCR1B,WGM12);
		SETBIT(TCCR1B,WGM13);
		ICR1 = 4999;
		#if (TIMER1_PWM_MODE == TIMER1_NON_INVERTING_PWM_MODE)
			CLRBIT(TCCR1A,COM1A0);
			SETBIT(TCCR1A,COM1A1);
		#elif (TIMER1_PWM_MODE == TIMER1_INVERTING_PWM_MODE)
		
		
		#endif
	#endif
}
void Timer1_Start(void)

{	
	#if (TMR1_PRESCALER_MODE == PRESCALER_0)
		SETBIT(TCCR1B,CS10);
		CLRBIT(TCCR1B,CS11);// prescaler
		CLRBIT(TCCR1B,CS12);
	#elif (TMR1_PRESCALER_MODE == PRESCALER_8)
		CLRBIT(TCCR1B,CS10);
		SETBIT(TCCR1B,CS11);// prescaler
		CLRBIT(TCCR1B,CS12);
	#elif (TMR1_PRESCALER_MODE == PRESCALER_64)
		SETBIT(TCCR1B,CS10);
		SETBIT(TCCR1B,CS11);// prescaler
		CLRBIT(TCCR1B,CS12);
	
	#elif (TMR1_PRESCALER_MODE == PRESCALER_256)
		CLRBIT(TCCR1B,CS10);
		CLRBIT(TCCR1B,CS11);// prescaler
		SETBIT(TCCR1B,CS12);
	#elif (TMR1_PRESCALER_MODE == PRESCALER_1024)
		SETBIT(TCCR1B,CS10);
		CLRBIT(TCCR1B,CS11);// prescaler
		SETBIT(TCCR1B,CS12);
#endif
}
void Timer1_Stop(void)
{
	CLRBIT(TCCR1B,CS10);
	CLRBIT(TCCR1B,CS11);
	CLRBIT(TCCR1B,CS12);
}

void Timer1_SetCallBack(void(*ptr_to_Func)(void))
{
	if(ptr_to_Func != NULL)
	private_ptr_CallBack_OVF = ptr_to_Func ;
}

void Timer1_Set_Comp_Match_A(uint16 copy_u9_compare_val)
{
	OCR1A = copy_u9_compare_val;
}

void Timer1_PWM_Set_Duty(uint16 Duty)
{
	#if (TIMER0_PWM_MODE == TIMER0_NON_INVERTING_PWM_MODE)
		if (Duty <=100)
		{
			OCR1A = (Duty*(ICR1+1))-1;
		}
	#elif (TIMER0_PWM_MODE == TIMER0_INVERTING_PWM_MODE)
		if (Duty <=100){
			OCR1A =100 - ((Duty*(ICR1+1))-1);
		}
	#endif

}


void __vector_9(void) __attribute__ ((signal));
void __vector_9(void)
{
	/*static uint16 counter = 0;
	counter++;
	if (counter == TIMER1_OVF_COUNTER)
	{
		counter = 0;*/
		//TCNT0 = TMR0_PRELOAD_VAL;
		
		//Call Action
		if(private_ptr_CallBack_OVF != NULL)
		{
			private_ptr_CallBack_OVF();
		}
		
	//}
}

void Timer1_Set_delay_ms_CTC(uint16 delay_ms)
{
	//Restriction under condition tick time is 4 usec
	//OCR0 = 249;
	//the real equation id --> (delay_ms*1000)/(OCR0+1)*4us(or it could be changed))
	private_CTC_A_counter = delay_ms; 
}

void __vector_7(void) __attribute__ ((signal));
void __vector_7(void)
{
	static uint16 ctc_counter = 0;
	ctc_counter++;
	if (ctc_counter == private_CTC_A_counter)
	{
		ctc_counter = 0;
		
		//Call Action
		if(private_ptr_CallBack_OVF != NULL)
		{
			private_ptr_CallBack_OVF();
		}
		
	}
}
/*

void __vector_8(void) __attribute__ ((signal));
void __vector_8(void)
{
	static uint16 ctc_counter = 0;
	ctc_counter++;
	if (ctc_counter == private_CTC_A_counter)
	{
		ctc_counter = 0;
		
		//Call Action
		if(private_ptr_CallBack_OVF != NULL)
		{
			private_ptr_CallBack_OVF();
		}
		
	}
}
*/


void ICU_clearTimerValue(void)
{
	TCNT1 =0;
	ICR1 =0;
}

/*
 * Description : Function to initialize the ICU driver
 * 	1. Set the required clock.
 * 	2. Set the required		edge detection.
 * 	3. Enable the Input Capture Interrupt.
 * 	4. Initialize Timer1 Registers
 */
/*
void ICU_init(const ICU_ConfigType * a_configPtr)
{
	Timer1_Init();
	if(a_configPtr->edge_detection == ICU_Rising_edge)
	SETBIT(TCCR1B,ICES1);
	else if (a_configPtr->edge_detection == ICU_Falling_edge)
	{
		CLRBIT(TCCR1B,ICES1);
	}
	if (a_configPtr->clock_ == PRESCALER_64)
	{
		Timer1_Start();
	}
	SETBIT(TIMSK,TICIE1);
}
*/

void ICU_init(ICU_EdgeSelect edge)
{
	Timer1_Init();
	switch (edge)
	{
		case ICU_Falling_edge:
		CLRBIT(TCCR1B,ICES1);
		break;
		case ICU_Rising_edge:
		SETBIT(TCCR1B,ICES1);
		break;
	}	
	SETBIT(TIMSK,TICIE1);
	Timer1_Start();
	}


/*
 * Description: Function to set the Call Back function address.
 */
void ICU_setCallBackFunc(void (*a_functionAddressPtr) (void))
{
	if(a_functionAddressPtr != NULL)
	private_ptr_ICU = a_functionAddressPtr ;
}

/*
 * Description: Function to set the required edge detection.
 */
void ICU_setEdgeDetectionType(ICU_EdgeSelect a_edgeType)
{
	switch (a_edgeType)
	{
		case ICU_Falling_edge:
		CLRBIT(TCCR1B,ICES1);
		break;
		case ICU_Rising_edge:
		SETBIT(TCCR1B,ICES1);
		break;
	}
}

/*
 * Description: Function to get the Timer1 Value when the input is captured
 *              The value stored at Input Capture Register ICR1
 */
uint16 ICU_getInputCaptureValue(void)
{
	return ICR1;
}

/*
 * Description: Function to disable the Timer1 to stop the ICU Driver
 */
void ICU_deInit(void)
{
	Timer1_Stop();
}

void M_TIMER1_ICU_void_INTDisable()
{
	CLRBIT(TIMSK,TICIE1);
}

void __vector_6(void) __attribute__ ((signal));
void __vector_6(void)
{
	if(private_ptr_ICU != NULL)
	{
		private_ptr_ICU();
	}
	
}