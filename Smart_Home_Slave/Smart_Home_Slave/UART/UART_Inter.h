/*
 * UART_Inter.h
 *
 * Created: 22-Sep-23 3:01:29 PM
 *  Author: lenovo
 */ 


#ifndef UART_INTER_H_
#define UART_INTER_H_
#include "../STD_TYPES.h"
#include "../BIT_MATH.h"

#include "UART_Config.h"
#include "UART_Priv.h"


void Uart_init();
void Uart_Transmit(uint8 data);
uint8 Uart_Receive();
void UART_TXC_intDisable(void);
void UART_RXC_intDisable(void);
void UART_vidSendString(uint8 * u8pStringCpy);
void USART_ReceiveString(uint8 *u8pStringCpy);
uint8 UART_receiveNoBlock(void);
void UART_sendNoBlock(const uint8 data);
void UART_TXC_intSetCallBack(void (*localFptr)(void));
void UART_RXC_intSetCallBack(void (*localFptr)(void));
void UART_DEMPTY_intSetCallBack(void (*localFptr)(void));

#endif /* UART_INTER_H_ */