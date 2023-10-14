/*
 * Smart_home.c
 *
 * Created: 02-Oct-23 3:08:48 PM
 *  Author: lenovo
 */ 

#include "Smart_Home.h"
uint8 flag =0;
u8 temp_read;
uint8 mode_flag=0, menu_flag =0,User_mode = 0;
static volatile u8 temp_val =0;

/****************************************EEPROM***************************************/
u8 i,j=0,key_pressed=0;
u8 true_flag=0,false_flag=0;
static uint8 SCOUNTER = 3;
static u8 trial_flag=1;

u8 USER_INPUT[4]={0};
static u8 USER_EXPECTED[4];
u8 Default_Password[4] = {0,0,0,0};
u8 USR_PASSWORD[4]     = {0,0,0,0};
u8 NEW_PASSWORD[4]     = {0,0,0,0};
u8 user_id=0;
static u8 user_available[10]  = {0,0,0,0,0,0,0,0,0,0};
u8 user_address[10]    = {0,0,16,32,48,64,80,96,112,128};
uint8 usrinv_flag = 0;

uint8 Return_Key_value()
{
	uint8 KeyPad_key = KEYPAD_read();
	while(KeyPad_key == 0)
	{
		KeyPad_key = KEYPAD_read();
	}
	if(KeyPad_key != '=')
	//LCD_write_data(KeyPad_key);
	while(KEYPAD_read()==KeyPad_key);
	return KeyPad_key;
}

uint16 convert_To_Int(uint8 *str)
{
	uint16 num=0;
	uint8 i=0;
	while(str[i] != '\0')
	{
		num = (num * 10) + (str[i] - 48);
		i++ ;
	}
	return num;
}

void present_admin_menu(void)
{
	uint8 temp_num[3];
	while(1)
	{
		while (1)
		{
		uint8_t responce =SPI_TranCeive(0);
		responce=SPI_TranCeive('A');
		
		UART_vidSendString("Add User (U)\r");
		UART_vidSendString("Delete User (D)\r");
		UART_vidSendString("Door control (C)\r");
		UART_vidSendString("Led control (L)\r");
		UART_vidSendString("Air Conditioner state (A)\r");		
		UART_vidSendString("Switch mode? (Y)\r");

		uint8 recv_states = Uart_Receive();
		UART_vidSendString("\r");
		switch (recv_states)
		{
/****************************************Door Control ***************************************/

			case 'C':
			case 'c':
			responce=SPI_TranCeive('C');
			UART_vidSendString("Door State (C/O)\r");
			uint8 state = Uart_Receive();
			UART_vidSendString("\r");
			if (state == 'C'||state == 'c' )
			{ ////////////////
				 UART_vidSendString("Door Closed\r");
				responce=SPI_TranCeive('C');
				if(responce=='C')
				{
				_delay_ms(500);
				menu_flag =1;
				}
			}
			else if (state == 'o'||state == 'O')
			{
				UART_vidSendString("Door Opened\r");
				responce=SPI_TranCeive('O');
			if (responce=='O' )
			{
				_delay_ms(500);
				menu_flag =1;
			}
			}
			break;
/****************************************Led Intensity***************************************/
			case 'l':
			case 'L':
				responce=SPI_TranCeive('L');
				UART_vidSendString("Light intensity?\r");
				uint8 intesity = Uart_Receive();
				UART_vidSendString("\r");
				if (intesity == 'a'||intesity == 'A')
				{
					responce=SPI_TranCeive('A');
					if(responce=='A')
					{
					_delay_ms(500);
					}
					UART_vidSendString("Led ON\r");

				}
				else if (intesity == 'b'||intesity == 'B')
				{
					responce=SPI_TranCeive('B');
					if(responce=='B')
					{
					_delay_ms(500);
					}
					UART_vidSendString("Lowering Led ");
					UART_vidSendString("Intensity\r");
				}
				else if (intesity == 'c'||intesity == 'C')
				{
					responce=SPI_TranCeive('C');
					if(responce=='C')
					{
					_delay_ms(500);
					}
					UART_vidSendString("Led OFF\r");

				}
				menu_flag = 1;
			break;
/****************************************Air Condition ***************************************/

			case 'A':
            case 'a':
                responce = SPI_TranCeive('A');
                UART_vidSendString("Air Conditioner\r");

                // Receive temp value from slave
                uint8_t temp_val = SPI_TranCeive(0);
                UART_vidSendString("Temp: ");
                UART_vidSendNumber(temp_val);
                UART_vidSendString("C\r");
                responce = SPI_TranCeive(0);
                UART_vidSendString("AC state: ");
                if (temp_val> 28 )
                	 UART_vidSendString("ON\r");
                else
                    UART_vidSendString("OFF\r");
                menu_flag = 1;
            break;
/****************************************Switch Mode ***************************************/

			case 'y':
			case 'Y':
			UART_vidSendString("Admin Mode Switched\r");
			_delay_ms(500);
			User_mode =0;
			menu_flag =1;
			break;
			
/****************************************ADD USER ***************************************/
			case 'U':
			case 'u':
			UART_vidSendString("Enter USER ID 1 to 8\r");
			uint8 user = Uart_Receive();
			UART_vidSendString("\r");
			user = user -'0';
			if (user>0&&user<9)
			{switch (user)
			{
				case 1 ... 8:
				UART_vidSendString("USR ");
				Uart_Transmit(user +'0');
				UART_vidSendString(" New Password:\r");
				PASS_Set(user);
				user_available[user]=1;
				break;
			}
			}
			else
			{
				UART_vidSendString("This user isn't available\r");
			}
			menu_flag = 1;
			break;
			
/****************************************DELETE USER ***************************************/
			case 'D':
			case 'd':
			UART_vidSendString("Enter USER ID 1 to 8\r");
			uint8 user_delete = Uart_Receive();
			UART_vidSendString("\r");
			user_delete = user_delete -'0';
			if (user>0&&user<9)
			{
			switch (user_delete)
			{
				case 1 ... 8:
				if (user_available[user_delete]==0)
				{
					UART_vidSendString("USR ");
					Uart_Transmit(user_delete+'0');
					UART_vidSendString(" Already Deleted!\r");
				}
				else if (user_available[user_delete]==1)
				{
					USER_DELETE(user_delete);
					UART_vidSendString("USR ");
					Uart_Transmit(user_delete+'0');
					UART_vidSendString(" Deleted Successfully\r");
				}
				
				break;
			}
			}
			else
			{
				UART_vidSendString("This user isn't available\r");
			}
			menu_flag = 1;
			break;
		}
		if (menu_flag == 1)
		{
			menu_flag =0;
			break;
		}
		
		}
		if (User_mode ==0)
		{
			break;
		}
	}
}

