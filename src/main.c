
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MRCC_interface.h"
#include "MGPIO_interface.h"
#include "MSPI_interface.h"
#include "SYSTICK_interface.h"
#include "HTFT_interface.h"
#include "HBUTTON_interface.h"
#include "CTRLBUTTONS_interface.h"
#include "MAINMENU_interface.h"
#include "OS_interface.h"
#include "NVIC_interface.h"
#include "HLEDMATRIX_interface.h"
#include "MTIM2_interface.h"
#include "GAME1_interface.h"
#include "HSD_interface.h"


void main(void)
{
	MRCC_voidInit();

	MRCC_voidPeripheralEnable(AHB1,GPIOA);
	MRCC_voidPeripheralEnable(AHB1,GPIOB);

	MRCC_voidPeripheralEnable(APB2,SPI1EN);
	MRCC_voidPeripheralEnable(APB2,SYSCFGEN);	//Enable SYSCFG

	MRCC_voidPeripheralEnable(APB1,TIM2EN);

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

	NVIC_voidEnable(TIM2);

	SYSTICK_voidStart(1000);
	CTRLBUTTONS_voidInit();
	MSPI_voidMasterInit();
	HTFT_voidCSHigh();
	SD_CS_HIGH();
	MSPI_voidMasterInit();
	volatile u8 sd_init=HSD_u8Init();
	SD_CS_HIGH();
	HTFT_voidCSLow();
	HTFT_voidInit();
	MAINMENU_voidInit();
	HLEDMATRIX_voidInitSTP();
	MTIM2_voidStart_us(500,HLEDMATRIX_OS);
	OS_u8CreateTask(MAINMENU_voidButtonNavigation,5,0,0);
	OS_u8CreateTask(GAME1_voidGameLogic,1,1,0);
	OS_voidTaskSuspend(1);
	OS_voidStartScheduler(500);
	while (1)
	 {

	 }
}
