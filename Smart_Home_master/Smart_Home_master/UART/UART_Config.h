/*
 * UART_Config.h
 *
 * Created: 22-Sep-23 3:02:13 PM
 *  Author: lenovo
 */ 


#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

#define Transmission_Type	SYNC

#define BAUD_RATE_EQN		(((uint32)F_CPU/16*(uint32)BAUD_RATE)-1)



#endif /* UART_CONFIG_H_ */