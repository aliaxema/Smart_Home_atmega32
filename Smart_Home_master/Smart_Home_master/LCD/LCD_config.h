/*
 * LCD_config.h
 *
 * Created: 10-Sep-23 1:44:44 PM
 *  Author: lenovo
 */ 


#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_


/*
#define	LCD_ENA(x)	if(x == 1) SETBIT(PORTA,2);else CLRBIT(PORTA,2);
#define	LCD_RSAA(x)	if(x == 1) SETBIT(PORTA,3);else CLRBIT(PORTA,3);
#define	LCD_PIN4(x)	if(x == 1) SETBIT(PORTB,0);else CLRBIT(PORTB,0);
#define	LCD_PIN5(x)	if(x == 1) SETBIT(PORTB,1);else CLRBIT(PORTB,1);
#define	LCD_PIN6(x)	if(x == 1) SETBIT(PORTB,2);else CLRBIT(PORTB,2);
#define	LCD_PIN7(x)	if(x == 1) SETBIT(PORTB,4);else CLRBIT(PORTB,4);
*/


#define LCD_D0	Pin_B0
#define LCD_D1	Pin_B1
#define LCD_D2	Pin_B2
#define LCD_D3	Pin_A7
#define LCD_D4	Pin_B0
#define LCD_D5	Pin_B1
#define LCD_D6	Pin_B2
#define LCD_D7	Pin_A7

#define LCD_EN	Pin_A2
#define LCD_RS	Pin_A3



#endif /* LCD_CONFIG_H_ */