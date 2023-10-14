/*
 * Timer_Inter.h
 *
 * Created: 17-Sep-23 11:26:23 AM
 *  Author: lenovo
 */ 


#ifndef TIMER_INTER_H_
#define TIMER_INTER_H_


#include "../STD_TYPES.h"
#include "../BIT_MATH.h"

#include "Timer1_Config.h"
#include "Timer1_Priv.h"

void Timer1_Init(void);
void Timer1_Start(void);
void Timer1_Stop(void);
void Timer1_SetCallBack(void(*ptr_to_Func)(void));
void Timer1_Set_Comp_Match_A(uint16 copy_u9_compare_val);
void Timer1_Set_delay_ms_CTC(uint16 delay_ms);
void Timer1_PWM_Set_Duty(uint16 Duty);

typedef enum {
	ICU_Falling_edge,
	ICU_Rising_edge
}ICU_EdgeSelect;
typedef struct
{
	uint8 clock_;
	ICU_EdgeSelect edge_detection;
}ICU_ConfigType;



void ICU_clearTimerValue(void);

/*
 * Description : Function to initialize the ICU driver
 * 	1. Set the required clock.
 * 	2. Set the required edge detection.
 * 	3. Enable the Input Capture Interrupt.
 * 	4. Initialize Timer1 Registers
 */
void ICU_init(ICU_EdgeSelect edge);

/*
 * Description: Function to set the Call Back function address.
 */
void ICU_setCallBackFunc(void (*a_functionAddressPtr) (void));

/*
 * Description: Function to set the required edge detection.
 */
void ICU_setEdgeDetectionType(ICU_EdgeSelect a_edgeType);

/*
 * Description: Function to get the Timer1 Value when the input is captured
 *              The value stored at Input Capture Register ICR1
 */
uint16 ICU_getInputCaptureValue(void);

/*
 * Description: Function to disable the Timer1 to stop the ICU Driver
 */
void ICU_deInit(void);


#endif /* TIMER_INTER_H_ */