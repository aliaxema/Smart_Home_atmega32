/*
 * UART_Prog.c
 *
 * Created: 22-Sep-23 3:01:00 PM
 *  Author: lenovo
 */ 

#include "UART_Inter.h"


static void (*uart_txc_fPtr)(void) ;
static void (*uart_rxc_fPtr)(void);
static void (*uart_dEmpty_fPtr)(void) ;

void Uart_init(){
	// baud rate
	
	UBRRL = 103;			// baud rate 9600, F_CPU = 16Mhz
	UCSRB|=(1<<RXEN)|(1<<TXEN);
	UCSRC|=(1<<UCSZ0)|(1<<UCSZ1);
	#if (Transmission_Type == ASYNC)
	UCSRB|=(1<<TXCIE)|(1<<RXCIE)|(1<<UDRIE);
	CLRBIT(UCSRC,UMSEL);
	#elif (Transmission_Type == SYNC)
	SETBIT(UCSRC,UMSEL); 
	#endif
	
}

void Uart_Transmit(uint8 data){
	while(READBIT(UCSRA,UDRE) == 0);
	UDR = data;
	while(READBIT(UCSRA,TXC) == 0);
}

uint8 Uart_Receive(){
	while(READBIT(UCSRA,RXC) == 0);
	return UDR;
}

void UART_vidSendString(uint8 * u8pStringCpy) {
	uint8 i=0;
	while(u8pStringCpy[i] != '\0') {
		Uart_Transmit(u8pStringCpy[i]);
		i++;
	}
	Uart_Transmit('\0');
}

void USART_ReceiveString(uint8 *u8pStringCpy)
{
	uint8 i = 0;
	u8pStringCpy[i] = Uart_Receive();
	while(u8pStringCpy[i] != '\0')
	{
		i++;
		u8pStringCpy[i] = Uart_Receive();
	}
	u8pStringCpy[i] = '\0';
}

void UART_sendNoBlock(const uint8 data)
{
	/* write data in buffer */
	UDR = data;
}

uint8 UART_receiveNoBlock(void)
{
	/* retrieve data from buffer */
	return UDR;
}

void UART_TXC_intDisable(void)
{
	CLRBIT(UCSRB, TXCIE);
}

void UART_RXC_intDisable(void)
{
	CLRBIT(UCSRB, RXCIE);
}

void UART_TXC_intSetCallBack(void (*localFptr)(void))
{
	uart_txc_fPtr = localFptr;
}

void UART_RXC_intSetCallBack(void (*localFptr)(void))
{
	uart_rxc_fPtr = localFptr;
}

void UART_DEMPTY_intSetCallBack(void (*localFptr)(void))
{
	uart_dEmpty_fPtr = localFptr;
}

void __vector_15(void) __attribute__ ((signal));
void __vector_15(void)
{
		uart_txc_fPtr();
	
}

void __vector_13(void) __attribute__ ((signal));
void __vector_13(void)
{
		uart_rxc_fPtr();
	
}

void __vector_14(void) __attribute__ ((signal));
void __vector_14(void)
{
	
		uart_dEmpty_fPtr();

}