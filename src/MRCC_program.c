/*
 * MRCC_program.c
 *
 *  Created on: Jul 19, 2025
 *      Author: march
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MRCC_config.h"
#include "MRCC_interface.h"
#include "MRCC_private.h"


void MRCC_voidInit(void) //Initialize RCC
{
	//Check Config. for System CLK source
	#if SYSTEM_CLOCK == HSI
		/*HSI ON*/
		SET_BIT(RCC->CR,HSION);

		/*Wait for stability*/
		while(!GET_BIT(RCC->CR,HSIRDY));

		/*Select HSI as System Clock SW=00*/
//		CLR_BIT(RCC->CFGR,0);
//		CLR_BIT(RCC->CFGR,1);
		RCC->CFGR &=~3;
		RCC->CFGR|=0;	//optional in this case but maybe needed in other cases

	#elif SYSTEM_CLOCK == HSE
		/*Choose HSE Source*/
		#if HSE_SOURCE_TYPE==MECHANICAL
			CLR_BIT(RCC->CR,HSEBYP);
		#elif
			SET_BIT(RCC->CR,HSEBYP);
		#endif
		/*HSE ON*/
		SET_BIT(RCC->CR,HSEON);

		/*Wait for stability*/
		while(!GET_BIT(RCC->CR,HSERDY));

		/*Select HSE as System Clock SW=01*/
		RCC->CFGR &=~3;
		RCC->CFGR |=1;

		/*HSI OFF*/
		CLR_BIT(RCC->CR,HSION);

	#elif SYSTEM_CLOCK == PLL_HSI
		/*HSI ON*/
		SET_BIT(RCC->CR,HSION);

		/*Wait for stability*/
		while(!GET_BIT(RCC->CR,HSIRDY));

		/*Select HSI as PLL Source*/
		CLR_BIT(RCC->PLLCFGR,PLLSRC);

		/*PLL ON*/
		SET_BIT(RCC->CR,PLLON);

		/*Wait for stability*/
		while(!GET_BIT(RCC->CR,PLLRDY));

		/*Select PLL as System Clock SW=10*/
		RCC->CFGR &=~3;
		RCC->CFGR |=2;

	#elif SYSTEM_CLOCK == PLL_HSE
		/*Choose HSE Source*/
		#if HSE_SOURCE_TYPE==MECHANICAL
			CLR_BIT(RCC->CR,HSEBYP);
		#elif
			SET_BIT(RCC->CR,HSEBYP);
		#endif
		/*HSE ON*/
		SET_BIT(RCC->CR,HSEON);

		/*Wait for stability*/
		while(!GET_BIT(RCC->CR,HSERDY));

		/*Select HSE as PLL Source*/
		SET_BIT(RCC->PLLCFGR,PLLSRC);

		/*PLL ON*/
		SET_BIT(RCC->CR,PLLON);

		/*Wait for stability*/
		while(!GET_BIT(RCC->CR,PLLRDY));

		/*Select PLL as System Clock SW=10*/
		RCC->CFGR &=~3;
		RCC->CFGR |=2;

		/*HSI OFF*/
		CLR_BIT(RCC->CR,HSION);

	#endif
}

void MRCC_voidPeripheralEnable(u8 Copy_u8Bus , u8 Copy_u8Peripheral) //Enable the Peripheral of your choice
{
	switch (Copy_u8Bus)
	{
	case AHB1:	//AHB1
		SET_BIT(RCC->AHB1ENR,Copy_u8Peripheral); //Enable Bit for specified Peripheral
		break;
	case AHB2:	//AHB2
		SET_BIT(RCC->AHB2ENR,Copy_u8Peripheral); //Enable Bit for specified Peripheral
		break;
	case APB1:	//APB1
		SET_BIT(RCC->APB1ENR,Copy_u8Peripheral); //Enable Bit for specified Peripheral
		break;
	case APB2:	//APB2
		SET_BIT(RCC->APB2ENR,Copy_u8Peripheral); //Enable Bit for specified Peripheral
		break;


	}
}

void MRCC_voidPeripheralDisable(u8 Copy_u8Bus , u8 Copy_u8Peripheral) //Disable the Peripheral of your choice
{
	switch (Copy_u8Bus)
	{
	case AHB1:	//AHB1
		CLR_BIT(RCC->AHB1ENR,Copy_u8Peripheral); //Enable Bit for specified Peripheral
		break;
	case AHB2:	//AHB2
		CLR_BIT(RCC->AHB2ENR,Copy_u8Peripheral); //Enable Bit for specified Peripheral
		break;
	case APB1:	//APB1
		CLR_BIT(RCC->APB1ENR,Copy_u8Peripheral); //Enable Bit for specified Peripheral
		break;
	case APB2:	//APB2
		CLR_BIT(RCC->APB2ENR,Copy_u8Peripheral); //Enable Bit for specified Peripheral
		break;
	}
}
