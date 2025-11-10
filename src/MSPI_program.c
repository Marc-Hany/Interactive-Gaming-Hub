/*
 * MSPI_program.c
 *
 *  Created on: Aug 29, 2025
 *      Author: march
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MSPI_private.h"
#include "MSPI_config.h"
#include "MSPI_interface.h"

void MSPI_voidMasterInit(void)
{
	CLR_BIT(MSPI->CR1,11);	//8 bit Frame
	CLR_BIT(MSPI->CR1,9);	//Software slave management disabled
	CLR_BIT(MSPI->CR1,10);	//Full Duplex
	CLR_BIT(MSPI->CR1,7);	//MSB transmitted first
	CLR_BIT(MSPI->CR1,1);	//Clock polarity 0 when idle
	CLR_BIT(MSPI->CR1,7);	//The first clock transition is the first data capture edge
	/*Baud rate control*/
	MSPI->CR1 &=~(7<<3);	//fPCLK/2
	SET_BIT(MSPI->CR1,2);	//Master Selection
	SET_BIT(MSPI->CR1,6);	//SPI Enable
}
void MSPI_voidSlaveInit(void)
{
	CLR_BIT(MSPI->CR1,11);	//8 bit Frame
	CLR_BIT(MSPI->CR1,9);	//Software slave management disabled
	CLR_BIT(MSPI->CR1,10);	//Full Duplex (default full duplex)
	CLR_BIT(MSPI->CR1,7);	//MSB transmitted first
	CLR_BIT(MSPI->CR1,1);	//Clock polarity 0 when idle
	CLR_BIT(MSPI->CR1,7);	//The first clock transition is the first data capture edge
	/*Baud rate control*/
	MSPI->CR1 &=~(7<<3);	//fPCLK/2
	CLR_BIT(MSPI->CR1,2);	//Slave Selection
	SET_BIT(MSPI->CR1,6);	//SPI Enable
}

u8 MSPI_u8Transceive(u8 Copy_u8Data)
{
	while(!GET_BIT(MSPI->SR,1))	//wait for data in register
	{
		/*Transmit Data*/
	}
	MSPI->DR = Copy_u8Data;


	while(!GET_BIT(MSPI->SR,0))	//wait for data in register
	{
		/*Receive Data*/
	}
	return (u8)MSPI->DR;


}
