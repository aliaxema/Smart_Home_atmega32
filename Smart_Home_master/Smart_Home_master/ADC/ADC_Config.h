/*
 * ADC_Config.h
 *
 *  Created on: Sep 15, 2023
 *      Author: alaae
 */

#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_


#define ADC0 0
#define ADC1 1
#define ADC2 2
#define ADC3 3
#define ADC4 4
#define ADC5 5
#define ADC6 6
#define ADC7 7

#define SG0Channel0	  ADC0
#define SG0Channel1	  ADC3
#define SG0channel2	  ADC5
#define SG0channel3	  ADC7

#define SG1Channel0	  ADC1
#define SG1Channel1	  ADC2
#define SG1channel2	  ADC4
#define SG1channel3	  ADC6


#define AREF            0
#define AVCC            1
#define Internal_2_56V  3

#define VOLTAGE_REFERENCE	AVCC
#define ADC_LEFT_ADJUSTMENT_ENABLE	  0

#define ADC_div_128   7
#define ADC_div_64    6
#define ADC_div_32    5
#define ADC_div_16    4
#define ADC_div_8     3
#define ADC_div_4     2
#define ADC_div_2     1


#define ENABLED   1
#define DISABLED  0

#define FREE_RUNNING                0
#define ANALOG_COMPARATOR	        1
#define EXTERNAL_INTERRUPT_REQUEST  2
#define Timer0_Compare_Match	    3
#define Timer0_Overflow			    4
#define Timer_Compare_Match_B	    5
#define Timer1_Overflow			    6
#define Timer1_Capture_Event	    7
#define SINGLE_CONVERSION_MODE      8

#define ADC_VOLTAGE_REFERENCE     AVCC

#define AUTO_TRIGGER_MODE	    DISABLED
#define AUTO_TRIGGER_SOURCE     EXTERNAL_INTERRUPT_REQUEST

#define ADC_Division_Factor      ADC_div_128	  // 15K SPS between Freq Source 50:200Khz



#endif /* ADC_CONFIG_H_ */
