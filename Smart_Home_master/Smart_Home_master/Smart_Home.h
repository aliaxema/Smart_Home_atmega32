/*
 * Smart_Home.h
 *
 * Created: 02-Oct-23 3:08:35 PM
 *  Author: lenovo
 */ 


#ifndef SMART_HOME_H_
#define SMART_HOME_H_

#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "DIO/DIO_INT.h"
#include "ADC/ADC_Interface.h"
#include "I2C/TWI_interface.h"
#include "SRVM/SRVM_Interface.h"
#include "UART/UART_Inter.h"
#include "Timer1/Timer1_Inter.h"
#include "KeyPad/KeyPad_interface.h"
#include "Ext_EEPROM/EEPROM_interface.h"
#include "LCD/LCD_int.h"
#include "Timer2/Timer2_Inter.h"
#include "GI/GI_Inter.h"
#include "SPI/SPI_Interface.h"

// ****************** USER CONTROL ********************

// ***** (1)  LED INTENSITY    *******

#define LED_INTENSITY				'1'

#define TURN_ON_LED					'3'
#define LOWER_LED_ON				'2'
#define TURN_OFF_LED				'1'


// ***** (2) AIR_COND   *******


#define  AIR_COND					'2'

#define CLOSE_AIR_COND				2
#define OPEN_AIR_COND				4
#define SET_TEMPRETURE             20
#define  FIXED_TEMP                28

 void Control_Led(u8 Duty_Cycle);
 uint16 convert_To_Int(uint8 *str);
 void LCD_First_Write_Pass(void);
 uint8 Return_Key_value();
 u8 Read_Temperature(void);



#endif /* SMART_HOME_H_ */
