/*
 * SPI_Interface.h
 *
 *  Created on: Sep 23, 2023
 *      Author: alaae
 */

#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

#include "../STD_TYPES.h"
#include "../BIT_MATH.h"

#include "../DIO/DIO_Int.h"
#include "../DIO/DIO_Prv.h"


#include "SPI_Private.h"
#include "SPI_Config.h"

void SPI_Master_Initialize(void);
void SPI_SLave_Initialize(void);
void SPI_Transmit(u8 dataTransmit);
u8 SPI_Receive(void);
u8 SPI_TranCeive(u8 data);

#endif /* SPI_INTERFACE_H_ */
