/*
 * NVIC_program.c
 *
 *  Created on: Aug 1, 2025
 *      Author: march
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "NVIC_config.h"
#include "NVIC_interface.h"
#include "NVIC_private.h"

#include "SCB_config.h"
#include "SCB_interface.h"
#include "SCB_private.h"

#include "Shared_Resources.h"



void NVIC_voidEnable(u8 Copy_u8Position)
{
	SET_BIT(NVIC->ISER[Copy_u8Position/32],Copy_u8Position%32);
}
void NVIC_voidDisable(u8 Copy_u8Position)
{
	SET_BIT(NVIC->ICER[Copy_u8Position/32],Copy_u8Position%32);
}

void NVIC_voidPendingEnable(u8 Copy_u8Position)
{
	SET_BIT(NVIC->ISPR[Copy_u8Position/32],Copy_u8Position%32);
}
void NVIC_voidPendingDisable(u8 Copy_u8Position)
{
	SET_BIT(NVIC->ICPR[Copy_u8Position/32],Copy_u8Position%32);
}

void NVIC_voidSetGroupPriority(u8 Copy_u8Position,u8 Copy_u8Group, u8 Copy_u8SubGroup)
{
	switch(GROUP_CONFIGURATION)
	{
	case GROUP16SUB0:
		NVIC->IPR[Copy_u8Position]&=~(15<<4);
		NVIC->IPR[Copy_u8Position]|=(Copy_u8Group<<4);
		break;
	case GROUP8SUB2:
		NVIC->IPR[Copy_u8Position]&=~(15<<4);
		NVIC->IPR[Copy_u8Position]|=(Copy_u8Group<<5)|(Copy_u8SubGroup<<4);
		break;
	case GROUP4SUB4:
		NVIC->IPR[Copy_u8Position]&=~(15<<4);
		NVIC->IPR[Copy_u8Position]|=(Copy_u8Group<<6)|(Copy_u8SubGroup<<4);
		break;
	case GROUP2SUB8:
		NVIC->IPR[Copy_u8Position]&=~(15<<5);
		NVIC->IPR[Copy_u8Position]|=(Copy_u8Group<<7)|(Copy_u8SubGroup<<4);
		break;
	case GROUP1SUB16:
		NVIC->IPR[Copy_u8Position]&=~(15<<5);
		NVIC->IPR[Copy_u8Position]|=(Copy_u8SubGroup<<4);
		break;
	}

}

u8 NVIC_u8ReadActiveFlag(u8 Copy_u8Position)
{
	return GET_BIT(NVIC->IABR[Copy_u8Position/32],Copy_u8Position%32);
}
