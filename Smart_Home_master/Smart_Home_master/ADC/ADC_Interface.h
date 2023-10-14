/*
 * ADC_Interface.h
 *
 *  Created on: Sep 15, 2023
 *      Author: alaae
 */

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_


#define ADC0              0
#define ADC1              1
#define ADC2              2
#define ADC3              3
#define ADC4              4
#define ADC5              5
#define ADC6              6
#define ADC7              7




typedef enum {
	ScanGroup0,
	ScanGroup1
}ScanGroup_t 	;

typedef enum
{
	ADC_Channel_0=0,
	ADC_Channel_1,
	ADC_Channel_2,
	ADC_Channel_3,
	ADC_Channel_4,
	ADC_Channel_5,
	ADC_Channel_6,
	ADC_Channel_7

}ADC_ChannelType;

void ADC_voidInit (void);
void ADC_ReadScanGroup(ScanGroup_t ScanGroupID, u16 *bufferPtr);
u16 ADC_ReadSingleChannel( u8 ADC_CHANNEL );
u16 U16ADC_getDigitalValueAsynchCallBack(ADC_ChannelType Channel_ID,void (*pf) (void));






#endif /* ADC_INTERFACE_H_ */
