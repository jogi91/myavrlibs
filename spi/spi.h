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

#define MASTER 0
#define SLAVE 1

#define SS PB2
#define MOSI PB3
#define MISO PB4
#define SCK	PB5

#define PRESCALER_2	4
#define PRESCALER_4 0
#define PRESCALER_8 5
#define PRESCALER_16 1
#define PRESCALER_32 6
#define PRESCALER_64 2
#define PRESCALER_128 3

#define SPI_MODE_0 0
#define SPI_MODE_1 1
#define SPI_MODE_2 2
#define SPI_MODE_3 3

void spi_master_init(char mode, uint8_t prescaler);
void spi_slave_init(char mode, char* receive_buffer, uint8_t receive_buffer_length);

void spi_send_blocking(char send);

uint16_t spi_slave_read(void);
