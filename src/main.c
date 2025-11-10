#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MRCC_interface.h"
#include "MGPIO_interface.h"
#include "MSPI_interface.h"
#include "SYSTICK_interface.h"
#include "HTFT_image.h"
#include "HTFT_interface.h"
#include "HBUTTON_interface.h"


void Func(void);
u8 Flag=0;
u8 X_start=50;
u8 X_end=100;
u8 Y_start=50;
u8 Y_end=100;
void main(void)
{
	MRCC_voidInit();
	MRCC_voidPeripheralEnable(AHB1,GPIOA);

	MRCC_voidPeripheralEnable(APB2,SPI1EN);
	MRCC_voidPeripheralEnable(APB2,SYSCFGEN);	//Enable SYSCFG
	MGPIO_voidSetPinMode(PORTA,PIN4,ALTERNATE_FUNC);
	MGPIO_voidSetAlternatFuncConfig(PORTA,PIN4,AF5); //SS

	MGPIO_voidSetPinMode(PORTA,PIN5,ALTERNATE_FUNC);
	MGPIO_voidSetAlternatFuncConfig(PORTA,PIN5,AF5); //CLK

	MGPIO_voidSetPinMode(PORTA,PIN6,ALTERNATE_FUNC);
	MGPIO_voidSetAlternatFuncConfig(PORTA,PIN6,AF5); //MISO

	MGPIO_voidSetPinMode(PORTA,PIN7,ALTERNATE_FUNC);
	MGPIO_voidSetAlternatFuncConfig(PORTA,PIN7,AF5); //MOSIss

	HTFT_voidInit();
	/*Initialize IR*/
	HBUTTON_voidInit(PORTA,PIN9,Func);
	HTFT_voidDisplayImage(Arr2);
	HTFT_voidDrawShape(Cube2,X_start,X_end,Y_start,Y_end);
	while (1)
	 {
		 if(Flag==0)		//Reduce Number by 1
		 {

		 }
		 else if(Flag==1)	//Increase Number by 1
		 {
			 X_start+=10;
			 X_end+=10;
//			 Y_start+=10;
//			 Y_end+=10;
			 HTFT_voidDisplayImage(Arr2);
			 HTFT_voidDrawShape(Cube2,X_start,X_end,Y_start,Y_end);
			 Flag=0;
		 }
		//HTFT_voidDrawShape(Cube,0,10,0,10);
	 }

}

void Func(void)
{
	if(Flag==0)
	{
		Flag=1;

	}
	else
	{
		Flag=0;
	}
}
