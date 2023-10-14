/*
 * Smart Home.c
 *
 * Created: 01-Oct-23 10:42:33 AM
 * Author : lenovo
 */ 


#include "Smart_Home.h"
static uint8 recieve_mode;
extern uint8 User_mode;
extern uint8 mode_flag;
extern u8 Default_Password[4];// = {0,0,0,0};
extern u8 user_address[10];//    = {5,15,25,35,45,55,65,75,85,95};
extern uint8 usrinv_flag;
void Timer2_INT(void);

int main(void)
{
	DIO_Init();
	ADC_init();
	LCD_init();
	EEPROM_voidInit();
	KEYPAD_init();
	Uart_init();
	SPI_Master_Initialize();
	Timer2_Init();
	TIMER0_voidInit();  // Initialize Timer0 for Fast PWM mode
	GI_Enable();
	TIMER0_voidStart();  // Start Timer0
	Timer2_Start();
	u8 user_iid=1;
	for (uint8 i=0;i<9;i++)
	{
		EEPROM_voidWritePage(user_address[user_iid],Default_Password,4);
		user_iid++;
	}

	while (1)
	{	
		Select_mode();
		if (recieve_mode =='U'||recieve_mode =='u')
		{
			User_mode =0;
			LCD_write_string("User Mode");
			_delay_ms(200);
			LCD_Clear();
			user_check();
			//LCD_write_string("AAA");
			/*if (usrinv_flag == 0)
			{
				User_mode =0;
				user_control();
			}*/
			
		}
		else if (recieve_mode =='A'||recieve_mode =='a')
		{
			//Timer2_SetCallBack(Timer2_INT);
			User_mode = 1;
			present_admin_menu();
		}

		
		
	}
}

void Select_mode(void)
{
	while (1)
	{
		
		UART_vidSendString("Select Mode (U/A)\r");
		recieve_mode = Uart_Receive();
		UART_vidSendString("\r");
		if (recieve_mode == 'A'||recieve_mode =='U'||recieve_mode=='u'||recieve_mode=='a')
		{
			mode_flag = 1;
		}
		if (mode_flag == 1)
		{
			break;
		}
		
	}
}

