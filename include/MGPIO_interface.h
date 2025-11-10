/*
 * MGPIO_interface.h
 *
 *  Created on: Jul 25, 2025
 *      Author: march
 */

#ifndef MGPIO_INTERFACE_H_
#define MGPIO_INTERFACE_H_

/*Define Ports A,B,C*/
typedef enum{
	PORTA=0,
	PORTB,
	PORTC
}PORTS;

/*Define Pins*/
typedef enum{
	PIN0=0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	PIN8,
	PIN9,
	PIN10,
	PIN11,
	PIN12,
	PIN13,
	PIN14,
	PIN15

}PINS;


/*Define Modes*/
typedef enum{
	INPUT=0,
	OUTPUT,
	ALTERNATE_FUNC,
	ANALOG

}MODES;

/*Define Output Types*/
typedef enum{
	PUSH_PULL=0,
	OPEN_DRAIN

}TYPES;

/*Define Speeds*/
typedef enum{
	LOW_SPEED=0,
	MEDIUM_SPEED,
	HIGH_SPEED,
	VERY_HIGH_SPEED
}SPEED;

/*Define Pin Value*/
typedef enum{
	PIN_LOW=0,
	PIN_HIGH
}PIN_VALUE;

/*Define Input Modes*/
typedef enum{
	FLOATING=0,
	PULL_UP,
	PULL_DOWN
}INPUT_MODES;

/*Define Alternate Functions*/
typedef enum{
	AF0=0,
	AF1,
	AF2,
	AF3,
	AF4,
	AF5,
	AF6,
	AF7,
	AF8,
	AF9,
	AF10,
	AF11,
	AF12,
	AF13,
	AF14,
	AF15

}AF;

void MGPIO_voidSetPinMode(PORTS Copy_uddtPort,PINS Copy_uddtPIN, MODES Copy_uddtMode);

/*================================================================================*/
/*=================================OUTPUT=========================================*/
void MGPIO_voidSetOutputConfig(PORTS Copy_uddtPort,PINS Copy_uddtPIN, TYPES Copy_uddtType, SPEED Copy_uddtSpeed);
void MGPIO_voidSetPinValue(PORTS Copy_uddtPort,PINS Copy_uddtPIN, PIN_VALUE Copy_uddtValue);
void MGPIO_voidSetAtomicPinValue(PORTS Copy_uddtPort,PINS Copy_uddtPIN, PIN_VALUE Copy_uddtValue);

/*=================================================================================*/
/*=================================INPUT===========================================*/
void MGPIO_voidSetInputConfig(PORTS Copy_uddtPort,PINS Copy_uddtPIN, INPUT_MODES Copy_uddtInputMode);
u8 MGPIO_voidGetPinValue(PORTS Copy_uddtPort,PINS Copy_uddtPIN);

/*=================================================================================*/
/*=================================ALTERNATE FUNC==================================*/
void MGPIO_voidSetAlternatFuncConfig(PORTS Copy_uddtPort,PINS Copy_uddtPIN, AF Copy_uddtAlternateFunc);

#endif /* MGPIO_INTERFACE_H_ */