void user_check(void)
{
	
	LCD_write_string("Enter User ID:");
	uint8 keyval = Return_Key_value();
	keyval = keyval -'0';
	if (keyval>0&&keyval<9)
	{
	switch (keyval)
	{
		case 1 ... 8:
		if (user_available[keyval]==1)
		{
			LCD_Clear();
			LCD_write_string("User ");
			LCD_write_num(keyval);
			LCD_write_string(" Password:");
			USER_LOGIN(keyval);
		}
		else if (user_available[keyval]==0)
		{
			LCD_Position(2,0);
			LCD_write_string("This ID is not ");
			LCD_Position(3,0);
			LCD_write_string("Available!");
			_delay_ms(200);
			LCD_Clear();
			user_check();
		}
		break;
	}
	}
	else
	{
		LCD_Clear();
		LCD_Position(1,2);
		LCD_write_string("This user ID is");
		LCD_Position(2,5);
		LCD_write_string(" Wrong!");
		_delay_ms(200);
		LCD_Clear();
		//user_check();
	}
}

void user_control(void)
{
	while (1){

		while(1)
		{uint8_t responce =SPI_TranCeive(0);
			responce=SPI_TranCeive('U');
			uint8 keypad_val,level_LED_Air;
			LCD_Position(1,0);
			LCD_write_string("Led Intensity->1");
			LCD_Position(2,0);
			LCD_write_string("AC state-> 2");
			LCD_Position(3,0);
			LCD_write_string("Switch mode -> 3");
			keypad_val = Return_Key_value();
			switch (keypad_val)
			{
				case LED_INTENSITY:
				menu_flag =1;
				LCD_Clear();
				LCD_write_string("Level 1 || 2 || 3 ?");
				LCD_Position(2,0);
				level_LED_Air = Return_Key_value();
				switch(level_LED_Air)
				{
					case TURN_ON_LED:
					SPI_TranCeive(TURN_ON_LED);
					menu_flag =1;

					LCD_Clear();
					LCD_write_string("LED intensity = 100%");
					_delay_ms(500);
					LCD_Clear();
					break;

					case LOWER_LED_ON:
					SPI_TranCeive(LOWER_LED_ON);
					menu_flag =1;

					LCD_Clear();
					LCD_write_string("LED intensity = 50%");
					_delay_ms(500);
					LCD_Clear();
					break;
					case TURN_OFF_LED:
					SPI_TranCeive(TURN_OFF_LED);
					menu_flag =1;
					LCD_Clear();
					LCD_write_string("LED intensity = 0%");
					_delay_ms(500);
					LCD_Clear();
					break;
				}
				break;
				case AIR_COND:
				SPI_TranCeive(SET_TEMPRETURE);
				_delay_ms(500);
				temp_read=SPI_TranCeive(0);
				menu_flag =1;
				LCD_Clear();
				LCD_write_string("AC state = ");
				if (temp_read>28)
				{
					LCD_write_string("ON");

				}
				else
				{
					LCD_write_string("OFF");


				}
				LCD_Position(2,0);
				LCD_write_string("Temp:");
				LCD_write_num(temp_read);
				LCD_write_string("C");
				_delay_ms(300);
				LCD_Clear();
				//return air cond state
				break;
				case '3':
				LCD_Clear();
				LCD_write_string("User mode switched");
				_delay_ms(300);
				LCD_Clear();
				menu_flag =1;
				User_mode =1;
				break;
			}
			if (menu_flag == 1)
			{
				menu_flag =0;
				break;
			}
		}
		if (User_mode == 1)
		{
			break;
		}
	}
}

