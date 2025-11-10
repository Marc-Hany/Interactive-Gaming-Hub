/*
 * MGPIO_program.c
 *
 *  Created on: Jul 25, 2025
 *      Author: march
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MGPIO_config.h"
#include "MGPIO_private.h"
#include "MGPIO_interface.h"



void MGPIO_voidSetPinMode(PORTS Copy_uddtPort,PINS Copy_uddtPIN, MODES Copy_uddtMode)
{
	switch(Copy_uddtPort)
	{
		case PORTA:
			GPIOA->MODER &=~(3<<(Copy_uddtPIN*2));				//Clear (Mask) the 2 bits i want to change
			GPIOA->MODER |= (Copy_uddtMode<<(Copy_uddtPIN*2));	//Set the masked bits with specified mode
			break;
		case PORTB:
			GPIOB->MODER &=~(3<<(Copy_uddtPIN*2));				//Clear (Mask) the 2 bits i want to change
			GPIOB->MODER |= (Copy_uddtMode<<(Copy_uddtPIN*2));	//Set the masked bits with specified mode
			break;
		case PORTC:
			GPIOC->MODER &=~(3<<(Copy_uddtPIN*2));				//Clear (Mask) the 2 bits i want to change
			GPIOC->MODER |= (Copy_uddtMode<<(Copy_uddtPIN*2));	//Set the masked bits with specified mode
			break;
	}
}

/*================================================================================*/
/*=================================OUTPUT=========================================*/
void MGPIO_voidSetOutputConfig(PORTS Copy_uddtPort,PINS Copy_uddtPIN, TYPES Copy_uddtType, SPEED Copy_uddtSpeed)
{
	switch(Copy_uddtPort)
		{
			case PORTA:
				/*Select Pin Type*/
				if(Copy_uddtType==PUSH_PULL)
				{
					CLR_BIT(GPIOA->OTYPER,Copy_uddtPIN);
				}
				else if(Copy_uddtType==OPEN_DRAIN)
				{
					SET_BIT(GPIOA->OTYPER,Copy_uddtPIN);
				}

				/*Set Speed*/
				GPIOA->OSPEEDR &=~(3<<(Copy_uddtPIN*2));				//Clear (Mask) the 2 bits i want to change
				GPIOA->OSPEEDR |= (Copy_uddtSpeed<<(Copy_uddtPIN));	   //Set the masked bits with specified speed
				break;
			case PORTB:
				/*Select Pin Type*/
				if(Copy_uddtType==PUSH_PULL)
				{
					CLR_BIT(GPIOB->OTYPER,Copy_uddtPIN);
				}
				else if(Copy_uddtType==OPEN_DRAIN)
				{
					SET_BIT(GPIOB->OTYPER,Copy_uddtPIN);
				}

				/*Set Speed*/
				GPIOB->OSPEEDR &=~(3<<(Copy_uddtPIN*2));				//Clear (Mask) the 2 bits i want to change
				GPIOB->OSPEEDR |= (Copy_uddtSpeed<<(Copy_uddtPIN));	    //Set the masked bits with specified speed
				break;
			case PORTC:
				/*Select Pin Type*/
				if(Copy_uddtType==PUSH_PULL)
				{
					CLR_BIT(GPIOC->OTYPER,Copy_uddtPIN);
				}
				else if(Copy_uddtType==OPEN_DRAIN)
				{
					SET_BIT(GPIOC->OTYPER,Copy_uddtPIN);
				}

				/*Set Speed*/
				GPIOC->OSPEEDR &=~(3<<(Copy_uddtPIN*2));				//Clear (Mask) the 2 bits i want to change
				GPIOC->OSPEEDR |= (Copy_uddtSpeed<<(Copy_uddtPIN));		//Set the masked bits with specified speed
				break;
		}
}
void MGPIO_voidSetPinValue(PORTS Copy_uddtPort,PINS Copy_uddtPIN, PIN_VALUE Copy_uddtValue)
{
	switch(Copy_uddtPort)
		{
			case PORTA:
				/*Set Output Value*/
				if(Copy_uddtValue==PIN_LOW)
				{
					CLR_BIT(GPIOA->ODR,Copy_uddtPIN);
				}
				else if(Copy_uddtValue==PIN_HIGH)
				{
					SET_BIT(GPIOA->ODR,Copy_uddtPIN);
				}
				break;
			case PORTB:
				if(Copy_uddtValue==PIN_LOW)
				{
					CLR_BIT(GPIOB->ODR,Copy_uddtPIN);
				}
				else if(Copy_uddtValue==PIN_HIGH)
				{
					SET_BIT(GPIOB->ODR,Copy_uddtPIN);
				}
				break;
			case PORTC:
				if(Copy_uddtValue==PIN_LOW)
				{
					CLR_BIT(GPIOC->ODR,Copy_uddtPIN);
				}
				else if(Copy_uddtValue==PIN_HIGH)
				{
					SET_BIT(GPIOC->ODR,Copy_uddtPIN);
				}
				break;
		}
}
void MGPIO_voidSetAtomicPinValue(PORTS Copy_uddtPort,PINS Copy_uddtPIN, PIN_VALUE Copy_uddtValue)
{
	switch(Copy_uddtPort)
		{
			case PORTA:
				/*Set Output Value*/
				if(Copy_uddtValue==PIN_HIGH)
				{
					GPIOA->BSRR=(1<<Copy_uddtPIN);	//Directly Set The Bit
				}
				else if(Copy_uddtValue==PIN_LOW)
				{
					GPIOA->BSRR=(1<<(Copy_uddtPIN+16));
				}
				break;
			case PORTB:
				if(Copy_uddtValue==PIN_HIGH)
				{
					GPIOB->BSRR=(1<<Copy_uddtPIN);	//Directly Set The Bit
				}
				else if(Copy_uddtValue==PIN_LOW)
				{
					GPIOB->BSRR=(1<<(Copy_uddtPIN+16));
				}
				break;
			case PORTC:
				if(Copy_uddtValue==PIN_HIGH)
				{
					GPIOC->BSRR=(1<<Copy_uddtPIN);	//Directly Set The Bit
				}
				else if(Copy_uddtValue==PIN_LOW)
				{
					GPIOC->BSRR=(1<<(Copy_uddtPIN+16));
				}
				break;
		}
}

