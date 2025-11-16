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
#include "HSD_interface.h"


u8 StartFlag=0;
u8 X_start=48;
u8 X_end=82;
u8 Y_start=15;
u8 Y_end=49;

u8 Buffer[2560]={0};
u16 BufferPixel[1280]={0};
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

	MGPIO_voidSetPinMode(PORTA,PIN0,OUTPUT);
	MGPIO_voidSetOutputConfig(PORTA,PIN0,PUSH_PULL,LOW_SPEED);

	MSPI_voidMasterInit();
	HSD_u8Init();
	HSD_voidReadBlocks(0,Buffer,5);

	HTFT_voidInit();
	HTFT_voidDisplayImage(Start);
	for(u16 i=0;i<2560;i+=2)
	{
		BufferPixel[i/2]= (Buffer[i+1] << 8) | Buffer[i];
	}
	HTFT_voidDrawShape(BufferPixel,Start,X_start,X_end,Y_start,Y_end);
	MGPIO_voidSetPinMode(PORTA,PIN9,OUTPUT);
	while (1)
	{

	}
}


