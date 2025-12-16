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
#include "HSD_interface.h"

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
volatile u8 LastPressed=0;
static u32 BoardIndex=178;
static u32 CorrectIndex=259;
static u32 WrongIndex=340;
static u32 Score_Index=501;
static u32 Background_Index=582;
static u32 Start_Index=663;
static u32 Listfull_Index=744;
static u32 Playerx_Index=825;
static u32 ExistingPlayers_Index=906;


static u32 Players_Data_Index=10000;


u8 smiley_face[8]={0, 0, 36, 0, 129, 66, 60, 0};
u8 sad_face[8]={0, 36, 0, 0, 60, 66, 129, 0};
u16 time_counter=2000;
u8 timeisupFlag=0;
u16 time_left=9;

typedef struct
{
	u8 Player_Number;
	u8 Last_Score;
	u8 Active;
}PLAYER_t;

PLAYER_t Players[3];
PLAYER_t CurrentPlayer;
volatile u8 Listful_Flag=0;
volatile u8 Players_Count=0;

static Sprite_t SelectBox85=
{
		SELECTBOX85,
		22,
		106,
		80,
		95,
		Select_Box85
};

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
	N2=29,
	New_Player=80,
	Existing_Player=58,
	Player1_Position=88,
	Player2_Position=63,
	Player3_Position=38,
	Score_Board=36

}POSITION;

typedef enum
{
	STARTGAME,
	STARTNAVIGATION,
	NEWPLAYER,
	NEWPLAYERNAVIGATION,
	PLAYERS,
	PLAYERSNAVIGATION,
	SCOREBOARD,
	NEWLEVEL,
	NAVIGATION,
	FINALSCORE,
	SCORENAVIGATION

}STATE;

volatile STATE NextFlag=STARTGAME;

static POSITION CurrentPosition=New_Player;
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

