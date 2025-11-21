/*
 * MAINMENU_program.c
 *
 *  Created on: Nov 19, 2025
 *      Author: march
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"


#include "MAINMENU_interface.h"
#include "HTFT_image.h"
#include "HTFT_interface.h"
#include "CTRLBUTTONS_interface.h"
#include "OS_interface.h"


static u8 UnderConst=0;
extern u8 Button_pressed;
static Sprite_t SelectBox=
{
		SELECTBOX,
		48,
		82,
		15,
		49,
		Select_Box
};

typedef enum
{
	Game1=15,
	Game2=65,
	Game3=115

}POSITION;

static POSITION CurrentPosition=Game1;

void update_position(void)
{
	if(SelectBox.Y_start==Game1)
	{
		CurrentPosition=Game1;
	}
	else if(SelectBox.Y_start==Game2)
	{
		CurrentPosition=Game2;
	}
	else if(SelectBox.Y_start==Game3)
	{
		CurrentPosition=Game3;
	}
}

void MAINMENU_voidInit(void)
{
	HTFT_voidDisplayImage(Start);
	HTFT_voidDrawShape(SelectBox,Start);
}

void MAINMENU_voidButtonNavigation(void)
{
	switch(Button_pressed)
	{
	case UP:
		if(UnderConst==0)
		{
			if(CurrentPosition==Game3)
			{
				break;
			}
			else
			{
				SelectBox.Y_start+=50;
				SelectBox.Y_end+=50;
				Button_pressed=NONE;
				HTFT_voidDisplayImage(Start);
				HTFT_voidDrawShape(SelectBox,Start);
				update_position();
			}
		}

		break;
	case DOWN:
		if(UnderConst==0)
		{
			if(CurrentPosition==Game1)
			{
				break;
			}
			else
			{
				SelectBox.Y_start-=50;
				SelectBox.Y_end-=50;
				Button_pressed=NONE;
				HTFT_voidDisplayImage(Start);
				HTFT_voidDrawShape(SelectBox,Start);
				update_position();
			}
		}

		break;
	case RIGHT:
		break;
	case LEFT:
		break;
	case OK:
		if(UnderConst==0)
		{
			if(CurrentPosition==Game1)
			{
				HTFT_voidDisplayImage(Game);
				UnderConst=1;
			}
			else if(CurrentPosition==Game2)
			{
				OS_voidTaskSuspend(0);//Suspend Main Menu
				OS_voidTaskResume(1);//Start Game1 Task
			}
			else if(CurrentPosition==Game3)
			{
				HTFT_voidDisplayImage(Game);
				UnderConst=1;
			}
		}
		else
		{
			MAINMENU_voidInit();
			UnderConst=0;
		}

		Button_pressed=NONE;
		break;
	default:

		break;
	}
}
