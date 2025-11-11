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

u8 Button_pressed=NONE;
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
	Button_pressed=UP;
	return Button_pressed;
}

CTRL_BUTTONS DOWN_Callback(void)
{
	Button_pressed=DOWN;
	return Button_pressed;
}

CTRL_BUTTONS RIGHT_Callback(void)
{
	Button_pressed=RIGHT;
	return Button_pressed;
}

CTRL_BUTTONS LEFT_Callback(void)
{
	Button_pressed=LEFT;
	return Button_pressed;
}

CTRL_BUTTONS OK_Callback(void)
{
	Button_pressed=OK;
	return Button_pressed;
}
