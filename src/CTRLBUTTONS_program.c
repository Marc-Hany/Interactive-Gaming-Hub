/*
 * CTRLBUTTONS_program.c
 *
 *  Created on: Nov 10, 2025
 *      Author: march
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MGPIO_interface.h"
#include "HBUTTON_interface.h"
#include "CTRLBUTTONS_config.h"
#include "CTRLBUTTONS_interface.h"
#include "SYSTICK_interface.h"

CTRL_BUTTONS Button_pressed=NONE;
u32  lastPressTime = 0;
void CTRLBUTTONS_voidInit(void)
{
	HBUTTON_voidInit(BUTTONS_PORT,UP,UP_Callback);
	HBUTTON_voidInit(BUTTONS_PORT,DOWN,DOWN_Callback);
	HBUTTON_voidInit(BUTTONS_PORT,RIGHT,RIGHT_Callback);
	HBUTTON_voidInit(BUTTONS_PORT,LEFT,LEFT_Callback);
	HBUTTON_voidInit(BUTTONS_PORT,OK,OK_Callback);
}

CTRL_BUTTONS UP_Callback(void)
{
	u32 now=SYSTICK_u32GetElapsedTime();
	if(now-lastPressTime>20)
	{
		Button_pressed=UP;
		lastPressTime = now;
	}
//	Button_pressed=UP;
	return Button_pressed;
}

CTRL_BUTTONS DOWN_Callback(void)
{
	u32 now=SYSTICK_u32GetElapsedTime();
	if(now-lastPressTime>20)
	{
		Button_pressed=DOWN;
		lastPressTime = now;
	}
//	Button_pressed=DOWN;
	return Button_pressed;
}

CTRL_BUTTONS RIGHT_Callback(void)
{
	u32 now=SYSTICK_u32GetElapsedTime();
	if(now-lastPressTime>20)
	{
		Button_pressed=RIGHT;
		lastPressTime = now;
	}
//	Button_pressed=RIGHT;
	return Button_pressed;
}

CTRL_BUTTONS LEFT_Callback(void)
{
	u32 now=SYSTICK_u32GetElapsedTime();
	if(now-lastPressTime>20)
	{
		Button_pressed=LEFT;
		lastPressTime = now;
	}
//	Button_pressed=LEFT;
	return Button_pressed;
}

CTRL_BUTTONS OK_Callback(void)
{
	u32 now=SYSTICK_u32GetElapsedTime();
	if(now-lastPressTime>20)
	{
		Button_pressed=OK;
		lastPressTime = now;
	}
//	Button_pressed=OK;
	return Button_pressed;
}
