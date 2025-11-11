/*
 * HTFT_interface.h
 *
 *  Created on: Sep 5, 2025
 *      Author: march
 */

#ifndef HTFT_INTERFACE_H_
#define HTFT_INTERFACE_H_

#define HTFT_444	0x03
#define HTFT_565	0x05
#define HTFT_666	0x06

#define TRANSPARENT	0xfd7f

void HTFT_voidInit(void);
void HTFT_voidSendData(u8 Copy_u8Data);
void HTFT_voidSendCommand(u8 Copy_u8Command);
void HTFT_voidDisplayImage(const u16* Copy_u16ImageArr);
void HTFT_voidDrawShape(const u16* Copy_u16ImageArr,const u16* Copy_u16BckgArr,u8 Copy_u8StartX, u8 Copy_u8EndX, u8 Copy_StartY, u8 Copy_u8EndY);


#endif /* HTFT_INTERFACE_H_ */
