
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MGPIO_interface.h"

#include "HDAC_config.h"
#include "HDAC_private.h"
#include "HDAC_interface.h"


void HDAC_voidInit(void)
{
	for(u8 i=8;i<16;i++)
	{
		MGPIO_voidSetPinMode(HDAC_PORT,i,OUTPUT);
		MGPIO_voidSetOutputConfig(HDAC_PORT,i,PUSH_PULL,LOW_SPEED);
	}
}
void HDAC_voidSendSample(u8 Copy_u8Sample)
{
	for(u8 i=8;i<16;i++)
	{
		MGPIO_voidSetPinValue(HDAC_PORT,i,GET_BIT(Copy_u8Sample,i-8));
	}
}
