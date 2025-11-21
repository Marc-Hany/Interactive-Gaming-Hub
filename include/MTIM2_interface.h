/*
 * MTIM2_interface.h
 *
 *  Created on: Nov 21, 2025
 *      Author: march
 */

#ifndef MTIM2_INTERFACE_H_
#define MTIM2_INTERFACE_H_

void MTIM2_voidStart_us(u32 Copy_u32Time_uSec, void (*Copy_pvCallBackFunc)(void));
void MTIM2_voidStart_ms(u32 Copy_u32Time_mSec, void (*Copy_pvCallBackFunc)(void));

#endif /* MTIM2_INTERFACE_H_ */
