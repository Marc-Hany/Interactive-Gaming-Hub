/*
 * MTIM2_program.c
 *
 *  Created on: Nov 21, 2025
 *      Author: march
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MTIM2_private.h"
#include "MTIM2_config.h"
#include "MTIM2_interface.h"

volatile u8 LedUpdateFlag = 0;
/* 16 MHz on APB1 */
#define TIMER_CLOCK 16000000UL

static void (*Global_pvCallBackFunc)(void) = NULL;

static void MTIM2_voidConfig(u32 Copy_u32Ticks)
{
    /* Compute PreScaler */
    TIM2->PSC = 0;

    /* Load Ticks Number */
    TIM2->ARR = Copy_u32Ticks - 1;

    /* Enable update interrupt */
    SET_BIT(TIM2->DIER, 0);

    /* Start counter */
    SET_BIT(TIM2->CR1, 0);
}

void MTIM2_voidStart_us(u32 Copy_u32Time_uSec, void (*Copy_pvCallBackFunc)(void))
{
	Global_pvCallBackFunc = Copy_pvCallBackFunc;
    u32 ticks = (TIMER_CLOCK / 1000000UL) * Copy_u32Time_uSec; // convert to ticks
    MTIM2_voidConfig(ticks);
}

void MTIM2_voidStart_ms(u32 Copy_u32Time_mSec, void (*Copy_pvCallBackFunc)(void))
{
	Global_pvCallBackFunc = Copy_pvCallBackFunc;
    u32 ticks = (TIMER_CLOCK / 1000UL) * Copy_u32Time_mSec; // convert to ticks
    MTIM2_voidConfig(ticks);
}

void TIM2_IRQHandler(void)
{
	TIM2->SR = 0; // clear UIF flag
	if (Global_pvCallBackFunc != NULL)
	{
		Global_pvCallBackFunc();
	}

}

