/*
 * HTFT_program.c
 *
 *  Created on: Sep 5, 2025
 *      Author: march
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include <stdio.h>
#include <stdlib.h>

#include "SYSTICK_interface.h"
#include "MGPIO_interface.h"
#include "MSPI_interface.h"

#include "HTFT_private.h"
#include "HTFT_config.h"
#include "HTFT_interface.h"

void HTFT_voidInit(void)
{

	/*Initialize Reset Pin*/
	MGPIO_voidSetPinMode(HTFT_PORT,HTFT_RST,OUTPUT);
	MGPIO_voidSetOutputConfig(HTFT_PORT,HTFT_RST,PUSH_PULL,LOW_SPEED);
	/*Initialize Control (A0) Pin*/
	MGPIO_voidSetPinMode(HTFT_PORT,HTFT_A0,OUTPUT);
	MGPIO_voidSetOutputConfig(HTFT_PORT,HTFT_A0,PUSH_PULL,LOW_SPEED);

	/*Initialize Control (A0) Pin*/
	MGPIO_voidSetPinMode(HTFT_PORT,PIN8,OUTPUT);
	MGPIO_voidSetOutputConfig(HTFT_PORT,PIN8,PUSH_PULL,LOW_SPEED);

	/*Initialize Control (CS) Pin*/
	MGPIO_voidSetPinMode(HTFT_PORT,HTFT_CS,OUTPUT);
	MGPIO_voidSetOutputConfig(HTFT_PORT,HTFT_CS,PUSH_PULL,LOW_SPEED);
	MGPIO_voidSetPinValue(HTFT_PORT,HTFT_CS,PIN_LOW);

	/*Initialize Systick and SPI*/
	SYSTCICK_voidInit();

	/*Reset Sequence*/
	MGPIO_voidSetPinValue(HTFT_PORT,HTFT_RST,PIN_HIGH);
	SYSTICK_voidDelay_us(100);
	MGPIO_voidSetPinValue(HTFT_PORT,HTFT_RST,PIN_LOW);
	SYSTICK_voidDelay_us(1);
	MGPIO_voidSetPinValue(HTFT_PORT,HTFT_RST,PIN_HIGH);
	SYSTICK_voidDelay_us(100);
	MGPIO_voidSetPinValue(HTFT_PORT,HTFT_RST,PIN_LOW);
	SYSTICK_voidDelay_us(100);
	MGPIO_voidSetPinValue(HTFT_PORT,HTFT_RST,PIN_HIGH);
	SYSTICK_voidDelay_ms(120);

	/*Sleep Out*/
	HTFT_voidSendCommand(0x11);
	SYSTICK_voidDelay_ms(10);

	/*Color Code Selection*/
	HTFT_voidSendCommand(0x3A);
	HTFT_voidSendData(HTFT_565);

	/*Display ON*/
	HTFT_voidSendCommand(0x029);
}
void HTFT_voidSendData(u8 Copy_u8Data)
{
	/*Control Pin High*/
	MGPIO_voidSetPinValue(HTFT_PORT,HTFT_A0,PIN_HIGH);

	/*Send Data Using SPI*/
	MSPI_u8Transceive(Copy_u8Data);
}
void HTFT_voidSendCommand(u8 Copy_u8Command)
{
	/*Control Pin Low*/
	MGPIO_voidSetPinValue(HTFT_PORT,HTFT_A0,PIN_LOW);

	/*Send Data Using SPI*/
	MSPI_u8Transceive(Copy_u8Command);
	MGPIO_voidSetPinValue(HTFT_PORT,PIN8,PIN_HIGH);
}
void HTFT_voidDisplayImage(u16* Copy_u16ImageArr)
{
	u8 Local_u8High;	//MSB of data u16
	u8 Local_u8Low;		//LSB of data u16

	/*Set X Position*/
	HTFT_voidSendCommand(0x2A);	//Set X Position
	HTFT_voidSendData(0);		//Start Position
	HTFT_voidSendData(0);		//Start Position
	HTFT_voidSendData(0);		//End Position
	HTFT_voidSendData(127);		//End Position

	/*Set Y Position*/
	HTFT_voidSendCommand(0x2B);	//Set X Position
	HTFT_voidSendData(0);		//Start Position
	HTFT_voidSendData(0);		//Start Position
	HTFT_voidSendData(0);		//End Position
	HTFT_voidSendData(159);		//End Position

	/*Send Data*/
	HTFT_voidSendCommand(0x2C);

	for(u16 i=0;i<20480;i++)
	{
		Local_u8High=(u8)(Copy_u16ImageArr[i]>>8);
		Local_u8Low =(u8)(Copy_u16ImageArr[i]);
		HTFT_voidSendData(Local_u8High);
		HTFT_voidSendData(Local_u8Low);
	}
}

