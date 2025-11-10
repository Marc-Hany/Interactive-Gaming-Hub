/*
 * SCB_private.h
 *
 *  Created on: Aug 1, 2025
 *      Author: march
 */

#ifndef SCB_PRIVATE_H_
#define SCB_PRIVATE_H_

#define SCB_BASE_ADDRESS	0xE000ED00

//#define AIRCR	(*(volatile u32*)0xE000ED0C)

typedef struct
{
	u32 CPUID;
	u32 ICSR;
	u32 VTOR;
	u32 AIRCR;
}SCB_t;

#define SCB	((volatile SCB_t*)SCB_BASE_ADDRESS)



#endif /* SCB_PRIVATE_H_ */