/*=================================================================================*/
/*=================================INPUT===========================================*/
void MGPIO_voidSetInputConfig(PORTS Copy_uddtPort,PINS Copy_uddtPIN, INPUT_MODES Copy_uddtInputMode)
{
	switch(Copy_uddtPort)
	{
		case PORTA:
			GPIOA->PUPDR &=~(3<<(Copy_uddtPIN*2));				//Clear (Mask) the 2 bits i want to change
			GPIOA->PUPDR |= (Copy_uddtInputMode<<(Copy_uddtPIN*2));	//Set the masked bits with specified mode
			break;
		case PORTB:
			GPIOB->PUPDR &=~(3<<(Copy_uddtPIN*2));				//Clear (Mask) the 2 bits i want to change
			GPIOB->PUPDR |= (Copy_uddtInputMode<<(Copy_uddtPIN*2));	//Set the masked bits with specified mode
			break;
		case PORTC:
			GPIOC->PUPDR &=~(3<<(Copy_uddtPIN*2));				//Clear (Mask) the 2 bits i want to change
			GPIOC->PUPDR |= (Copy_uddtInputMode<<(Copy_uddtPIN*2));	//Set the masked bits with specified mode
			break;
	}
}
u8 MGPIO_voidGetPinValue(PORTS Copy_uddtPort,PINS Copy_uddtPIN)
{
	u8 Local_u8PinValue=0;
	switch(Copy_uddtPort)
	{
		case PORTA:
			Local_u8PinValue= GET_BIT(GPIOA->IDR,Copy_uddtPIN);
			break;
		case PORTB:
			Local_u8PinValue= GET_BIT(GPIOB->IDR,Copy_uddtPIN);
			break;
		case PORTC:
			Local_u8PinValue= GET_BIT(GPIOC->IDR,Copy_uddtPIN);
			break;
	}
	return Local_u8PinValue;
}

/*=================================================================================*/
/*=================================ALTERNATE FUNC==================================*/
void MGPIO_voidSetAlternatFuncConfig(PORTS Copy_uddtPort,PINS Copy_uddtPIN, AF Copy_uddtAlternateFunc)
{
	switch(Copy_uddtPort)
	{
		case PORTA:
			if(Copy_uddtPIN<8)
			{
				GPIOA->AFRL &=~(15<<(Copy_uddtPIN*4));						//Clear (Mask) the 2 bits i want to change
				GPIOA->AFRL |= (Copy_uddtAlternateFunc<<(Copy_uddtPIN*4));	//Set the masked bits with specified mode
			}
			else if(Copy_uddtPIN>=8 && Copy_uddtPIN<17)
			{
				Copy_uddtPIN-=8;											//Reset Pin Counter
				GPIOA->AFRH &=~(15<<(Copy_uddtPIN*4));						//Clear (Mask) the 2 bits i want to change
				GPIOA->AFRH |= (Copy_uddtAlternateFunc<<(Copy_uddtPIN*4));	//Set the masked bits with specified mode
			}
			break;
		case PORTB:
			if(Copy_uddtPIN<8)
			{
				GPIOB->AFRL &=~(15<<(Copy_uddtPIN*4));						//Clear (Mask) the 2 bits i want to change
				GPIOB->AFRL |= (Copy_uddtAlternateFunc<<(Copy_uddtPIN*4));	//Set the masked bits with specified mode
			}
			else if(Copy_uddtPIN>=8 && Copy_uddtPIN<17)
			{
				Copy_uddtPIN-=8;											//Reset Pin Counter
				GPIOB->AFRH &=~(15<<(Copy_uddtPIN*4));						//Clear (Mask) the 2 bits i want to change
				GPIOB->AFRH |= (Copy_uddtAlternateFunc<<(Copy_uddtPIN*4));	//Set the masked bits with specified mode
			}
			break;
		case PORTC:
			if(Copy_uddtPIN<8)
			{
				GPIOC->AFRL &=~(15<<(Copy_uddtPIN*4));						//Clear (Mask) the 2 bits i want to change
				GPIOC->AFRL |= (Copy_uddtAlternateFunc<<(Copy_uddtPIN*4));	//Set the masked bits with specified mode
			}
			else if(Copy_uddtPIN>=8 && Copy_uddtPIN<17)
			{
				Copy_uddtPIN-=8;											//Reset Pin Counter
				GPIOC->AFRH &=~(15<<(Copy_uddtPIN*4));						//Clear (Mask) the 2 bits i want to change
				GPIOC->AFRH |= (Copy_uddtAlternateFunc<<(Copy_uddtPIN*4));	//Set the masked bits with specified mode
			}
			break;
	}
}
