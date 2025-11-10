/*
 * NVIC_private.h
 *
 *  Created on: Aug 1, 2025
 *      Author: march
 */

#ifndef NVIC_PRIVATE_H_
#define NVIC_PRIVATE_H_

#define NVIC_BASE_ADDRESS	0xE000E100

typedef struct
{
	u32 ISER[8];
	u32 Reserved0[24];
	u32 ICER[8];
	u32 Reserved1[24];
	u32 ISPR[8];
	u32 Reserved2[24];
	u32 ICPR[8];
	u32 Reserved3[24];
	u32	IABR[8];
	u32 Reserved4[56];
	u8 IPR[240];	//it should have been u32 IPR[60] (each register 4 peripherals) but we wrote it this way for easier coding as if each register is one peripheral
	u32 Reserved5[580];
	u32 STIR;
}NVIC_t;

#define NVIC	((volatile NVIC_t*)NVIC_BASE_ADDRESS)



#endif /* NVIC_PRIVATE_H_ */
