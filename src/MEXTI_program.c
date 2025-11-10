/*
 * MEXTI_program.c
 *
 *  Created on: Aug 2, 2025
 *      Author: march
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MEXTI_config.h"
#include "MEXTI_interface.h"
#include "MEXTI_private.h"

#include <stdlib.h>


/* Array of callback function pointers */
static void (*EXTI_Callbacks[MEXTI_LINE_COUNT])(void) = {0};

void MEXTI_voidEnable(MEXTI_LINES Copy_uddtInterruptLine)
{
	SET_BIT(MEXTI->IMR,Copy_uddtInterruptLine);
}
void MEXTI_voidDisable(MEXTI_LINES Copy_uddtInterruptLine)
{
	CLR_BIT(MEXTI->IMR,Copy_uddtInterruptLine);
}


void MEXTI_voidSetTriggerEvent(MEXTI_LINES Copy_uddtInterruptLine,TRIGGER_EVENTS Copy_uddtTriggerEvent)
{
	switch(Copy_uddtTriggerEvent)
	{
	case EXTI_RISING_EDGE:
		SET_BIT(MEXTI->RTSR,Copy_uddtInterruptLine);
		CLR_BIT(MEXTI->FTSR,Copy_uddtInterruptLine);
		break;
	case EXTI_FALLING_EDGE:
		SET_BIT(MEXTI->FTSR,Copy_uddtInterruptLine);
		CLR_BIT(MEXTI->RTSR,Copy_uddtInterruptLine);
		break;
	case EXTI_ON_CHANGE:
		SET_BIT(MEXTI->RTSR,Copy_uddtInterruptLine);
		SET_BIT(MEXTI->FTSR,Copy_uddtInterruptLine);
		break;

	}
}
void MEXTI_voidSelectPort(MEXTI_LINES Copy_uddtInterruptLine,MEXTI_PORTS Copy_uddtLinePort)
{
	MSYSCFG->EXTICR[Copy_uddtInterruptLine/4] &=~(15<<(Copy_uddtInterruptLine%4)*4);
	MSYSCFG->EXTICR[Copy_uddtInterruptLine/4] |= (Copy_uddtLinePort<<(Copy_uddtInterruptLine%4)*4);
}

/* Register callback for specific EXTI line */
void MEXTI_voidSetCallback(MEXTI_LINES line, void (*callback)(void))
{
    if (line < MEXTI_LINE_COUNT)
    {
        EXTI_Callbacks[line] = callback;
    }
}

/* Common handler logic for a given EXTI line */
void MEXTI_HandleLine(u8 line)
{
    /* Clear the pending flag */
    MEXTI->PR = (1 << line);

    /* Call the callback if registered */
    if (EXTI_Callbacks[line] != NULL)
    {
        EXTI_Callbacks[line]();
    }
}

/* ---- IRQ Handlers ---- */

/* Single-line IRQs */
void EXTI0_IRQHandler(void)  { MEXTI_HandleLine(0); }
void EXTI1_IRQHandler(void)  { MEXTI_HandleLine(1); }
void EXTI2_IRQHandler(void)  { MEXTI_HandleLine(2); }
void EXTI3_IRQHandler(void)  { MEXTI_HandleLine(3); }
void EXTI4_IRQHandler(void)  { MEXTI_HandleLine(4); }

/* Shared IRQ for lines 5–9 */
void EXTI9_5_IRQHandler(void)
{
    for (u8 line = 5; line <= 9; line++)
    {
        if (MEXTI->PR & (1 << line))  // If pending
        {
            MEXTI_HandleLine(line);
        }
    }
}

/* Shared IRQ for lines 10–15 */
void EXTI15_10_IRQHandler(void)
{
    for (u8 line = 10; line <= 15; line++)
    {
        if (MEXTI->PR & (1 << line))
        {
            MEXTI_HandleLine(line);
        }
    }
}
