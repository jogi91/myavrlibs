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

#include <avr/io.h>
#include <avr/interrupt.h>
#include "spi.h"

static volatile uint8_t Spi_Read_Position = 0;
static volatile uint8_t Spi_Write_Position = 0;
static char* Spi_Receive_Buffer;
static uint8_t Spi_Receive_Buffer_Size;

ISR(SPI_STC_vect){
	if(MASTER == 1){ //set SS high after Transmission
		PORTB = PORTB | (1<<SS);
	}
	if(MASTER == 0){
		Spi_Receive_Buffer[Spi_Write_Position++] = SPDR;
		if (Spi_Write_Position >= Spi_Receive_Buffer_Size) {
			Spi_Write_Position = 0;
		}
	}
}

void spi_master_init(char mode, uint8_t prescaler){
	DDRB = DDRB | (1<<SCK) | (1<<MISO) | (1<<MOSI) | (1<<SS); //Configure Pins as output;
	PORTB = PORTB | (1<<PB2);
	SPCR = SPCR | (1<<SPE) | (1<<MSTR) | (mode<<CPHA) | (prescaler & 0x03);
	if (prescaler & 4) { //Do I have to set the SPI2X bit?
		SPSR = SPSR | SPI2X;
	}

	SPCR = SPCR | (1<<SPIE);
}

void spi_send_blocking(char send){
	PORTB = PORTB & ~(1<<SS); //Set SS low to initialize comm
	SPDR = send;
	while (!(SPSR & (1<<SPIF))) {
		//Waiting for complete
	}
}

void spi_slave_init(char mode, char* receive_buffer, uint8_t receive_buffer_length){
	//Clear MISO to not send back any Data
	PORTB = PORTB & ~(1<<MISO);
	DDRB = DDRB & ~(1<<MISO); 
	SPCR = (1<<SPIE) | (1<<SPE) | (mode<<CPHA);
	Spi_Receive_Buffer = receive_buffer;
	Spi_Receive_Buffer_Size = receive_buffer_length;
}
/* 
 * Read the SPI-DATA
 * FF in the HIGH-Byte Means: No Data
 * 00 in the High-Byte Means: Everything ok
 */ 
uint16_t spi_slave_read(){
	if (Spi_Read_Position == Spi_Write_Position) {
		return 0xFFFF; 
	}
	uint16_t result = 0x00FF & Spi_Receive_Buffer[Spi_Read_Position++];
	if (Spi_Read_Position >= Spi_Receive_Buffer_Size) {
		Spi_Read_Position = 0;
	}
	return result;
}
