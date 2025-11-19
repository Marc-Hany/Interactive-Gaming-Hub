#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MRCC_interface.h"
#include "MGPIO_interface.h"
#include "MSPI_interface.h"
#include "SYSTICK_interface.h"
#include "HTFT_image.h"
#include "HTFT_interface.h"
#include "HBUTTON_interface.h"
#include "CTRLBUTTONS_interface.h"


u8 StartFlag=0;
u8 X_start=48;
u8 X_end=82;
u8 Y_start=15;
u8 Y_end=49;
extern u8 Button_pressed;


void main(void)
{
	MRCC_voidInit();
	MRCC_voidPeripheralEnable(AHB1,GPIOA);
	MRCC_voidPeripheralEnable(AHB1,GPIOB);

	MRCC_voidPeripheralEnable(APB2,SPI1EN);
	MRCC_voidPeripheralEnable(APB2,SYSCFGEN);	//Enable SYSCFG

	MGPIO_voidSetPinMode(PORTA,PIN4,ALTERNATE_FUNC);
	MGPIO_voidSetAlternatFuncConfig(PORTA,PIN4,AF5); //SS

	MGPIO_voidSetPinMode(PORTA,PIN5,ALTERNATE_FUNC);
	MGPIO_voidSetAlternatFuncConfig(PORTA,PIN5,AF5); //CLK

	MGPIO_voidSetPinMode(PORTA,PIN6,ALTERNATE_FUNC);
	MGPIO_voidSetAlternatFuncConfig(PORTA,PIN6,AF5); //MISO

	MGPIO_voidSetPinMode(PORTA,PIN7,ALTERNATE_FUNC);
	MGPIO_voidSetAlternatFuncConfig(PORTA,PIN7,AF5); //MOSI

	MGPIO_voidSetPinMode(PORTA,PIN9,OUTPUT);
	MGPIO_voidSetOutputConfig(PORTA,PIN9,PUSH_PULL,LOW_SPEED);

	SYSTICK_voidStart(1000);
	CTRLBUTTONS_voidInit();
	MSPI_voidMasterInit();


	HTFT_voidInit();
	HTFT_voidDisplayImage(Start);
	while (1)
	 {
		switch(Button_pressed)
		{
		case UP:
			if(StartFlag==1)
			{
				if(Y_start==115 && Y_end==149)
				{
					break;
				}
				else
				{
					Y_start+=50;
					Y_end+=50;
					Button_pressed=NONE;
					HTFT_voidDisplayImage(Game);
					HTFT_voidDrawShape(Select_Box,Game,X_start,X_end,Y_start,Y_end);
				}
			}
			break;
		case DOWN:
			if(StartFlag==1)
			{
				if(Y_start==15 && Y_end==49)
				{
					break;
				}
				else
				{
					Y_start-=50;
					Y_end-=50;
					Button_pressed=NONE;
					HTFT_voidDisplayImage(Game);
					HTFT_voidDrawShape(Select_Box,Game,X_start,X_end,Y_start,Y_end);
				}
			}
			break;
		case RIGHT:
			break;
		case LEFT:
			break;
		case OK:
			if(StartFlag==0)
			{
				Button_pressed=NONE;
				HTFT_voidDisplayImage(Game);
				HTFT_voidDrawShape(Select_Box,Game,X_start,X_end,Y_start,Y_end);
				StartFlag=1;
			}
		}

	 }
}


