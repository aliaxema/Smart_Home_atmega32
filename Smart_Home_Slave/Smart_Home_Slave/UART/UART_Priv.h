/*
 * UART_Priv.h
 *
 * Created: 22-Sep-23 3:01:46 PM
 *  Author: lenovo
 */ 


#ifndef UART_PRIV_H_
#define UART_PRIV_H_



#define UCSRC 	(*((volatile uint8*)0x40))
#define UBRRH 	(*((volatile uint8*)0x40))
#define UBRRL 	(*((volatile uint8*)0x29))
#define UDR 	        (*((volatile uint8*)0x2C))


#define UCSRA 	(*((volatile uint8*)0x2B))
/* UCSRA */
#define RXC     7
#define TXC     6
#define UDRE    5
#define FE      4
#define DOR     3
#define PE      2
#define U2X     1
#define MPCM    0



#define UCSRB 	(*((volatile uint8*)0x2A))
/* UCSRB */
#define RXCIE   7
#define TXCIE   6
#define UDRIE   5
#define RXEN    4
#define TXEN    3
#define UCSZ2   2
#define RXB8    1
#define TXB8    0

/* UCSRC */
#define URSEL   7
#define UMSEL   6
#define UPM1    5
#define UPM0    4
#define USBS    3
#define UCSZ1   2
#define UCSZ0   1
#define UCPOL   0



#define ASYNC	1
#define SYNC	2

#endif /* UART_PRIV_H_ */