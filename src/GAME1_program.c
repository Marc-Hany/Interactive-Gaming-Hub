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
#include "HLEDMATRIX_interface.h"

#include <stdlib.h>

extern u8 Button_pressed;
extern u8 randomN1;	//Number 1 (0-9)
extern u8 randomN2;	//Number 2 (0-9)
extern u8 randomOp;	//Operand (0-3)
extern u8 randomAp;	//Answer Position (0-3)
extern u8 randomAnswer1;	//Answer (0-99)
extern u8 randomAnswer2;	//Answer (0-99)
extern u8 randomAnswer3;	//Answer (0-99)
extern u16 Image[20480];

volatile u8 CorrectAnswer=0;
volatile u8 LevelCounter=0;
volatile u8 CorrectCounter=0;
volatile u8 NextFlag=0;
volatile u8 LastPressed=0;
static u32 BoardIndex=178;
static u32 CorrectIndex=259;
static u32 WrongIndex=340;
static u32 Score_Index=501;
static u32 Background_Index=582;

u8 smileyFace[9]={255, 255, 219, 255, 126, 189, 195, 255};


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
static POSITION CorrectPosition=0;
static POSITION PositionsArray[4]={Answer1,Answer2,Answer3,Answer4};


static Sprite_t Number1=
{
		NUMBER,
		N1,
		N1+9,
		104,
		133,
		One
};

