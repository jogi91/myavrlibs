/*
** Copyright (C) 2013 Johannes Weinbuch <jweinbuch@gmx.ch>
**  
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
** 
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software 
** Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

/** @file
*
* This is a Library for using the SPI. Edit this file to suit your needs. At the moment, it is written for an ATMega8.
*/

/** @name Configuration
 * These Bits make clear if the AVR is a Master or a Slave
*/
/**@{ */ 
/** 
* @brief SPI-Master
*
* Should be defined as 1, if the AVR is configured as a Master, 0 otherwise
*/
#define MASTER 0
/** 
* @brief SPI-Slave
*
* Should be defined as 1, if the AVR is configured as a Slave, 0 otherwise
*/
#define SLAVE 1
/** @} */ 

/** @name SPI-Pins	
*
* These definitions are used to determine the SPI-PINS. SS can be moved to any free pin on PORTB
*/
/** @{ */ 
#define SS PB2
#define MOSI PB3
#define MISO PB4
#define SCK	PB5
/** @} */ 

/** @name SPI-Prescalers
 *
 * Use them to set the SCK-Speed in spi_master_init()*/ 
/** @{ */ 
#define PRESCALER_2	4
#define PRESCALER_4 0
#define PRESCALER_8 5
#define PRESCALER_16 1
#define PRESCALER_32 6
#define PRESCALER_64 2
#define PRESCALER_128 3
/** @} */ 

/** @name SPI-Modes
*
* Use them to set the SPI-Mode in spi_master_init() or spi_slave_init()
*/
/** @{ */ 
#define SPI_MODE_0 0
#define SPI_MODE_1 1
#define SPI_MODE_2 2
#define SPI_MODE_3 3
/** @} */ 

/** 
* @brief Initializes the Master
*
* The and the Prescaler are set. Further the SPI-Interrupt gets activated. 
* Use sei() before sending via spi. 
* The SS-Pin is used as an output.
*/
void spi_master_init(char mode, uint8_t prescaler);

/** 
* @brief Initializes the Slave
*
* Use sei() before trying to read data.
*
* @param mode Use one of the Macros
* @param receive_buffer Where should received Bytes be stored.
* @param receive_buffer_length How much space is in the buffer?
*/
void spi_slave_init(char mode, char* receive_buffer, uint8_t receive_buffer_length);

/** 
* @brief sends a char and waits
* 
* After send is written to the SPI-Data-Register, 
* the MCU waits until the transmission is complete before returning.
* @param send The char to be sent
*/
void spi_send_blocking(char send);

/**
 * @brief reads the oldest received byte from the buffer
 *
 * @return Two bytes. The lower byte is data, the upper one is meta-information.
 *
 * - 0xFF in the HI-Byte Means: No Data
 * - 0x00 in the HI-Byte Means: Everything ok
 * */ 
uint16_t spi_slave_read(void);