void Control_Led (u8 Duty_Cycle)
{
	TIMER0_voidSetDutyCycleFastPWM(Duty_Cycle);
}

u8 Read_Temperature(void) {

	uint16 ADC_Value = ADC_ReadSingleChannel(ADC1);
	//ADC_ReadScanGroup(ScanGroup1, &ADC_Value); // Read from ADC channel 0

	// Calculate temperature value in degrees Celsius
	u16 mV_Value = (ADC_Value * 5000UL) / 1023UL;
	u8 temperature_value = mV_Value / 10;


	return temperature_value  ;
}

void check_temp(void)
{
		temp_val = Read_Temperature();
		if(temp_val > 28)
		{
			DIO_WritePinVal(Pin_A4,HIGH);
		}
		else
		{
			DIO_WritePinVal(Pin_A4,LOW);
		}

}

void convert_To_String(uint8 str[], uint32 num)
{
	sint32 len=0, temp1, i, rem;
	
	temp1 = num;
	
	while(temp1 != 0)                 //finding length of the number
	{
		len++;
		temp1 /= 10;
	}

	for(i=0; i<len; i++)             //converting numbers to equivalent char
	{
		rem = num % 10;
		num = num / 10;
		str[len - (i+1)] = rem + '0';
	}
	str[len] = '\0';
}

void USER_INVALID(void)
{
	u8 i;
	for (i=0;i<20;i++)
	{
		LCD_Clear();
		LCD_Position(1,5);
		LCD_write_string("!WARNING!");
		LCD_Position(2,5);
		LCD_write_string("*********");
		DIO_WritePinVal(Pin_C6,HIGH);
		DIO_WritePinVal(Pin_C7,HIGH);
		_delay_ms(150);
		DIO_WritePinVal(Pin_C7,LOW);
		_delay_ms(30);
		
	}
}
	
void USERISVALID(u8 user_id)
{
	LCD_Clear();
	LCD_write_string("WELCOME BACK,USER ");     //Sends welcome msg. to all users with iD 
	LCD_write_num(user_id);
	_delay_ms(300);
	LCD_Clear();
	user_control();
}

void USER_LOGIN(u8 user_id)
{
	//only reads user which is currently trying to login 
	EEPROM_voidReadPage(user_address[user_id],USER_EXPECTED,4);
	/*for (i=0;i<4;i++)
	{
		LCD_write_num(USER_EXPECTED[i]);  //dummy print for testing!
		
	}*/
	PASS_CHECK(USER_EXPECTED,user_id);	
}

void PASS_CHECK(u8* pass_arr,u8 user_id)
{
	true_flag =0;
	j=0;
	USER_INPUT[0] = 0;
	USER_INPUT[1] = 0;
	USER_INPUT[2] = 0;
	USER_INPUT[3] = 0;
	if (SCOUNTER == 0)
	{
		USER_INVALID();
	}
	while(j<4)
	{
		key_pressed = Return_Key_value();
		switch(key_pressed)
		{
			case '1':
			USER_INPUT[j]=1;
			LCD_write_data('*');
			j++;
			break;
			
			case '2':
			USER_INPUT[j]=2;
			LCD_write_data('*');
			j++;
			break;
			
			case '3':
			USER_INPUT[j]=3;
			LCD_write_data('*');
			j++;
			break;
			
			case '4':
			USER_INPUT[j]=4;
			LCD_write_data('*');
			j++;
			break;
			
			case '5':
			USER_INPUT[j]=5;
			LCD_write_data('*');
			j++;
			break;
			
			case '6':
			USER_INPUT[j]=6;
			LCD_write_data('*');
			j++;
			break;
			
			case '7':
			USER_INPUT[j]=7;
			LCD_write_data('*');
			j++;
			break;
			
			case '8':
			USER_INPUT[j]=8;
			LCD_write_data('*');
			j++;
			break;
			
			case '9':
			USER_INPUT[j]=9;
			LCD_write_data('*');
			j++;
			break;
			
			case '0':
			USER_INPUT[j]=0;
			LCD_write_data('*');
			j++;
			break;
			
			}
			
		}
		for(i=0;i<4;i++)
			{
				if(USER_EXPECTED[i] == USER_INPUT[i])
				{
					true_flag++;
				}
			}
			
			if (true_flag==4)
			{
				//usrinv_flag =0;
				USERISVALID(user_id);
				true_flag =0;
				SCOUNTER = 3;
			}
			else
			{
				LCD_Clear();
				LCD_Position(1,0);
				LCD_write_string("Wrong!");
				LCD_Position(2,0);
				LCD_write_string("Trials left:");
				LCD_write_num(--SCOUNTER);
				_delay_ms(200);
				LCD_Clear();
				/*false_flag++;*/
				LCD_write_string("User ");
				LCD_write_num(user_id);
				LCD_write_string("Password:");
				PASS_CHECK(USER_EXPECTED,user_id);
			}

}

