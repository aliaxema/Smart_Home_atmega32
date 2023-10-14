/*
 * ADC_Program.c
 *
 *  Created on: Sep 15, 2023
 *      Author: alaae
 */

#include "../STD_Types.h"
#include "../BIT_MATH.h"
#include "ADC_Private.h"
#include "ADC_Interface.h"
#include "ADC_Config.h"


static void (*ADC_Fptr )(void) = NULL;


u8 AdcScanGroup1[4]={ SG1Channel0,SG1Channel1,SG1channel2,SG1channel3 };
u8 AdcScanGroup0[4]={ SG0Channel0,SG0Channel1,SG0channel2,SG0channel3 };

u8 * ptr[2]={AdcScanGroup0 , AdcScanGroup1}	;


void ADC_ReadScanGroup(ScanGroup_t ScanGroupID, u16 * bufferPtr ){
	  u8 ChannelIndex;
	  for (ChannelIndex=0;ChannelIndex<4;ChannelIndex++)
	  {
		  bufferPtr[ChannelIndex] = ADC_ReadSingleChannel(  ptr[ScanGroupID][ChannelIndex]	)  ;

	  }

}

void ADC_init() {


	#if (AUTO_TRIGGER_MODE == DISABLED)

	 ADCSRA    =  (1 <<ADEN) | (1<<ADIE) | ADC_Division_Factor ;

	#else

	ADCSRA    = ADC_Division_Factor| (1 <<ADEN) | (1<<ADIE) | 1<<ADATE;

	SFIOR = (AUTO_TRIGGER_SOURCE << ADTS0)| (SFIOR & 0x0F);

	#endif




}

u16 ADC_ReadSingleChannel( u8 ADC_CHANNEL ){


	ADMUX =  (VOLTAGE_REFERENCE<<REFS0) | (ADC_LEFT_ADJUSTMENT_ENABLE<<ADLAR) |ADC_CHANNEL;


	SET_BIT(ADCSRA,ADSC); //  Start Conversion

	while(GET_BIT(ADCSRA,ADIF)==0);

	SET_BIT(ADCSRA,ADIF);// CLear flag by setting it to 1

	return ADC_DATA_REG ;
}

void ADC_InterruptEnable(u8 ADC_CHANNEL)
{
	SET_BIT(ADCSRA,ADIE); //Enable ADC interrupt
	ADMUX =  (VOLTAGE_REFERENCE<<REFS0) | (ADC_LEFT_ADJUSTMENT_ENABLE<<ADLAR) |ADC_CHANNEL; // select channel
	SET_BIT(ADCSRA,ADSC); //Start conversion

}

void ADC_SetCallBack(void(*LocalPtr)(void))
{
	ADC_Fptr=LocalPtr;

}

void __vector_16(void)
{
	if(ADC_Fptr!=0)
{
	ADC_Fptr();


}

}
