/*
 * TIMR0_Interface.h
 *
 *  Created on: Sep 17, 2023
 *      Author: alaae
 */

#ifndef TIMR0_INTERFACE_H_
#define TIMR0_INTERFACE_H_


void TIMER0_voidInit(void);

void TIMER0_voidStart(void);

void TIMER0_voidStop(void);

void TIMER0_voidSetDelayUsingCTC_Ms(u16 Delay_ms);

void TIMER0_voidSetCompareVal(u8 Copy_u8ComVal);
void TIMER0_voidSetDutyCycleFastPWM(u8 Duty_Cycle);

void TIMER0_voidetCallBackOV(void(*PtrToFun)(void));
void TIMER0_voidetCallBackCTC(void(*PtrToFun)(void));



#endif /* TIMR0_INTERFACE_H_ */
