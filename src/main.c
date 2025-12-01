#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MRCC_interface.h"
#include "MGPIO_interface.h"
#include "MSPI_interface.h"
#include "SYSTICK_interface.h"
#include "HTFT_interface.h"
#include "HBUTTON_interface.h"
#include "CTRLBUTTONS_interface.h"
#include "HSD_interface.h"
#include "Assets.h"


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
	MGPIO_voidSetInputConfig(PORTA,PIN6,PULL_UP);	//Pull MISO UP

	MGPIO_voidSetPinMode(PORTA,PIN7,ALTERNATE_FUNC);
	MGPIO_voidSetAlternatFuncConfig(PORTA,PIN7,AF5); //MOSI

	MGPIO_voidSetPinMode(PORTA,PIN9,OUTPUT);
	MGPIO_voidSetOutputConfig(PORTA,PIN9,PUSH_PULL,LOW_SPEED);

	MGPIO_voidSetPinMode(PORTA,PIN0,OUTPUT);
	MGPIO_voidSetOutputConfig(PORTA,PIN0,PUSH_PULL,LOW_SPEED);

	HTFT_voisCSHigh();
	SD_CS_HIGH();
	MSPI_voidMasterInit();
	volatile u8 sd_init=HSD_u8Init();
	volatile u8 write_chec2k;
//	u16 block[20480];
//	for(u16 i=0;i<20480;i++)
//	{
//		block[i]=Game[i];
//	}
//	write_chec2k=HSD_u8WriteBlocks(16,Game,80);
//	SD_CS_HIGH();
//	write_chec2k=HSD_u8WriteBlocks(97,Start,80);


	u16 data[20480]={0};
	HSD_voidReadBlocks(16,data,80);
	SD_CS_HIGH();
	HTFT_voisCSLow();
	HTFT_voidInit();
	HTFT_voidDisplayImage(data);

	HTFT_voisCSHigh();
	SD_CS_LOW();
	HSD_voidReadBlocks(97,data,80);
	SD_CS_HIGH();
	HTFT_voisCSLow();
	HTFT_voidInit();
	HTFT_voidDisplayImage(data);

	MGPIO_voidSetPinMode(PORTA,PIN0,OUTPUT);
	while (1)
	{

	}
}


