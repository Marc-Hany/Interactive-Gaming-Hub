
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
#include "MUSART_interface.h"

extern u8 MUSART_u8DataReceivedFlag;  // 0 = no data, 1 = reset, 2 = Block/Unblock
volatile u8 Block_Flag=0;
static u32 Block_Index=1149;
extern u16 Image[20480];
volatile u8 SD_Fault[8]={126, 189, 219, 231, 231, 219, 189, 126};

void wifi_commands(void);

void main(void)
{
	/*MRCC Setup*/
	MRCC_voidInit();

	MRCC_voidPeripheralEnable(AHB1,GPIOA);
	MRCC_voidPeripheralEnable(AHB1,GPIOB);

	MRCC_voidPeripheralEnable(APB2,SPI1EN);
	MRCC_voidPeripheralEnable(APB2,SYSCFGEN);	//Enable SYSCFG

	MRCC_voidPeripheralEnable(APB1,TIM2EN);
	MRCC_voidPeripheralEnable(APB2,USART1EN);

	/*GPIO Setup*/
	/*UART TX and RX*/
	MGPIO_voidSetPinMode(PORTA,PIN9,ALTERNATE_FUNC);	//TX
	MGPIO_voidSetAlternatFuncConfig(PORTA,PIN9,AF7);

	MGPIO_voidSetPinMode(PORTA,PIN10,ALTERNATE_FUNC);	//RX
	MGPIO_voidSetAlternatFuncConfig(PORTA,PIN10,AF7);

	/*SPI Pins*/
	MGPIO_voidSetPinMode(PORTA,PIN4,ALTERNATE_FUNC);
	MGPIO_voidSetAlternatFuncConfig(PORTA,PIN4,AF5); //SS

	MGPIO_voidSetPinMode(PORTA,PIN5,ALTERNATE_FUNC);
	MGPIO_voidSetAlternatFuncConfig(PORTA,PIN5,AF5); //CLK

	MGPIO_voidSetPinMode(PORTA,PIN6,ALTERNATE_FUNC);
	MGPIO_voidSetAlternatFuncConfig(PORTA,PIN6,AF5); //MISO

	MGPIO_voidSetInputConfig(PORTA,PIN6,PULL_UP);	//Pull MISO UP (needed for some SD cards to work)

	MGPIO_voidSetPinMode(PORTA,PIN7,ALTERNATE_FUNC);
	MGPIO_voidSetAlternatFuncConfig(PORTA,PIN7,AF5); //MOSI

	/*Initialize UART*/
	MUSART_voidInit();
	NVIC_voidEnable(USART1);	//UART Interrupt enable

	/*Enable Timer 2 Interrupt*/
	NVIC_voidEnable(TIM2);

	/*Initialize LED Matrix*/
	HLEDMATRIX_voidInitSTP();
	MTIM2_voidStart_us(1000,HLEDMATRIX_OS);

	/*Initialize SPI*/
	MSPI_voidMasterInit();

	/*Initialize SD Card*/
	HTFT_voidCSHigh();	//TFT CS LOW
	SD_CS_HIGH();		//SD CS HIGH
	volatile u8 sd_init=0;
	sd_init=HSD_u8Init();	//Check that SD card is initialized

	if(sd_init==1)
	{
		SD_CS_HIGH();		//SD CS HIGH

		/*Start SYSTICK Clock*/
		SYSTICK_voidStart(1000);

		/*Initialize Control Buttons*/
		CTRLBUTTONS_voidInit();

		/*Initialize TFT*/
		HTFT_voidCSLow();	//TFT CS LOW
		HTFT_voidInit();

		/*Start Main Menu*/
		MAINMENU_voidInit();

		/*Create OS Tasks*/
		OS_u8CreateTask(MAINMENU_voidButtonNavigation,5,0,0);
		OS_u8CreateTask(GAME1_voidGameLogic,2,1,0);
		OS_u8CreateTask(wifi_commands,3,2,0);
		OS_voidTaskSuspend(1);

		/*Start Scheduler*/
		OS_voidStartScheduler(500);
	}
	else
	{
		HLEDMATRIX_voidSetDisplay(SD_Fault);	//X means SD card no initialized
	}


	while (1)
	 {

	 }
}

/*This function checks UART interrupt for commands from website*/
void wifi_commands(void)
{
	/*Reset Players List*/
	if(MUSART_u8DataReceivedFlag==1)
	{
		MUSART_u8DataReceivedFlag=0;
		GAME1_voidResetPlayersData();
	}

	/*Block/Unblock Games*/
	if(MUSART_u8DataReceivedFlag==2)
	{
		MUSART_u8DataReceivedFlag=0;
		if(Block_Flag==0)
		{
			Block_Flag=1;
			OS_voidTaskSuspend(0);
			OS_voidTaskSuspend(1);
			HTFT_voidDisplayImage(Block_Index,Image);
		}
		else if(Block_Flag==1)
		{
			Block_Flag=0;
			MAINMENU_voidInit();
			OS_voidTaskResume(0);
		}
	}
}


