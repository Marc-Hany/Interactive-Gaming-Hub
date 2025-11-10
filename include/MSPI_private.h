/*
 * MSPI_private.h
 *
 *  Created on: Aug 29, 2025
 *      Author: march
 */

#ifndef MSPI_PRIVATE_H_
#define MSPI_PRIVATE_H_


#define MSPI1_BASE_ADDRESS	0x40013000

typedef struct
{
	u32 CR1;
	u32 CR2;
	u32 SR;
	u32 DR;
	u32 CRCPR;
	u32 RXCRCR;
	u32 TXCRCR;
	u32 I2SCFGR;
	u32 I2SPR;

}MSPI_t;

#define MSPI	((volatile MSPI_t*)MSPI1_BASE_ADDRESS)

#endif /* MSPI_PRIVATE_H_ */
