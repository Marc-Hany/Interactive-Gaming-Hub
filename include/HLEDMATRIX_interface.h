/*
 * HLEDMATRIX_interface.h
 *
 *  Created on: Aug 8, 2025
 *      Author: march
 */

#ifndef HLEDMATRIX_INTERFACE_H_
#define HLEDMATRIX_INTERFACE_H_


void HLEDMATRIX_voidInit(void);
void HLEDMATRIX_voidInitSTP(void);
void HLEDMATRIX_voidDisplay(u8 *Copy_pu8Shape);
void HLEDMATRIX_voidDisplaySTP(u8 *Copy_pu8Shape,u8 Copy_u8Col);

void HLEDMATRIX_voidPulse(u8 Copy_u8ClkPort,u8 Copy_u8ClkPin);
void HLEDMATRIX_voidOutputSTP(u8 Copy_u8SerialPort,u8 Copy_u8SerialPin,
						u8 Copy_u8ClkPort,u8 Copy_u8ClkPin,
						u8 Copy_u8LatchPort,u8 Copy_u8LatchPin,
						u8 Copy_u8Row,u8 Copy_u8Col);

void HLEDMATRIX_OS(void);

#endif /* HLEDMATRIX_INTERFACE_H_ */
