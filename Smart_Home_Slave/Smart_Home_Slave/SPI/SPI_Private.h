/*
 * SPI_Private.h
 *
 *  Created on: Sep 23, 2023
 *      Author: alaae
 */

#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_


#define DDRB (*(volatile uint8*)(0x37U))

#define SPCR (*((volatile u8*)0x2D))
#define SPIE 7
#define SPE 6
#define DORD 5
#define MSTR 4
#define CPOL 3
#define CPHA 2
#define SPR1 1
#define SPR0 0

#define SPSR (*((volatile u8*)0x2E))
#define SPIF 7
#define WCOL 6
#define SPI2X 0

#define SPDR (*((volatile u8*)0x2F))

#define DDRB (*((volatile u8*)0x37))
#define PORTB (*((volatile u8*)0X38))
#define SS 4
#define MOSI 5
#define MISO 6
#define SCK 7

#define MASTER                                     0
#define SLAVE                                      1

#define MSB                                        0
#define LSB                                        1

#define SPI_FOSC_4                                 0
#define SPI_FOSC_16                                1
#define SPI_FOSC_64                                2
#define SPI_FOSC_128                               3
#define SPI_FOSC_2                                 4
#define SPI_FOSC_8                                 5
#define SPI_FOSC_32                                6
#define SPI_FOSC_64_2                              7


#define  LEAD_RISING_SAMPLE                        0
#define  LEAD_FALING_SAMPLE                        1
#define  LEAD_RISING_SET                           2
#define  LEAD_FALING_SET                           3




#endif /* SPI_PRIVATE_H_ */
