/*
 * MUSART_private.h
 *
 *  Created on: Aug 22, 2025
 *      Author: march
 */

#ifndef MUSART_PRIVATE_H_
#define MUSART_PRIVATE_H_

#define MSUART_BASE_ADDRESS		0x40011000

typedef struct
{
	u32 SR;
	u32 DR;
	u32 BRR;
	u32 CR1;
	u32 CR2;
	u32 CR3;
	u32 GTPR;

}MSUART_t;


#define MUSART1		((volatile MSUART_t*)MSUART_BASE_ADDRESS)


#endif /* MUSART_PRIVATE_H_ */