static Sprite_t Number2=
{
		NUMBER,
		N2,
		N2+9,
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

static Sprite_t Answer=
{
		ANSWER,
		0,
		0,
		0,
		0,
		One
};

static Sprite_t Score=
{
		SCORE,
		66,
		75,
		76,
		105,
		One
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
static void GAME1_voidSetNumberSprite(Sprite_t* Copy_uddtNumber,u8 Copy_u8RandomNumber)
{
	switch(Copy_u8RandomNumber)
	{
	case 0:
		Copy_uddtNumber->Copy_u16ImageArr=Zero;
		break;
	case 1:
		Copy_uddtNumber->Copy_u16ImageArr=One;
		break;
	case 2:
		Copy_uddtNumber->Copy_u16ImageArr=Two;
		break;
	case 3:
		Copy_uddtNumber->Copy_u16ImageArr=Three;
		break;
	case 4:
		Copy_uddtNumber->Copy_u16ImageArr=Four;
		break;
	case 5:
		Copy_uddtNumber->Copy_u16ImageArr=Five;
		break;
	case 6:
		Copy_uddtNumber->Copy_u16ImageArr=Six;
		break;
	case 7:
		Copy_uddtNumber->Copy_u16ImageArr=Seven;
		break;
	case 8:
		Copy_uddtNumber->Copy_u16ImageArr=Eight;
		break;
	case 9:
		Copy_uddtNumber->Copy_u16ImageArr=Nine;
		break;
	default:
		break;
	}
}

static void GAME1_voidSetOperandSprite(void)
{
	if(randomN1<randomN2 && (randomOp==1 || randomOp==3))
	{
		u8 temp=0;
		temp=randomN1;
		randomN1=randomN2;
		randomN2=temp;
		GAME1_voidSetNumberSprite(&Number1,randomN1);
		GAME1_voidSetNumberSprite(&Number2,randomN2);
	}
	if(randomN2==0 && randomOp==3)
	{
		randomOp=0;
	}
	switch(randomOp)
	{
	case 0:
		Operand.Copy_u16ImageArr=Plus;
		CorrectAnswer=randomN1+randomN2;
		break;
	case 1:
		Operand.Copy_u16ImageArr=Minus;
		CorrectAnswer=randomN1-randomN2;
		break;
	case 2:
		Operand.Copy_u16ImageArr=Multiply;
		CorrectAnswer=randomN1*randomN2;
		break;
	case 3:
		Operand.Copy_u16ImageArr=Divide;
		CorrectAnswer=randomN1/randomN2;
		break;
	default:
		break;
	}
}

static void GAME1_voidDrawCorrectAnswer(void)
{
	/*Get Position*/
	switch(randomAp)
	{
	case 0:
		Answer.X_start=(Answer1/100)+5;
		Answer.X_end=Answer.X_start+9;
		Answer.Y_start=Answer1%100;
		Answer.Y_end=Answer.Y_start+29;
		CorrectPosition=Answer1;
		break;
	case 1:
		Answer.X_start=(Answer2/100)+5;
		Answer.X_end=Answer.X_start+9;
		Answer.Y_start=Answer2%100;
		Answer.Y_end=Answer.Y_start+29;
		CorrectPosition=Answer2;
		break;
	case 2:
		Answer.X_start=(Answer3/100)+5;
		Answer.X_end=Answer.X_start+9;
		Answer.Y_start=Answer3%100;
		Answer.Y_end=Answer.Y_start+29;
		CorrectPosition=Answer3;
		break;
	case 3:
		Answer.X_start=(Answer4/100)+5;
		Answer.X_end=Answer.X_start+9;
		Answer.Y_start=Answer4%100;
		Answer.Y_end=Answer.Y_start+29;
		CorrectPosition=Answer4;
		break;
	}
	/*Check if Answer is two digits*/
	if(CorrectAnswer>=10 && CorrectAnswer<=99)
	{

		/*Draw second digit*/
		u8 digit=0;
		digit=CorrectAnswer%10;
		GAME1_voidSetNumberSprite(&Answer,digit);

		/*Draw Answers*/
		HTFT_voidDrawShapeBackgroundUpdate(Answer,Background_Index,Image);

		/*Draw First digit*/
		digit=CorrectAnswer/10;
		Answer.X_start+=9;	//Shift the drawer 1 position
		Answer.X_end+=9;
		GAME1_voidSetNumberSprite(&Answer,digit);

		/*Draw Answers*/
		HTFT_voidDrawShapeBackgroundUpdate(Answer,Background_Index,Image);
	}
	else if(CorrectAnswer<10)
	{
		GAME1_voidSetNumberSprite(&Answer,CorrectAnswer);

		/*Draw Answers*/
		HTFT_voidDrawShapeBackgroundUpdate(Answer,Background_Index,Image);
	}
	else
	{

	}
}

static void GAME1_voidDrawRandomAnswers(u8 Copy_u8RandomAnswer)
{
	/*Check if Random Answer equal to correct Answer*/
	if(Copy_u8RandomAnswer==CorrectAnswer)
	{
		Copy_u8RandomAnswer=CorrectAnswer/2;
	}

	/*Check if Answer is two digits*/
	if(Copy_u8RandomAnswer>=10 && Copy_u8RandomAnswer<=99)
	{

		/*Draw second digit*/
		u8 digit=0;
		digit=Copy_u8RandomAnswer%10;
		GAME1_voidSetNumberSprite(&Answer,digit);

		/*Draw Answers*/
		HTFT_voidDrawShapeBackgroundUpdate(Answer,Background_Index,Image);

		/*Draw First digit*/
		digit=Copy_u8RandomAnswer/10;
		Answer.X_start+=9;	//Shift the drawer 1 position
		Answer.X_end+=9;
		GAME1_voidSetNumberSprite(&Answer,digit);

		/*Draw Answers*/
		HTFT_voidDrawShapeBackgroundUpdate(Answer,Background_Index,Image);
	}
	else if(Copy_u8RandomAnswer<10)
	{
		GAME1_voidSetNumberSprite(&Answer,Copy_u8RandomAnswer);

		/*Draw Answers*/
		HTFT_voidDrawShapeBackgroundUpdate(Answer,Background_Index,Image);
	}
	else
	{

	}
}

void GAME1_voidDrawAnswers(void)
{
	u8 RandomAnswersArray[3]={randomAnswer1,randomAnswer2,randomAnswer3};
	/*Draw Correct Answer*/
	GAME1_voidDrawCorrectAnswer();

	/*Draw Rest of Answers*/
	u8 k=0;
	u8 i=0;
	while(k<4)
	{
		if(PositionsArray[k]!=CorrectPosition)
		{
			Answer.X_start=(PositionsArray[k]/100)+5;
			Answer.X_end=Answer.X_start+9;
			Answer.Y_start=PositionsArray[k]%100;
			Answer.Y_end=Answer.Y_start+29;
			GAME1_voidDrawRandomAnswers(RandomAnswersArray[i]);
			i++;
			k++;
		}
		else
		{
			k++;
		}
	}

}

void GAME1_voidLevelStart(void)
{

	/*Draw background*/
	HTFT_voidDisplayImage(BoardIndex,Image);


	/*Draw Equation*/
	GAME1_voidSetNumberSprite(&Number1,randomN1);
	GAME1_voidSetNumberSprite(&Number2,randomN2);
	GAME1_voidSetOperandSprite();
//	HTFT_voidDrawShape(Number1,BoardIndex,Image);
//	HTFT_voidDrawShape(Number2,BoardIndex,Image);
//	HTFT_voidDrawShape(Operand,BoardIndex,Image);
	HTFT_voidDrawShapeBackgroundUpdate(Number1,BoardIndex,Image);	//Number 1
	HTFT_voidDrawShapeBackgroundUpdate(Number2,BoardIndex,Image);	//Number 2
	HTFT_voidDrawShapeBackgroundUpdate(Operand,BoardIndex,Image);	//Operand


//	/*Draw Answers*/
	GAME1_voidDrawAnswers();

	/*Draw Selection Board*/
	HTFT_voidDrawShape(SelectBox,Background_Index,Image);

	/*Run Navigation*/
	NextFlag=1;
}


void GAME1_voidGame1Navigation(void)
{
	u8 CorrectFlag=0;
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
			HTFT_voidDisplayImage(Background_Index,Image);
			HTFT_voidDrawShape(SelectBox,Background_Index,Image);
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
			HTFT_voidDisplayImage(Background_Index,Image);
			HTFT_voidDrawShape(SelectBox,Background_Index,Image);
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
			HTFT_voidDisplayImage(Background_Index,Image);
			HTFT_voidDrawShape(SelectBox,Background_Index,Image);
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
			HTFT_voidDisplayImage(Background_Index,Image);
			HTFT_voidDrawShape(SelectBox,Background_Index,Image);
			GAME1_voidUpdatePosition();
		}
		break;
	case OK:
		if (CurrentPosition==CorrectPosition)
		{
			HTFT_voidDisplayImage(CorrectIndex,Image);
			CorrectFlag=1;


		}
		else
		{
			HTFT_voidDisplayImage(WrongIndex,Image);
		}
		u32 now=SYSTICK_u32GetElapsedTime();
		if(now-LastPressed>700)
		{
			Button_pressed=NONE;
			/*Run Next Level*/
			NextFlag=0;
			LastPressed = now;
			LevelCounter++;
			if(CorrectFlag==1)
			{
				CorrectCounter++;
				CorrectFlag=0;
			}
		}
		if(LevelCounter==5)
		{
			NextFlag=2;
		}
		break;
	default:

		break;
	}

}

static void GAME1_voidScoreMenu(void)
{
	switch(Button_pressed)
	{
	case UP:
		Button_pressed=NONE;
		OS_voidTaskSuspend(1);
		OS_voidTaskResume(0);
		break;
	case OK:
		NextFlag=0;
		CorrectCounter=0;
		LevelCounter=0;
		Button_pressed=NONE;
		break;
	default:
		break;
	}
}
void GAME1_voidGameLogic(void)
{
	if(NextFlag==0)
	{
		GAME1_voidLevelStart();
	}
	else if(NextFlag==1)
	{
		GAME1_voidGame1Navigation();
	}
	else if(NextFlag==2)
	{
		/*Draw Score Board*/
		HTFT_voidDisplayImage(Score_Index,Image);

		/*Draw Score at Correct Position*/
		GAME1_voidSetNumberSprite(&Score,CorrectCounter);

		HTFT_voidDrawShape(Score,Score_Index,Image);
		NextFlag=3;
	}
	else if(NextFlag==3)
	{
		GAME1_voidScoreMenu();
	}

}
