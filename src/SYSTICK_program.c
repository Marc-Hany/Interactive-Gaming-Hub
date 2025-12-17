/*
 * SYSTICK_program.c
 *
 *  Created on: Jul 26, 2025
 *      Author: march
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SYSTICK_config.h"
#include "SYSTICK_interface.h"
#include "SYSTICK_private.h"

static u8 Flag=0;
static void(*Global_pvFuncPtr)(void)=NULL;

void SYSTCICK_voidInit(void)
{
	#if SYSTICK_CLOCK_SOURCE==AHB_CLOCK_SOURCE
	{
		SET_BIT(SYSTICK->STK_CTRL,CTRL_CLKSOURCE);
	}
	#elif SYSTICK_CLOCK_SOURCE==AHB_DIVIDED_BY_8
	{
		CLR_BIT(SYSTICK->STK_CTRL,CTRL_CLKSOURCE);
	}
	#endif
}
void SYSTICK_voidConfigInterruptState(INTERRUPT_STATE Copy_uddtState)
{
	if (Copy_uddtState==INT_DISABLE)
	{
		CLR_BIT(SYSTICK->STK_CTRL,CTRL_TICKINT);
	}
	else if( Copy_uddtState==INT_ENABLE)
	{
		SET_BIT(SYSTICK->STK_CTRL,CTRL_TICKINT);
	}
}
void SYSTICK_voidStart(u32 Copy_u32TicksValue)
{
	SYSTICK->STK_LOAD=Copy_u32TicksValue;
	SYSTICK->STK_VAL=0;						//Clear Val Register
	SET_BIT(SYSTICK->STK_CTRL,CTRL_ENABLE);
}

void SYSTICK_voidDelay_ms(u32 Copy_u32DelayTime)
{
	SYSTICK_voidStart(Copy_u32DelayTime*2000);				//Multiply by 2000 to get time in 1 ms
	while(!GET_BIT(SYSTICK->STK_CTRL,CTRL_COUNTFLAG));		//Wait for flag
	CLR_BIT(SYSTICK->STK_CTRL,CTRL_ENABLE);					//Disable Timer
}
void SYSTICK_voidDelay_us(u32 Copy_u32DelayTime)
{
	SYSTICK_voidStart(Copy_u32DelayTime*2);					//Multiply by 2 to get time in 1 us
	while(!GET_BIT(SYSTICK->STK_CTRL,CTRL_COUNTFLAG));		//Wait for flag
	CLR_BIT(SYSTICK->STK_CTRL,CTRL_ENABLE);					//Disable Timer
}

u32 SYSTICK_u32GetElapsedTime()
{
	return (SYSTICK->STK_LOAD)-(SYSTICK->STK_VAL);
}
u32 SYSTICK_u32GetRemainingTime()
{
	return (SYSTICK->STK_VAL);
}

void SYSTICK_SetCallback(void(*Copy_pvFunc)(void),u32 Copy_u32Periodicity_us)
{
	Global_pvFuncPtr=Copy_pvFunc;
	SYSTICK_voidStart(Copy_u32Periodicity_us*2);
}

void SYSTICK_SetCallbackSingle(void(*Copy_pvFunc)(void),u32 Copy_u32Periodicity_us)
{
	Flag=1;
	Global_pvFuncPtr=Copy_pvFunc;
	SYSTICK_voidStart(Copy_u32Periodicity_us*2);
}

void SysTick_Handler(void)
{
	if(Global_pvFuncPtr!=NULL)
	{
		Global_pvFuncPtr();
	}
	if(Flag)
	{
		SYSTICK_voidConfigInterruptState(INT_DISABLE);
	}
	Flag=0;
}
