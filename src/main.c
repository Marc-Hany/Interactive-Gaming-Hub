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


u8 Flag=0;
u8 X_start=0;
u8 X_end=50;
u8 Y_start=0;
u8 Y_end=50;

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

	CTRLBUTTONS_voidInit();
	HTFT_voidInit();
	HTFT_voidDisplayImage(Arr2);
	HTFT_voidDrawShape(Cube3,Arr2,X_start,X_end,Y_start,Y_end);
	while (1)
	 {
		switch(Button_pressed)
		{
		case UP:
			X_start+=10;
			X_end+=10;
			if(X_end>=127)
			{
				X_start=0;
				X_end=50;
				break;
			}
			Button_pressed=NONE;
			HTFT_voidDisplayImage(Arr2);
			HTFT_voidDrawShape(Cube3,Arr2,X_start,X_end,Y_start,Y_end);
			break;
		case DOWN:
			X_start-=10;
			X_end-=10;
			if(X_start>=127)
			{
				X_start=70;
				X_end=120;
				break;
			}
			Button_pressed=NONE;
			HTFT_voidDisplayImage(Arr2);
			HTFT_voidDrawShape(Cube3,Arr2,X_start,X_end,Y_start,Y_end);
			break;
		case RIGHT:
			Y_start+=10;
			Y_end+=10;
			Button_pressed=NONE;
			HTFT_voidDisplayImage(Arr2);
			HTFT_voidDrawShape(Cube3,Arr2,X_start,X_end,Y_start,Y_end);
			break;
		case LEFT:
			Y_start-=10;
			Y_end-=10;
			Button_pressed=NONE;
			HTFT_voidDisplayImage(Arr2);
			HTFT_voidDrawShape(Cube3,Arr2,X_start,X_end,Y_start,Y_end);
			break;
		case OK:
			Button_pressed=NONE;
			HTFT_voidDisplayImage(Arr2);
			HTFT_voidDrawShape(Cube3,Arr2,X_start,X_end,Y_start,Y_end);
			break;
		default:
			break;
		}

	 }
}


