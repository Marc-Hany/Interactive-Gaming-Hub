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
#include "HTFT_private.h"
#include "HTFT_config.h"
#include "HTFT_interface.h"
#include "MSPI_interface.h"
#include "HSD_interface.h"


void HTFT_voisCSLow(void)
{
	MGPIO_voidSetPinValue(HTFT_PORT,HTFT_CS,PIN_LOW);
}

void HTFT_voisCSHigh(void)
{
	MGPIO_voidSetPinValue(HTFT_PORT,HTFT_CS,PIN_HIGH);
}

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
void HTFT_voidDisplayImage(const u8* Copy_u16ImageArr)
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

	for(u16 i=0;i<40960;i+=2)
	{
		Local_u8High=(u8)(Copy_u16ImageArr[i]);
		Local_u8Low =(u8)(Copy_u16ImageArr[i+1]);
		HTFT_voidSendData(Local_u8High);
		HTFT_voidSendData(Local_u8Low);
	}
}

void HTFT_voidDrawShape(const u16* Copy_u16ImageArr,const u8* Copy_u16BckgArr,u8 Copy_u8StartX, u8 Copy_u8EndX, u8 Copy_u8StartY, u8 Copy_u8EndY)
{
	u8 Local_u8High;	//MSB of data u16
	u8 Local_u8Low;		//LSB of data u16
	u16 color=0;
	u16 width =(Copy_u8EndX-Copy_u8StartX)+1;
	u16 height=(Copy_u8EndY-Copy_u8StartY)+1;

	/*Set X Position*/
	HTFT_voidSendCommand(0x2A);	//Set X Position
	HTFT_voidSendData(0);		//Start Position
	HTFT_voidSendData(Copy_u8StartX);		//Start Position
	HTFT_voidSendData(0);		//End Position
	HTFT_voidSendData(Copy_u8EndX);		//End Position

	/*Set Y Position*/
	HTFT_voidSendCommand(0x2B);	//Set X Position
	HTFT_voidSendData(0);		//Start Position
	HTFT_voidSendData(Copy_u8StartY);		//Start Position
	HTFT_voidSendData(0);		//End Position
	HTFT_voidSendData(Copy_u8EndY);		//End Position

	/*Global Position*/
	volatile u8 X_global;
	volatile u8 Y_global;
	volatile u16 Global_Index;
	volatile u16 Local_Index;
	volatile u16 counter=0;

	/*Send Data*/
	HTFT_voidSendCommand(0x2C);
	for(u8 Y=0;Y<height;Y++)
	{
		for(u8 X=0;X<width;X+=2)
		{
			Local_Index=(width*Y)+X;
			Local_u8High=(u8)(Copy_u16ImageArr[Local_Index]<<8);
			Local_u8Low =(u8)(Copy_u16ImageArr[Local_Index]);
			color=(Local_u8High<<8) | Local_u8Low;
			if(color == TRANSPARENT)
			{
				X_global=Copy_u8StartX+X;
				Y_global=Copy_u8StartY+Y;
				Global_Index=(Y_global*128)+X_global;
				Local_u8High=(u8)(Copy_u16BckgArr[Global_Index]);
				Local_u8Low =(u8)(Copy_u16BckgArr[Global_Index+1]);

			}
			HTFT_voidSendData(Local_u8High);
			HTFT_voidSendData(Local_u8Low);
			counter++;
		}
	}
	counter=0;
}

void HTFT_voidSDDrawShape(const u16* Copy_u16BckgArr,
                          u8 Copy_u8StartX,
                          u8 Copy_u8StartY,
                          u8 Copy_u8Width,
                          u8 Copy_u8Height,
                          u16 Copy_u16StartBlock)
{
    u8 Buffer[512];  // SD block buffer
    u16 byteIndex = 0;
    u16 pixelIndexInBlock = 0;
    u16 color;
    u8 Local_u8High, Local_u8Low;

    u8 EndX = Copy_u8StartX + Copy_u8Width - 1;
    u8 EndY = Copy_u8StartY + Copy_u8Height - 1;

    // Set X Position
    HTFT_voidSendCommand(0x2A);
    HTFT_voidSendData(0);
    HTFT_voidSendData(Copy_u8StartX);
    HTFT_voidSendData(0);
    HTFT_voidSendData(EndX);

    // Set Y Position
    HTFT_voidSendCommand(0x2B);
    HTFT_voidSendData(0);
    HTFT_voidSendData(Copy_u8StartY);
    HTFT_voidSendData(0);
    HTFT_voidSendData(EndY);

    // Send Memory Write Command
    HTFT_voidSendCommand(0x2C);

    // Read first block
    HSD_voidReadBlock(Copy_u16StartBlock, Buffer);
    pixelIndexInBlock = 0;

    for(u8 Y = 0; Y < Copy_u8Height; Y++)
    {
        for(u8 X = 0; X < Copy_u8Width; X++)
        {
            // Load new block if we reached end of current block
            if(pixelIndexInBlock >= 256)  // 512 bytes / 2 bytes per pixel
            {
                Copy_u16StartBlock++;
                HSD_voidReadBlock(Copy_u16StartBlock, Buffer);
                pixelIndexInBlock = 0;
            }

            byteIndex = pixelIndexInBlock * 2;
            Local_u8High = Buffer[byteIndex];
            Local_u8Low  = Buffer[byteIndex + 1];
            color = (Local_u8High << 8) | Local_u8Low;

            if(color == TRANSPARENT)
            {
                u16 Global_Index = (Copy_u8StartY + Y) * 128 + (Copy_u8StartX + X);
                Local_u8High = (u8)(Copy_u16BckgArr[Global_Index] >> 8);
                Local_u8Low  = (u8)(Copy_u16BckgArr[Global_Index]);
            }

            HTFT_voidSendData(Local_u8High);
            HTFT_voidSendData(Local_u8Low);

            pixelIndexInBlock++;
        }
    }
}