void HTFT_voidDrawShape(Sprite_t Sprite,const u16* Copy_u16BckgArr)
{
	u8  Local_u8StartX=Sprite.X_start;
	u8  Local_u8EndX  =Sprite.X_end;
	u8  Local_u8StartY=Sprite.Y_start;
	u8  Local_u8EndY  =Sprite.Y_end;
	const u16* Local_u16ImageArr=Sprite.Copy_u16ImageArr;

	u8 Local_u8High;	//MSB of data u16
	u8 Local_u8Low;		//LSB of data u16
	u16 color=0;
	u16 width =(Local_u8EndX-Local_u8StartX)+1;
	u16 height=(Local_u8EndY-Local_u8StartY)+1;

	/*Set X Position*/
	HTFT_voidSendCommand(0x2A);	//Set X Position
	HTFT_voidSendData(0);		//Start Position
	HTFT_voidSendData(Local_u8StartX);		//Start Position
	HTFT_voidSendData(0);		//End Position
	HTFT_voidSendData(Local_u8EndX);		//End Position

	/*Set Y Position*/
	HTFT_voidSendCommand(0x2B);	//Set X Position
	HTFT_voidSendData(0);		//Start Position
	HTFT_voidSendData(Local_u8StartY);		//Start Position
	HTFT_voidSendData(0);		//End Position
	HTFT_voidSendData(Local_u8EndY);		//End Position

	/*Global Position*/
	volatile u8 X_global;
	volatile u8 Y_global;
	volatile u16 Global_Index;
	volatile u16 Local_Index;

	/*Send Data*/
	HTFT_voidSendCommand(0x2C);
	for(u8 Y=0;Y<height;Y++)
	{
		for(u8 X=0;X<width;X++)
		{
			Local_Index=(width*Y)+X;
			Local_u8High=(u8)(Local_u16ImageArr[Local_Index]>>8);
			Local_u8Low =(u8)(Local_u16ImageArr[Local_Index]);
			color=(Local_u8High<<8) | Local_u8Low;
			if(color == TRANSPARENT)
			{
				X_global=Local_u8StartX+X;
				Y_global=Local_u8StartY+Y;
				Global_Index=(Y_global*128)+X_global;
				Local_u8High=(u8)(Copy_u16BckgArr[Global_Index]>>8);
				Local_u8Low =(u8)(Copy_u16BckgArr[Global_Index]);

			}
			HTFT_voidSendData(Local_u8High);
			HTFT_voidSendData(Local_u8Low);
		}
	}
}

void HTFT_voidDrawShapeBackgroundUpdate(Sprite_t Sprite,const u16* Copy_u16BckgArr,u16* Copy_u16BckgArr2)
{
	for(u16 i=0;i<20480;i++)
	{
		Copy_u16BckgArr2[i]=Copy_u16BckgArr[i];
	}

	u8  Local_u8StartX=Sprite.X_start;
	u8  Local_u8EndX  =Sprite.X_end;
	u8  Local_u8StartY=Sprite.Y_start;
	u8  Local_u8EndY  =Sprite.Y_end;
	const u16* Local_u16ImageArr=Sprite.Copy_u16ImageArr;

	u8 Local_u8High;	//MSB of data u16
	u8 Local_u8Low;		//LSB of data u16
	volatile u16 color=0;
	u16 width =(Local_u8EndX-Local_u8StartX)+1;
	u16 height=(Local_u8EndY-Local_u8StartY)+1;

	/*Set X Position*/
	HTFT_voidSendCommand(0x2A);	//Set X Position
	HTFT_voidSendData(0);		//Start Position
	HTFT_voidSendData(Local_u8StartX);		//Start Position
	HTFT_voidSendData(0);		//End Position
	HTFT_voidSendData(Local_u8EndX);		//End Position

	/*Set Y Position*/
	HTFT_voidSendCommand(0x2B);	//Set X Position
	HTFT_voidSendData(0);		//Start Position
	HTFT_voidSendData(Local_u8StartY);		//Start Position
	HTFT_voidSendData(0);		//End Position
	HTFT_voidSendData(Local_u8EndY);		//End Position

	/*Global Position*/
	volatile u8 X_global;
	volatile u8 Y_global;
	volatile u16 Global_Index;
	volatile u16 Local_Index;

	/*Send Data*/
	HTFT_voidSendCommand(0x2C);
	for(u8 Y=0;Y<height;Y++)
	{
		for(u8 X=0;X<width;X++)
		{
			X_global=Local_u8StartX+X;
			Y_global=Local_u8StartY+Y;
			Global_Index=(Y_global*128)+X_global;
			Local_Index=(width*Y)+X;
			Local_u8High=(u8)(Local_u16ImageArr[Local_Index]>>8);
			Local_u8Low =(u8)(Local_u16ImageArr[Local_Index]);
			color=(Local_u8High<<8) | Local_u8Low;
			if(color == TRANSPARENT)
			{
				Local_u8High=(u8)(Copy_u16BckgArr[Global_Index]>>8);
				Local_u8Low =(u8)(Copy_u16BckgArr[Global_Index]);
				color=(Local_u8High<<8) | Local_u8Low;
			}
			Copy_u16BckgArr2[Global_Index]=color;
			HTFT_voidSendData(Local_u8High);
			HTFT_voidSendData(Local_u8Low);
		}
	}
}
