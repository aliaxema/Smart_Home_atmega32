/*
 * SPI_Program.c
 *
 *  Created on: Sep 23, 2023
 *      Author: alaae
 */

#include "SPI_interface.h"

void SPI_Master_Initialize(void)
{
	//Define directions of pins for master
	SET_BIT(DDRB, 5);//MOSI pins
	CLEAR_BIT(DDRB, 6);//MISO pins
	SET_BIT(DDRB, 7);//SCK pins
	SET_BIT(DDRB, 4);//SS pins
	//One Line
	SPCR = 0x53;
}
void SPI_SLave_Initialize(void)
{
	//Define direction of pins for slave
	CLEAR_BIT(DDRB, MOSI);//MOSI pins
	SET_BIT(DDRB, MISO);//MISO pins
	CLEAR_BIT(DDRB, SCK);//SCK pins
	CLEAR_BIT(DDRB, SS);//SS pins
	//One Line
	SPCR = 0x43;

}
void SPI_Transmit(u8 dataTransmit)
{
	//Two Lines
	SPDR = dataTransmit;
	while (GET_BIT(SPSR, SPIF) != 1);
}
u8 SPI_Receive(void)
{
	//Two Lines
	while (GET_BIT(SPSR, SPIF) != 1);
	return SPDR;
}
u8 SPI_TranCeive(u8 data)
{
	SPDR = data;
	while (GET_BIT(SPSR, SPIF) != 1);
	return SPDR;
}




