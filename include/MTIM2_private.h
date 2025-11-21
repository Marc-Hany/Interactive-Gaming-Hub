/*
 * MTIM2_private.h
 *
 *  Created on: Nov 21, 2025
 *      Author: march
 */

#ifndef MTIM2_PRIVATE_H_
#define MTIM2_PRIVATE_H_


#define BASE_ADDRESS	0x40000000

typedef struct {
	u32 CR1;
	u32 CR2;
	u32 SMCR;
	u32 DIER;
	u32 SR;
	u32 EGR;
	u32 CCMR1;
	u32 CCMR2;
	u32 CCER;
	u32 CNT;
	u32 PSC;
	u32 ARR;
	u32 Reserved;
	u32 CCR1;
	u32	CCR2;
	u32 CCR3;
	u32 CCR4;
	u32 Reserved1;
	u32 DCR;
	u32 DMAR;
	u32 TIM2_OR;
}TIM2_t;

#define TIM2	((volatile TIM2_t*)BASE_ADDRESS)




#endif /* MTIM2_PRIVATE_H_ */
