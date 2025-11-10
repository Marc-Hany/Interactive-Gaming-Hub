/*
 * MRCC_interface.h
 *
 *  Created on: Jul 19, 2025
 *      Author: march
 */

#ifndef MRCC_INTERFACE_H_
#define MRCC_INTERFACE_H_

typedef enum{
	AHB1=0,
	AHB2,
	APB1,
	APB2
}Peripheral_Bus;

typedef enum{
	GPIOA=0,
	GPIOB,
	GPIOC,
	CRCEN=12,
	DMA1EN=21,
	DMA2EN
}AHB1_Peripherals;

typedef enum{
	OTGFSEN=7
}AHB2_Peripherals;

typedef enum{
	TIM2EN=0,
	TIM3EN,
	TIM4EN,
	TIM5EN,
	WWDGEN=11,
	SPI2EN=14,
	SPI3EN,
	USART2EN=17,
	I2C1EN=21,
	I2C2EN,
	I2C3EN,
	PWREN=28
}APB1_Peripherals;

typedef enum{
	TIM1EN=0,
	USART1EN=4,
	USART6EN,
	ADC1EN=8,
	SDIOEN=11,
	SPI1EN,
	SPI4EN,
	SYSCFGEN,
	TIM9EN=19,
	TIM10EN,
	TIM11EN
}APB2_Peripherals;


void MRCC_voidInit(void); //Initialize Peripheral

void MRCC_voidPeripheralEnable(u8 Copy_u8Bus , u8 Copy_u8Peripheral); //Enable the Peripheral of your choice

void MRCC_voidPeripheralDisable(u8 Copy_u8Bus , u8 Copy_u8Peripheral); //Disable the Peripheral of your choice


#endif /* MRCC_INTERFACE_H_ */
