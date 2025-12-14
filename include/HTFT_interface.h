
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

typedef enum
{
	SELECTBOX=0,
	SELECTBOX30,
	NUMBER,
	OPERAND,
	ANSWER,
	TIME,
	SCORE,

}SPRITE_ID;

typedef struct
{
	SPRITE_ID Sprite_Id;
	u8 X_start;
	u8 X_end;
	u8 Y_start;
	u8 Y_end;
	const u16* Copy_u16ImageArr;
}Sprite_t;

void HTFT_voidCSLow(void);
void HTFT_voidCSHigh(void);
void HTFT_voidInit(void);
void HTFT_voidSendData(u8 Copy_u8Data);
void HTFT_voidSendCommand(u8 Copy_u8Command);
void HTFT_voidDisplayImage(u32 Copy_u32ImageIndex, u16* Copy_u16Image);
void HTFT_voidDrawShape(Sprite_t Sprite,u32 Copy_u32ImageIndex, u16* Copy_u16Image);
void HTFT_voidDrawShapeBackgroundUpdate(Sprite_t Sprite,u32 Copy_u32ImageIndex, u16* Copy_u16Image);


#endif /* HTFT_INTERFACE_H_ */
