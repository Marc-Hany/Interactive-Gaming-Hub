/*
 * SYSTICK_interface.h
 *
 *  Created on: Jul 26, 2025
 *      Author: march
 */

#ifndef SYSTICK_INTERFACE_H_
#define SYSTICK_INTERFACE_H_

/*Define Interrupt States*/
typedef enum
{
	INT_DISABLE=0,
	INT_ENABLE
}INTERRUPT_STATE;


void SYSTCICK_voidInit(void);
void SYSTICK_voidConfigInterruptState(INTERRUPT_STATE Copy_uddtState);
void SYSTICK_voidStart(u32 Copy_u32TicksValue);

void SYSTICK_voidDelay_ms(u32 Copy_u32DelayTime);
void SYSTICK_voidDelay_us(u32 Copy_u32DelayTime);

u32 SYSTICK_u32GetElapsedTime();
u32 SYSTICK_u32GetRemainingTime();

void SYSTICK_SetCallback(void(*Copy_pvFunc)(void),u32 Copy_u32Periodicity_us);
void SYSTICK_SetCallbackSingle(void(*Copy_pvFunc)(void),u32 Copy_u32Periodicity_us);


#endif /* SYSTICK_INTERFACE_H_ */
