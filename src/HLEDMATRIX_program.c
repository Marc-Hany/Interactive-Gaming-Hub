/*
 * HLEDMATRIX_program.c
 *
 *  Created on: Aug 8, 2025
 *      Author: march
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MGPIO_interface.h"
#include "SYSTICK_interface.h"

#include "HLEDMATRIX_config.h"
#include "HLEDMATRIX_interface.h"
#include "HLEDMATRIX_private.h"


u8 Display[8]={0, 0, 0, 0, 0, 0, 0, 0};
u8 Copy_u8Col=0b00000001;
u8 ij=0;

void HLEDMATRIX_voidSetDisplay(u8 Copy_u8Display[])
{
	for(u8 i=0;i<8;i++)
	{
		Display[i]=Copy_u8Display[i];
	}
}
void HLEDMATRIX_voidInit(void)
{
	/*Define Pins Configuration*/
	/*ROWS*/
	for(int i=0;i<8;i++)
	{
		MGPIO_voidSetPinMode(PORTA,i,OUTPUT);
		MGPIO_voidSetOutputConfig(PORTA,i,PUSH_PULL,LOW_SPEED);
	}
	/*COLUMNS*/
	for(int i=0;i<11;i++)	//There is no pin PB11 in Blackpill
	{
		if ((i==3)||(i==4)||(i==5))	//not preferred to use these 3 pins so we bypass them
		{
			continue;
		}
		MGPIO_voidSetPinMode(PORTB,i,OUTPUT);
		MGPIO_voidSetOutputConfig(PORTB,i,PUSH_PULL,LOW_SPEED);
		MGPIO_voidSetPinValue(PORTB,i,PIN_HIGH);	//Deactivate Column
	}
}

void HLEDMATRIX_voidInitSTP(void)
{
	/*Define Pins Configuration*/
	MGPIO_voidSetPinMode(SERIAL_PORT,SERIAL_PIN,OUTPUT);
	MGPIO_voidSetOutputConfig(SERIAL_PORT,SERIAL_PIN,PUSH_PULL,LOW_SPEED);

	MGPIO_voidSetPinMode(CLK_PORT,CLK_PIN,OUTPUT);
	MGPIO_voidSetOutputConfig(CLK_PORT,CLK_PIN,PUSH_PULL,LOW_SPEED);

	MGPIO_voidSetPinMode(LATCH_PORT,LATCH_PIN,OUTPUT);
	MGPIO_voidSetOutputConfig(LATCH_PORT,LATCH_PIN,PUSH_PULL,LOW_SPEED);
}

void HLEDMATRIX_voidDisplay(u8 *Copy_pu8Shape)
{
	u8 k=0;
	/*Loop on columns*/
	for (int i=0;i<11;i++)
	{
		if ((i==3)||(i==4)||(i==5))	//not preferred to use these 3 pins so we bypass them
		{
			continue;
		}
		/*Set the value on row*/
		for (int j=0;j<8;j++)
		{
			MGPIO_voidSetPinValue(PORTA,j,GET_BIT(Copy_pu8Shape[k],j));
		}
		/*Activate Column*/
		MGPIO_voidSetPinValue(PORTB,i,PIN_LOW);
		/*Delay*/
		SYSTICK_voidDelay_us(2500);
		/*Deactivate Column*/
		MGPIO_voidSetPinValue(PORTB,i,PIN_HIGH);
		k++;
	}

}

void HLEDMATRIX_voidDisplaySTP(u8 *Copy_pu8Shape,u8 Copy_u8Col)
{
	/*Loop on columns*/
	for (int i=0;i<8;i++)
	{
		/*Set the value on row*/
		HLEDMATRIX_voidOutputSTP(SERIAL_PORT,SERIAL_PIN,CLK_PORT,CLK_PIN,LATCH_PORT,LATCH_PIN,Copy_pu8Shape[i],Copy_u8Col);
		Copy_u8Col<<=1;
		/*Delay*/
		SYSTICK_voidDelay_us(500);
	}

}

void HLEDMATRIX_voidPulse(u8 Copy_u8ClkPort,u8 Copy_u8ClkPin)
{
	MGPIO_voidSetPinValue(Copy_u8ClkPort,Copy_u8ClkPin,PIN_HIGH);
//	SYSTICK_voidDelay_us(100);
//	for(volatile u8 j=0;j<50;j++);
	MGPIO_voidSetPinValue(Copy_u8ClkPort,Copy_u8ClkPin,PIN_LOW);
}

void HLEDMATRIX_voidOutputSTP(u8 Copy_u8SerialPort,u8 Copy_u8SerialPin,
						u8 Copy_u8ClkPort,u8 Copy_u8ClkPin,
						u8 Copy_u8LatchPort,u8 Copy_u8LatchPin,
						u8 Copy_u8Row,u8 Copy_u8Col)
{
	u16 Byte= ((u16)Copy_u8Row<< 8) | Copy_u8Col;
	for(int i=15;i>=0;i--)
	{
		MGPIO_voidSetPinValue(Copy_u8SerialPort,Copy_u8SerialPin,GET_BIT(Byte,i));
		HLEDMATRIX_voidPulse(Copy_u8ClkPort,Copy_u8ClkPin);

	}


	HLEDMATRIX_voidPulse(Copy_u8LatchPort,Copy_u8LatchPin);

}



void HLEDMATRIX_OS(void)
{
	HLEDMATRIX_voidOutputSTP(PORTB,PIN5,PORTB,PIN6,PORTB,PIN7,Display[ij], Copy_u8Col);

	Copy_u8Col <<= 1;
	if(Copy_u8Col == 0) Copy_u8Col = 0b00000001;

	ij++;
	if(ij == 8) ij = 0;

}
