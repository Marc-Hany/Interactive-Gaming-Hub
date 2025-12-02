/*
 * HSD_interface.h
 *
 *  Created on: Nov 14, 2025
 *      Author: march
 */

#ifndef HSD_INTERFACE_H_
#define HSD_INTERFACE_H_

#define CMD0	0x40	//GO_IDLE_STATE
#define CMD8	0x48
#define CMD9	0x49
#define	CMD12	0x4C
#define	CMD17	0x51
#define	CMD18	0x52
#define CMD24	0x58
#define CMD25	0x59
#define CMD55	0x77
#define CMD58	0x7A
#define ACMD41	0x69

#define SD_CS_HIGH() MGPIO_voidSetPinValue(SD_PORT,SD_PIN,PIN_HIGH)
#define SD_CS_LOW()  MGPIO_voidSetPinValue(SD_PORT,SD_PIN,PIN_LOW)

#define SDHC	1
#define SDSC	0

/*
 * HSD_program.c
 *
 *  Created on: Nov 14, 2025
 *      Author: march
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MGPIO_interface.h"
#include "MSPI_interface.h"
#include "HSD_private.h"
#include "HSD_config.h"
#include "HSD_interface.h"

void HSD_voidSendCommand(u8 Copy_u8CMD, u32 Copy_u32Arg, u8 Copy_u8Crc);
u8 HSD_u8Init(void);
u8 HSD_u8GetCardType(void);
void HSD_voidReadBlock(u32 Copy_u32BlockIndex, u8* Copy_u8Buffer);
void HSD_voidReadBlocks(u32 Copy_u32BlockIndex, u8* Copy_u8Buffer, u32 Copy_u32BlockCount);
u8 HSD_u8WriteBlock(u32 Copy_u32BlockIndex, u8* Copy_u8Buffer);
u8 HSD_u8WriteBlocks(u32 Copy_u32BlockIndex, u8* Copy_u8Buffer,u32 Copy_u32BlockCount);





#endif /* HSD_INTERFACE_H_ */
