/*
 * Timer2_Inter.h
 *
 * Created: 26-Sep-23 1:47:49 PM
 *  Author: lenovo
 */ 


#ifndef TIMER2_INTER_H_
#define TIMER2_INTER_H_

#include "../STD_TYPES.h"
#include "../BIT_MATH.h"

#include "Timer2_Config.h"
#include "Timer2_Priv.h"

void Timer2_Init(void);
void Timer2_Start(void);
void Timer2_Stop(void);
void Timer2_SetCallBack(void(*ptr_to_Func)(void));
void Timer2_Set_Comp_Match(uint8 copy_u9_compare_val);
void Timer2_Set_delay_ms_CTC(uint16 delay_ms);
void Timer2_PWM_Set_Duty(uint8 Duty);



#endif /* TIMER2_INTER_H_ */