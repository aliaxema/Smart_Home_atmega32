
#include "../STD_TYPES.h"
#include "../BIT_MATH.h"
#include "TIMR0_config.h"
#include "TIMR0_interface.h"
#include "TIMR0_Private.h"



static u16 Privite_ctcCounter;
static void (*Private_pCallBackOVF)(void)=NULL;
static void (*Private_pCallBackCTC)(void)=NULL;

void TIMER0_voidInit(void)
{

	     /*Select  Timer Mode*/

      #if(TIMER0_MODE == TIMER0_NORMAL)
      	   CLEAR_BIT(TCCR0 , 6);
      	   CLEAR_BIT(TCCR0 , 3);

      	 /*INIT TIMER WITH PRELOAD VALUE*/
      	   TCNT0=TIMR0_PRELOAD_VALUE;

      	 /*Enable OV INTERRUPT*/
      	    SET_BIT(TIMSK , 0);

      #elif(TIMER0_MODE == TIMER0_CTC)

      	   CLEAR_BIT(TCCR0 , 6);
      	   SET_BIT(TCCR0   , 3);

           /*Enable OUTPUT COMPARE MATCH INTERRUPT*/
    	    SET_BIT(TIMSK , 1);

      #elif(TIMER0_MODE == TIMER0_FAST_PWM )
               SET_BIT(TCCR0 , 6);
               SET_BIT(TCCR0 , 3);

            #if (TIMER0_PWM_ACTION==NON_INVERTING_MODE)
                    /*SELECT NON INVERVAL MODE */
               	   CLEAR_BIT(TCCR0 , 4);
                   SET_BIT(TCCR0 , 5);
            #elif(TIMER0_PWM_ACTION==INVERTING_MODE)
                     /*SELECT INTERVAL MODE */
                    SET_BIT(TCCR0 , 4);
                 	  SET_BIT(TCCR0 , 5);
            #endif


      #elif(TIMER0_MODE == TIMER0_PHASE_PWM )
      	SET_BIT(TCCR0 , 6);
      	CLEAR_BIT(TCCR0 , 3);

      #endif




}
	

// START TIMER 0
	
void TIMER0_voidStart(void)
{  //SELECT  PRESCALER  -> 64
	SET_BIT(TCCR0 , 0);
    SET_BIT(TCCR0 , 1);
    CLEAR_BIT(TCCR0 , 2);
	}

// STOP TIMER 0

void TIMER0_voidStop(void)
{
	CLEAR_BIT(TCCR0 , 0);
	CLEAR_BIT(TCCR0 , 1);
	CLEAR_BIT(TCCR0 , 2);
}

// DELAY MS  USING CTC MODE

void TIMER0_voidSetDelayUsingCTC_Ms(u16 Delay_ms)
{

   OCR0=249;
   Privite_ctcCounter= Delay_ms ;

}

// SET DUTY CYCLE FOR  FAST PWM

void TIMER0_voidSetDutyCycleFastPWM(u8 Duty_Cycle)
{

	if(Duty_Cycle <=100)
	{
      #if (TIMER0_PWM_ACTION==NON_INVERTING_MODE)

		OCR0 = (((u16)Duty_Cycle*256)/100)-1;

      #elif(TIMER0_PWM_ACTION==INVERTING_MODE)
      	Duty_Cycle=100-Duty_Cycle;

    	OCR0= (((u16)Duty_Cycle *256 ) /100)-1;

      #endif
    }
}
// SET OCR0 REGESTER WITH COMPLERE VALUE

void TIMER0_voidSetCompareVal(u8 Copy_u8ComVal)
{
	OCR0=Copy_u8ComVal;
}

/*********************************************************************************************/
/*                                      CALL BACK FUNCTIONS                                  */
/*********************************************************************************************/
// OVER FLOW CALL BACK FUNCTION

void TIMER0_voidetCallBackOV(void(*PtrToFun)(void))
{

if(PtrToFun !=NULL)
{
	Private_pCallBackOVF=PtrToFun;
}
}

// CTC CALL BACK FUNCTION

void TIMER0_voidetCallBackCTC(void(*PtrToFun)(void))
{

if(PtrToFun !=NULL)
{
	Private_pCallBackCTC=PtrToFun;
}
}

/*********************************************************************************************/
/*                                          ISRS                                             */
/*********************************************************************************************/
// OVER FLOW INTERRUPT
void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{
	static u16 Counter=0;
	Counter++;
	if(TIMR0_OV_COUNTER == Counter)
	{
		/*Init timer with preload value*/
		TCNT0=TIMR0_PRELOAD_VALUE;

		Counter= 0;
		/*Call Action*/
   if(Private_pCallBackOVF != NULL)
   {
	   Private_pCallBackOVF();
   }
	}
	
}
// CTC INTERRUPT

void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
	static u16 Counter=0;
	Counter++;
	if(Privite_ctcCounter == Counter)
	{

		Counter= 0;
		/*Call Action*/
   if(Private_pCallBackCTC != NULL)
   {
	   Private_pCallBackCTC();
   }
	}

}
