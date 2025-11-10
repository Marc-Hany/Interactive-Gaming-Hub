/*
 * MRCC_private.h
 *
 *  Created on: Jul 19, 2025
 *      Author: march
 */

#ifndef MRCC_PRIVATE_H_
#define MRCC_PRIVATE_H_

#define BASE_ADDRESS	0x40023800

typedef struct {
	u32 CR;
	u32 PLLCFGR;
	u32 CFGR;
	u32 CIR;
	u32 AHB1RSTR;
	u32 AHB2RSTR;
	u32 Reserved1;
	u32 Reserved2;
	u32 APB1RSTR;
	u32 APB2RSTR;
	u32 Reserved3;
	u32 Reserved4;
	u32 AHB1ENR;
	u32 AHB2ENR;
	u32 Reserved5;
	u32 Reserved6;
	u32	APB1ENR;
	u32 APB2ENR;
	u32 Reserved7;
	u32 Reserved8;
	u32 AHB1LPENR;
	u32 AHB2LPENR;
	u32 Reserved9;
	u32 Reserved10;
	u32 APB1LPENR;
	u32 APB2LPENR;
	u32 Reserved11;
	u32 Reserved12;
	u32 BDCR;
	u32 CSR;
	u32 Reserved13;
	u32 Reserved14;
	u32 SSCGR;
	u32 PLLI2SCFGR;
	u32 Reserved15;
	u32 DCKCFGR;
}RCC_t;

#define RCC	((volatile RCC_t*)BASE_ADDRESS)

/*System Clocks*/
#define HSI			0
#define HSE 		1
#define PLL_HSI		2
#define PLL_HSE		3

/*HSI Bits*/
#define HSION		0
#define HSIRDY		1
#define HSEBYP		18	//HSE Bypass


/*HSE Bits*/
#define MECHANICAL	0	//Mechanical Oscillator
#define ELECTRICAL	1	//Electrical Oscillator
#define HSEON		16
#define HSERDY		17


/*PLL Bits*/
#define PLLSRC	22
#define PLLON	24
#define PLLRDY	25



#endif /* MRCC_PRIVATE_H_ */
