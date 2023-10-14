/*
 * Smart Home.c
 *
 * Created: 01-Oct-23 10:42:33 AM
 * Author : lenovo
 */ 


#include "Smart_Home.h"

extern volatile u8 temp_val;

void Timer2_INT(void);
volatile u8 TEMP ;

int main(void)
{
	DIO_Init();
	ADC_init();
	LCD_init();
	KEYPAD_init();
	Uart_init();
	SPI_SLave_Initialize();
	Timer2_Init();
	TIMER0_voidInit();  // Initialize Timer0 for Fast PWM mode
	GI_Enable();
	TIMER0_voidStart();  // Start Timer0
	Timer2_Start();

	while (1) {
	    Timer2_SetCallBack(Timer2_INT);

	    uint8_t response = SPI_TranCeive(0);
/*********************************************Admin Mode*************************************************/
	    if (response == 'A') {
	    	if(temp_val > 60)
	    		{
	    			DIO_WritePinVal(Pin_C0,HIGH);

	    		}
	    		else
	    		{
	    			DIO_WritePinVal(Pin_C0,LOW);

	    		}
	        response = SPI_TranCeive(0);
/**************************************Door Control***************************************/
	        if (response == 'C') {
	            response = SPI_TranCeive(0);
	            /*      Open Door      */
	            if (response == 'O') {
	                response = SPI_TranCeive('O');
	                SRVM_voidOn(180);
	            }
	            /*      Close Door      */

	            else if (response == 'C') {
	                response = SPI_TranCeive('C');
	                SRVM_voidOn(90);
	            }
	        }

/**************************************Dimming the led***************************************/
	        else if (response == 'L') {
	       	            response = SPI_TranCeive(0);
	       	            /*      Level A      */
	       	            if (response == 'A') {
	       	                response = SPI_TranCeive('A');
	       	                   Control_Led(100);
	       	            }
	       	            /*      Level B      */

	       	            else if (response == 'B') {
	       	                response = SPI_TranCeive('B');
	       	                 Control_Led(40);
	       	               }
	       	            /*      Level C      */
	       	            else if (response == 'C') {
	       	         	        response = SPI_TranCeive('C');
	       	         	       Control_Led(1);
	       	         	   }
	       	        }
/************************************Air Condition Control************************************/
	        else if (response == 'A') {
	            response = SPI_TranCeive(temp_val);
	            if (response == '0') {
	                if (READ_BIT(PINA, 4) == 0)
	                   response = SPI_TranCeive('O');
	                else if (READ_BIT(PINA, 4) == 1)
	                   response = SPI_TranCeive('C');

	            }}


	        }

/*********************************************User Mode*************************************************/
	    else if (response == 'U'){
	    	if(temp_val >60 )
	         {
	         	DIO_WritePinVal(Pin_C0,HIGH);
	         }
	         else
	         {
	         	DIO_WritePinVal(Pin_C0,LOW);

	         }
	    u8  request = SPI_TranCeive(DEFAULT_ACK);
		switch(request)
		{
		case TURN_ON_LED :
		DIO_WritePinVal(Pin_B0,HIGH);
		Control_Led(100);
		break;
		case LOWER_LED_ON :
		Control_Led(50);
		break;
		case TURN_OFF_LED :
		//DIO_WritePinVal(Pin_B0,HIGH);
		Control_Led(1);
		break;
		case SET_TEMPRETURE :
		SPI_TranCeive(temp_val);
		//TEMP = SPI_TranCeive(DEFAULT_ACK);


		DIO_WritePinVal(Pin_B0,HIGH);
		break;
	   }


	    }
}
}
void Timer2_INT(void)
{
	check_temp();
}
