/*
 * MEXTI_interface.h
 *
 *  Created on: Aug 2, 2025
 *      Author: march
 */

#ifndef MEXTI_INTERFACE_H_
#define MEXTI_INTERFACE_H_

typedef enum
{
	EXTI_LINE0=0,
	EXTI_LINE1,
	EXTI_LINE2,
	EXTI_LINE3,
	EXTI_LINE4,
	EXTI_LINE5,
	EXTI_LINE6,
	EXTI_LINE7,
	EXTI_LINE8,
	EXTI_LINE9,
	EXTI_LINE10,
	EXTI_LINE11,
	EXTI_LINE12,
	EXTI_LINE13,
	EXTI_LINE14,
	EXTI_LINE15

}MEXTI_LINES;

typedef enum
{
	EXTI_RISING_EDGE=0,
	EXTI_FALLING_EDGE,
	EXTI_ON_CHANGE

}TRIGGER_EVENTS;

typedef enum
{
	EXTI_PORTA=0,
	EXTI_PORTB,
	EXTI_PORTC
}MEXTI_PORTS;

void MEXTI_voidEnable(MEXTI_LINES Copy_uddtInterruptLine);
void MEXTI_voidDisable(MEXTI_LINES Copy_uddtInterruptLine);

void MEXTI_voidSetTriggerEvent(MEXTI_LINES Copy_uddtInterruptLine,TRIGGER_EVENTS Copy_uddtTriggerEvent);
void MEXTI_voidSelectPort(MEXTI_LINES Copy_uddtInterruptLine,MEXTI_PORTS Copy_uddtLinePort);

void MEXTI_voidSetCallback(MEXTI_LINES line, void (*callback)(void));
void MEXTI_HandleLine(u8 line);

#endif /* MEXTI_INTERFACE_H_ */
