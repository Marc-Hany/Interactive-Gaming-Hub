/*
 * HBUTTON_program.c
 *
 *  Created on: Nov 8, 2025
 *      Author: march
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MGPIO_interface.h"
#include "NVIC_interface.h"
#include "SCB_interface.h"
#include "MEXTI_interface.h"


#include "HBUTTON_private.h"
#include "HBUTTON_config.h"
#include "HBUTTON_interface.h"

void HBUTTON_voidInit(PORTS Copy_uddtPort,PINS Copy_uddtPIN,void (*callback)(void))
{
	/*Initialize Pin*/
	MGPIO_voidSetPinMode(Copy_uddtPort,Copy_uddtPIN,INPUT);
	MGPIO_voidSetInputConfig(Copy_uddtPort,Copy_uddtPIN, PULL_DOWN);

	/*Initialize Interrupt*/
	MEXTI_voidSelectPort(Copy_uddtPIN,Copy_uddtPort);
	MEXTI_voidSetTriggerEvent(Copy_uddtPIN,EXTI_FALLING_EDGE);
	MEXTI_voidEnable(Copy_uddtPIN);

	u8 EXTI_LINE=0;
	if(Copy_uddtPIN==0)
	{
		EXTI_LINE=EXTI0;
	}
	else if(Copy_uddtPIN==1)
	{
		EXTI_LINE=EXTI1;
	}
	else if(Copy_uddtPIN==2)
	{
		EXTI_LINE=EXTI2;
	}
	else if(Copy_uddtPIN==3)
	{
		EXTI_LINE=EXTI3;
	}
	else if(Copy_uddtPIN==4)
	{
		EXTI_LINE=EXTI4;
	}
	else if(Copy_uddtPIN>=5 && Copy_uddtPIN <= 9)
	{
		EXTI_LINE=EXTI9_5;
	}
	else if(Copy_uddtPIN>=10 && Copy_uddtPIN <= 15)
	{
		EXTI_LINE=EXTI15_10;
	}

	NVIC_voidEnable(EXTI_LINE);	//Enable EXTI0, Number 6 in vectored table
	MEXTI_voidSetCallback(Copy_uddtPIN,callback);
}

