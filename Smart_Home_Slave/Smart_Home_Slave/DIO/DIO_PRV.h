/*
 * DIO_PRV.h
 *
 * Created: 08-Sep-23 11:21:03 AM
 *  Author: lenovo
 */ 



#ifndef DIO_PRV_H_
#define DIO_PRV_H_



#define PORTA					(*(volatile uint8*)(0x3BU))
#define DDRA 					(*(volatile uint8*)(0x3AU))
#define PINA 					(*(volatile uint8*)(0x39U))
        
#define PORTB					(*(volatile uint8*)(0x38U))
#define DDRB					(*(volatile uint8*)(0x37U))
#define PINB					(*(volatile uint8*)(0x36U))
        
#define PORTC					(*(volatile uint8*)(0x35U))
#define DDRC					(*(volatile uint8*)(0x34U))
#define PINC					(*(volatile uint8*)(0x33U))
        
#define PORTD					(*(volatile uint8*)(0x32U))
#define DDRD					(*(volatile uint8*)(0x31U))
#define PIND					(*(volatile uint8*)(0x30U))


#endif /* DIO_PRV_H_ */