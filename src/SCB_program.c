/*
 * SCB_program.c
 *
 *  Created on: Aug 1, 2025
 *      Author: march
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SCB_config.h"
#include "SCB_interface.h"
#include "SCB_private.h"


/*
 * SCB_program.c
 *
 *  Created on: Aug 1, 2025
 *      Author: march
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SCB_config.h"
#include "SCB_interface.h"
#include "SCB_private.h"

#include "Shared_Resources.h"




void SCB_voidSetGroupConfiguration(u8 Copy_u8GroupConfig)
{
	u32 Local_GroupConfig=SCB->AIRCR;
	Local_GroupConfig &= ~(7<<8);
	Local_GroupConfig |= (GROUP_CONFIGURATION<<8);
	Local_GroupConfig &= (0x0000FFFF);
	Local_GroupConfig |= (0x5FA<<16);

	SCB->AIRCR=Local_GroupConfig;
}