void PASS_Set(u8 user_id)
{
	
	u8 j=0,funbreak=1;
	while(funbreak!=0)
	{
		key_pressed = Uart_Receive();//uart recive only 1 bit until 4 bits
		switch(key_pressed)
		{
			case '1':
			NEW_PASSWORD[j]=1;
			//LCD_WriteChar('*');
			j++;
			break;
			
			case '2':
			NEW_PASSWORD[j]=2;
			//LCD_WriteChar('*');
			j++;
			break;
			
			case '3':
			NEW_PASSWORD[j]=3;
			//LCD_WriteChar('*');
			j++;
			break;
			
			case '4':
			NEW_PASSWORD[j]=4;
			//LCD_WriteChar('*');
			j++;
			break;
			
			case '5':
			NEW_PASSWORD[j]=5;
			//LCD_WriteChar('*');
			j++;
			break;
			
			case '6':
			NEW_PASSWORD[j]=6;
			//LCD_WriteChar('*');
			j++;
			break;
			
			case '7':
			NEW_PASSWORD[j]=7;
			//LCD_WriteChar('*');
			j++;
			break;
			
			case '8':
			NEW_PASSWORD[j]=8;
			//LCD_WriteChar('*');
			j++;
			break;
			
			case '9':
			NEW_PASSWORD[j]=9;
			//LCD_WriteChar('*');
			j++;
			break;
			
			case '0':
			NEW_PASSWORD[j]=0;
			//LCD_WriteChar('*');
			j++;
			break;
			//case 'E':           // E for Enter and it saves password in EEPROM through Change pass. function
			//LCD_Fix();
			/*LCD_WriteString("Password SET!");*/		
			}
		if (j==4)
		{
			UART_vidSendString("\r");
			UART_vidSendString("Password SET!\r");
			//_delay_ms(600);
			CHANGE_PASSWORD(user_id);
			funbreak=0;
			break;
		}
	}
	//CHANGE_PASSWORD(user_id);
}

void USER_DELETE(user_id)
{
	user_available[user_id]=0;      //function not used
}

void USER_ADD(user_id)
{
	user_available[user_id]=1;     //function not used
}

void CHANGE_PASSWORD(u8 user_id)
{
	//assign userpassword array into EEPROM with each of the 9 users addresses pre-assigned
	u8 i=0,n=0;
	for (i;i<4;i++)
	{
		USR_PASSWORD[i]=NEW_PASSWORD[i];
	}
	switch(user_id)
	{
		case 1:		
			EEPROM_voidWritePage(0,USR_PASSWORD,4);//u8 user_address[10]    = {0,0,16,32,48,64,80,96,112,128};
		break;
		
		case 2:
			EEPROM_voidWritePage(16,USR_PASSWORD,4);		
		break;
		
		case 3:
			EEPROM_voidWritePage(32,USR_PASSWORD,4);		
		break;
		
		case 4:
			EEPROM_voidWritePage(48,USR_PASSWORD,4);		
		break;
		
		case 5:
			EEPROM_voidWritePage(64,USR_PASSWORD,4);		
		break;
		
		case 6:
			EEPROM_voidWritePage(80,USR_PASSWORD,4);		
		break;
		
		case 7:
			EEPROM_voidWritePage(96,USR_PASSWORD,4);		
		break;
		
		case 8:
			EEPROM_voidWritePage(112,USR_PASSWORD,4);		
		break;
		
/*
		case 9:
			EEPROM_voidWritePage(128,USR_PASSWORD,4);		
		break;*/
	}
	//DIO_WritePin(PINA6,HIGH);
	//START();
	/*if (user_id==1)
	{
		for (i;i<4;i++)
		{
			USRONE_PASSWORD[i]=NEW_PASSWORD[i];
			EEPROM_voidWritePage(50,USRONE_PASSWORD,4);
		}
	}*/
}
