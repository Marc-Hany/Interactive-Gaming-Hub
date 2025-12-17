/*
 * MUSART_interface.h
 *
 *  Created on: Aug 22, 2025
 *      Author: march
 */

#ifndef MUSART_INTERFACE_H_
#define MUSART_INTERFACE_H_

typedef enum
{
	SBK=0,
	RWU,
	RE,
	TE,
	IDLEIE,
	RXNEIE,
	TCIE,
	TXEIE,
	PEIE,
	PS,
	PCE,
	WAKE,
	M,
	UE,
	OVER8=15
}MSUART_CR1;

typedef enum
{
	ADD=0,
	LBDL=5,
	LBDIE,
	LBCL=8,
	CPHA,
	CPOL,
	CLKEN,
	STOP,
	LINEN=14
}MSUART_CR2;

typedef enum
{
	DIV_Fraction=0,
	DIV_Mantissa=4
}MSUART_BRR;

void MUSART_voidInit(void);

void MUSART_voidTransmit(u8 Copy_u8Data);	//using 8 bits frame

u8 MUSART_u8Receive(void);
void MUSART_voidSendChars(const u8* ptr);

//TODO: USART with interrupt

#endif /* MUSART_INTERFACE_H_ */
