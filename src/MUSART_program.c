/*
 * MUSART_program.c
 *
 *  Created on: Aug 22, 2025
 *      Author: march
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MUSART_private.h"
#include "MUSART_config.h"
#include "MUSART_interface.h"

volatile u8 MUSART_u8ReceivedData;
volatile u8 MUSART_u8DataReceivedFlag = 0;  // 0 = no data, 1 = data received

void MUSART_voidInit(void)
{
	/*Enable TX, RX and UART*/

	SET_BIT(MUSART1->CR1,UE);	//Enable UART
	SET_BIT(MUSART1->CR1,TE);	//Enable TX
	SET_BIT(MUSART1->CR1,RE);	//Enable RX

	/* Enable RXNE interrupt */
	SET_BIT(MUSART1->CR1, RXNEIE);

	/*Set Baud Rate*/
	CLR_BIT(MUSART1->CR1,OVER8);	//oversampling by 16
//	MUSART1->BRR=(8<<DIV_Mantissa) | (11);	//Baud rate = 115200
	MUSART1->BRR=(104<<DIV_Mantissa) | (3); //Baud rate = 9600

	/*Set Parity*/
	CLR_BIT(MUSART1->CR1,PCE);	//Disable Parity Control

	/*Set Frame Size*/
	SET_BIT(MUSART1->CR1,M);	//8 bits frame

	/*Set Stop Bits*/
	CLR_BIT(MUSART1->CR2,STOP);	//1 stop bit
	CLR_BIT(MUSART1->CR2,(STOP+1));
}

void MUSART_voidTransmit(u8 Copy_u8Data)	//using 8 bits frame
{
	while(!GET_BIT(MUSART1->SR,7));	//wait for data
	MUSART1->DR = Copy_u8Data;	// transmit
}

// Send a null-terminated char array over UART
void MUSART_voidSendChars(const u8* ptr) {
    while (*ptr) {
    	MUSART_voidTransmit(*ptr++);
    }
}

u8 MUSART_u8Receive(void)
{
	u8 Local_u8Data;
	while(!GET_BIT(MUSART1->SR,5));	//wait for data
	Local_u8Data=MUSART1->DR;
	return Local_u8Data;
}

void USART1_IRQHandler(void)
{
    if (GET_BIT(MUSART1->SR, 5))   // RXNE flag
    {
        MUSART_u8ReceivedData = MUSART1->DR; // read byte
        if(MUSART_u8ReceivedData=='1')
        {
        	MUSART_u8DataReceivedFlag = 1;       // set flag
        }
        if(MUSART_u8ReceivedData=='2')
		{
			MUSART_u8DataReceivedFlag = 2;       // set flag
		}

    }
}

