/*
 * MEXTI_private.h
 *
 *  Created on: Aug 2, 2025
 *      Author: march
 */

#ifndef MEXTI_PRIVATE_H_
#define MEXTI_PRIVATE_H_

#define MEXTI_BASE_ADDRESS		0x40013C00
#define MSYSCFG_BASE_ADDRESS	0x40013800

typedef struct
{
	u32 IMR;
	u32 EMR;
	u32 RTSR;
	u32 FTSR;
	u32 SWIER;
	u32 PR;

}MEXTI_t;

typedef struct
{
	u32 MEMRMP;
	u32 PMC;
	u32 EXTICR[4];
	u32 Reserved[2];
	u32 CMPCR;

}MSYSCFG_t;

#define MEXTI	((volatile MEXTI_t*)MEXTI_BASE_ADDRESS)
#define MSYSCFG	((volatile MSYSCFG_t*)MSYSCFG_BASE_ADDRESS)

/* Number of EXTI lines (usually 16 for STM32F4/F1 series) */
#define MEXTI_LINE_COUNT 16

#endif /* MEXTI_PRIVATE_H_ */
