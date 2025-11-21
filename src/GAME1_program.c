/*
 * GAME1_program.c
 *
 *  Created on: Nov 21, 2025
 *      Author: march
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GAME1_Assets.h"
#include "GAME1_interface.h"
#include "HTFT_interface.h"
#include "OS_interface.h"
#include "CTRLBUTTONS_interface.h"

extern u8 Button_pressed;

static Sprite_t SelectBox=
{
		SELECTBOX30,
		19,
		48,
		15,
		44,
		Select_Box30
};

typedef enum
{
	Answer1=2016,
	Answer2=8016,
	Answer3=2061,
	Answer4=8061,
	N1=89,
	OP=58,
	N2=29

}POSITION;

static POSITION CurrentPosition=Answer1;

static Sprite_t Number=
{
		NUMBER,
		N1,
		98,
		104,
		133,
		One
};

static Sprite_t Operand=
{
		OPERAND,
		OP,
		67,
		104,
		133,
		Plus
};

volatile u8 X_start=0;
volatile u8 Y_start=0;

static void GAME1_voidUpdateXY(void)
{
	X_start=CurrentPosition/100;
	Y_start=CurrentPosition%100;
}

static void GAME1_voidUpdatePosition(void)
{
	CurrentPosition=((SelectBox.X_start+1)*100)+(SelectBox.Y_start+1);
}

void GAME1_voidGameStart(void)
{
	HTFT_voidDisplayImage(Board);
	HTFT_voidDrawShape(SelectBox,Board);
	HTFT_voidDrawShapeBackgroundUpdate(Number,Board,Board2);
	Number.X_start=N2;
	Number.X_end=N2+9;
	Number.Copy_u16ImageArr=Zero;
	HTFT_voidDrawShapeBackgroundUpdate(Number,Board2,Board2);
	HTFT_voidDrawShapeBackgroundUpdate(Operand,Board2,Board2);
	OS_voidTaskResume(2);
	OS_voidTaskSuspend(1);
}


void GAME1_voidGame1Navigation(void)
{
	switch(Button_pressed)
	{
	case UP:
		if(CurrentPosition==Answer3 || CurrentPosition==Answer4)
		{
			break;
		}
		else
		{
			SelectBox.Y_start+=45;
			SelectBox.Y_end+=45;
			Button_pressed=NONE;
			HTFT_voidDisplayImage(Board2);
			HTFT_voidDrawShape(SelectBox,Board2);
			GAME1_voidUpdatePosition();
		}
		break;
	case DOWN:
		if(CurrentPosition==Answer1 || CurrentPosition==Answer2)
		{
			break;
		}
		else
		{
			SelectBox.Y_start-=45;
			SelectBox.Y_end-=45;
			Button_pressed=NONE;
			HTFT_voidDisplayImage(Board2);
			HTFT_voidDrawShape(SelectBox,Board2);
			GAME1_voidUpdatePosition();
		}
		break;
	case RIGHT:
		if(CurrentPosition==Answer4 || CurrentPosition==Answer2)
		{
			break;
		}
		else
		{
			SelectBox.X_start+=60;
			SelectBox.X_end+=60;
			Button_pressed=NONE;
			HTFT_voidDisplayImage(Board2);
			HTFT_voidDrawShape(SelectBox,Board2);
			GAME1_voidUpdatePosition();
		}
		break;
	case LEFT:
		if(CurrentPosition==Answer3 || CurrentPosition==Answer1)
		{
			break;
		}
		else
		{
			SelectBox.X_start-=60;
			SelectBox.X_end-=60;
			Button_pressed=NONE;
			HTFT_voidDisplayImage(Board2);
			HTFT_voidDrawShape(SelectBox,Board2);
			GAME1_voidUpdatePosition();
		}
		break;
	default:

		break;
	}

}