static Sprite_t Time=
{
		TIME,
		108,
		117,
		130,
		159,
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

static Sprite_t PlayerX=
{
		PLAYERX,
		26,
		35,
		79,
		108,
		One
};

static Sprite_t ExistingPlayer=
{
		EXISTINGPLAYER,
		43,
		87,
		88,
		103,
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

static void GAME1_voidDownloadPlayersData(void)
{
	u8 PlayersData[512];
	HSD_voidReadBlock(Players_Data_Index,PlayersData);
	u8 i=0;
	for(u8 j=0;j<3;j++)
	{
		Players[j].Player_Number=PlayersData[i++];
		Players[j].Last_Score=PlayersData[i++];
		Players[j].Active=PlayersData[i++];
		if(Players[j].Active==1)
		{
			Players_Count++;
		}
	}
}

static void GAME1_voidUploadPlayersData(void)
{
	u8 PlayersData[512];
	u8 i=0;
	for(u8 j=0;j<3;j++)
	{
		PlayersData[i++]=Players[j].Player_Number;
		PlayersData[i++]=Players[j].Last_Score;
		PlayersData[i++]=Players[j].Active;
	}
	HSD_u8WriteBlock(Players_Data_Index,PlayersData);
}

void GAME1_voidResetPlayersData(void)
{
	u8 PlayersData[512];
	u8 i=0;
	for(u8 j=0;j<3;j++)
	{
		PlayersData[i++]=0;
		PlayersData[i++]=0;
		PlayersData[i++]=0;
	}
	Listful_Flag=0;
	HSD_u8WriteBlock(Players_Data_Index,PlayersData);
}

static void GAME1_voidNewPlayerNavigation(void)
{
	switch (Button_pressed) {
		case OK:
			if(Listful_Flag)
			{
				NextFlag=STARTGAME;
			}
			else NextFlag=NEWLEVEL;
			Button_pressed=NONE;
			break;
		default:
			break;
	}

}

static void GAME1_voidNewPlayerMenu(void)
{
	if(Players[0].Active && Players[1].Active && Players[2].Active)
	{
		/*Player List Full Go back and select an existing player*/
		HTFT_voidDisplayImage(Listfull_Index,Image);
		NextFlag=NEWPLAYERNAVIGATION;
		Listful_Flag=1;

	}
	else
	{
		for(u8 i=0;i<3;i++)
		{
			if(Players[i].Active==0)
			{
				/*Create New Player*/
				Players[i].Player_Number=i+1;
				Players[i].Active=1;
				CurrentPlayer=Players[i];
				break;
			}
		}
		GAME1_voidSetNumberSprite(&PlayerX,CurrentPlayer.Player_Number);
		HTFT_voidDisplayImage(Playerx_Index,Image);
		HTFT_voidDrawShape(PlayerX,Playerx_Index,Image);
		NextFlag=NEWPLAYERNAVIGATION;
	}
	Button_pressed=NONE;

}

static void GAME1_voidExistingPlayersMenu(void)
{
	HTFT_voidDisplayImage(ExistingPlayers_Index,Image);
	for(u8 i=0;i<3;i++)
	{
		if(Players[i].Active==1)
		{
			if(i==0)
			{
				ExistingPlayer.Copy_u16ImageArr=Player1;
			}
			else if(i==1)
			{
				ExistingPlayer.Copy_u16ImageArr=Player2;
			}
			else if(i==2)
			{
				ExistingPlayer.Copy_u16ImageArr=Player3;
			}
			HTFT_voidDrawShapeBackgroundUpdate(ExistingPlayer,ExistingPlayers_Index,Image);
		}
		ExistingPlayer.Y_end-=25;
		ExistingPlayer.Y_start-=25;
	}
	SelectBox85.X_start=24;
	SelectBox85.X_end=108;
	SelectBox85.Y_start=88;
	SelectBox85.Y_end=103;
	HTFT_voidDrawShape(SelectBox85,Background_Index,Image);
	CurrentPosition=Player1_Position;
	NextFlag=PLAYERSNAVIGATION;
}

static void GAME1_voidExistingPlayersNavigation(void)
{
	switch (Button_pressed) {
		case UP:
			if(CurrentPosition==Player1_Position)
			{
				break;
			}
			else
			{
				SelectBox85.Y_start+=25;
				SelectBox85.Y_end+=25;
				Button_pressed=NONE;
				HTFT_voidDisplayImage(Background_Index,Image);
				HTFT_voidDrawShape(SelectBox85,Background_Index,Image);
				CurrentPosition=SelectBox85.Y_start;
			}
			break;
		case DOWN:
			if(Players_Count==3 && CurrentPosition==Player3_Position)
			{
				break;
			}
			else if(Players_Count==2 && CurrentPosition==Player2_Position)
			{
				break;
			}
			else if(Players_Count==1 && CurrentPosition==Player1_Position)
			{
				break;
			}
			else
			{
				SelectBox85.Y_start-=25;
				SelectBox85.Y_end-=25;
				Button_pressed=NONE;
				HTFT_voidDisplayImage(Background_Index,Image);
				HTFT_voidDrawShape(SelectBox85,Background_Index,Image);
				CurrentPosition=SelectBox85.Y_start;
			}
			break;
		case OK:
			if(CurrentPosition==Player1_Position)
			{
				CurrentPlayer=Players[0];
				NextFlag=NEWLEVEL;
			}
			else if(CurrentPosition==Player2_Position)
			{
				CurrentPlayer=Players[1];
				NextFlag=NEWLEVEL;
			}
			else if(CurrentPosition==Player3_Position)
			{
				CurrentPlayer=Players[2];
				NextFlag=NEWLEVEL;
			}
			Button_pressed=NONE;
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

static void GAME1_voidGameStart(void)
{
	HTFT_voidDisplayImage(Start_Index,Image);
	HTFT_voidDrawShape(SelectBox85,Start_Index,Image);
	NextFlag=STARTNAVIGATION;
}

static void GAME1_voidStartNavigation(void)
{
	switch (Button_pressed) {
		case UP:
			if(CurrentPosition==New_Player)
			{
				break;
			}
			else
			{
				SelectBox85.Y_start+=22;
				SelectBox85.Y_end+=22;
				Button_pressed=NONE;
				HTFT_voidDisplayImage(Start_Index,Image);
				HTFT_voidDrawShape(SelectBox85,Start_Index,Image);
				CurrentPosition=SelectBox85.Y_start;
			}
			break;
		case DOWN:
			if(CurrentPosition==Score_Board)
			{
				break;
			}
			else
			{
				SelectBox85.Y_start-=22;
				SelectBox85.Y_end-=22;
				Button_pressed=NONE;
				HTFT_voidDisplayImage(Start_Index,Image);
				HTFT_voidDrawShape(SelectBox85,Start_Index,Image);
				CurrentPosition=SelectBox85.Y_start;
			}
			break;
		case OK:
			if(CurrentPosition==New_Player)
			{
				NextFlag=NEWPLAYER;
			}
			else if(CurrentPosition==Existing_Player)
			{
				NextFlag=PLAYERS;
			}
			else if(CurrentPosition==Score_Board)
			{
				NextFlag=SCOREBOARD;
			}
			Button_pressed=NONE;
			break;
		default:
			break;
	}
}

static void GAME1_voidDrawTime(void)
{
	Time.Copy_u16ImageArr=TimeBackground;
	HTFT_voidDrawShapeBackgroundUpdate(Time,Background_Index,Image);
	GAME1_voidSetNumberSprite(&Time,time_left);

	/*Draw Answers*/
	HTFT_voidDrawShapeBackgroundUpdate(Time,Background_Index,Image);
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
	CurrentPosition=Answer1;
	/*Draw Selection Board*/
	HTFT_voidDrawShape(SelectBox,Background_Index,Image);

	/*Draw Time*/
	GAME1_voidDrawTime();


	/*Run Navigation*/
	NextFlag=NAVIGATION;
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
			HLEDMATRIX_voidSetDisplay(smiley_face);
			CorrectFlag=1;
		}
		else
		{
			HTFT_voidDisplayImage(WrongIndex,Image);
			HLEDMATRIX_voidSetDisplay(sad_face);
		}
		u32 now=SYSTICK_u32GetElapsedTime();
		if(now-LastPressed>400)
		{
			Button_pressed=NONE;
			/*Run Next Level*/
			NextFlag=NEWLEVEL;
			/*Reset Timer*/
			timeisupFlag=0;
			time_counter=2000;
			time_left=9;
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
			NextFlag=FINALSCORE;
		}
		break;
	default:
		if(timeisupFlag)
		{
			HLEDMATRIX_voidSetDisplay(sad_face);
			HTFT_voidDisplayImage(WrongIndex,Image);
			/*Run Next Level*/
			timeisupFlag=0;
			time_counter=2000;
			time_left=9;
			NextFlag=NEWLEVEL;
			LevelCounter++;
		}
		if(LevelCounter==5)
		{
			NextFlag=FINALSCORE;
		}

		break;
	}

}

static void GAME1_voidScoreMenu(void)
{
	/*Draw Score Board*/
	HTFT_voidDisplayImage(Score_Index,Image);

	/*Draw Score at Correct Position*/
	GAME1_voidSetNumberSprite(&Score,CorrectCounter);

	HTFT_voidDrawShape(Score,Score_Index,Image);

	NextFlag=SCORENAVIGATION;

}

static void GAME1_voidScoreNavigation(void)
{
	switch(Button_pressed)
	{
	case UP:
		Button_pressed=NONE;
		OS_voidTaskSuspend(1);
		OS_voidTaskResume(0);
		CurrentPlayer.Last_Score=CorrectCounter;
		GAME1_voidUploadPlayersData();
		break;
	case OK:
		NextFlag=NEWLEVEL;
		CorrectCounter=0;
		LevelCounter=0;
		Button_pressed=NONE;
		CurrentPlayer.Last_Score=CorrectCounter;
		GAME1_voidUploadPlayersData();
		break;
	default:
		break;
	}
}

void GAME1_voidGameLogic(void)
{
	if(NextFlag>=NEWLEVEL && NextFlag<=FINALSCORE)
	{
		time_counter--;
		if(time_counter==0)
		{
			time_left--;
			GAME1_voidDrawTime();
			time_counter=2000;
		}
		if(time_left==0)
		{
			GAME1_voidDrawTime();
			timeisupFlag=1;
		}
	}

	if(NextFlag==STARTGAME)
	{
		GAME1_voidGameStart();
		GAME1_voidDownloadPlayersData();
	}
	else if(NextFlag==STARTNAVIGATION)
	{
		GAME1_voidStartNavigation();
	}
	else if(NextFlag==NEWPLAYER)
	{
		GAME1_voidNewPlayerMenu();
	}
	else if(NextFlag==NEWPLAYERNAVIGATION)
	{
		GAME1_voidNewPlayerNavigation();
	}
	else if(NextFlag==PLAYERS)
	{
		GAME1_voidExistingPlayersMenu();
	}
	else if(NextFlag==PLAYERSNAVIGATION)
	{
		GAME1_voidExistingPlayersNavigation();
	}
	else if(NextFlag==NEWLEVEL)
	{
		time_counter=2000;
		time_left=9;
		GAME1_voidLevelStart();
	}
	else if(NextFlag==NAVIGATION)
	{
		GAME1_voidGame1Navigation();
	}
	else if(NextFlag==FINALSCORE)
	{
		GAME1_voidScoreMenu();
	}
	else if(NextFlag==SCORENAVIGATION)
	{
		GAME1_voidScoreNavigation();
	}


}
