/*
 * CTRLBUTTONS_interface.h
 *
 *  Created on: Nov 10, 2025
 *      Author: march
 */

#ifndef CTRLBUTTONS_INTERFACE_H_
#define CTRLBUTTONS_INTERFACE_H_

typedef enum
{
	UP=0,
	DOWN,
	LEFT,
	RIGHT,
	OK,
	NONE
}CTRL_BUTTONS;

void CTRLBUTTONS_voidInit(void);
CTRL_BUTTONS UP_Callback(void);
CTRL_BUTTONS DOWN_Callback(void);
CTRL_BUTTONS RIGHT_Callback(void);
CTRL_BUTTONS LEFT_Callback(void);
CTRL_BUTTONS OK_Callback(void);


#endif /* CTRLBUTTONS_INTERFACE_H_ */
