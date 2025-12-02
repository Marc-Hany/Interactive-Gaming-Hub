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

void HSD_voidSendCommand(u8 Copy_u8CMD, u32 Copy_u32Arg, u8 Copy_u8Crc)
{
	MSPI_u8Transceive(Copy_u8CMD);   						// Command index (CMD0)
	MSPI_u8Transceive((Copy_u32Arg >> 24) & 0xFF);          // Argument byte 1
	MSPI_u8Transceive((Copy_u32Arg >> 16) & 0xFF);          // Argument byte 2
	MSPI_u8Transceive((Copy_u32Arg >> 8) & 0xFF);			// Argument byte 3
	MSPI_u8Transceive(Copy_u32Arg & 0xFF);          		// Argument byte 4
	MSPI_u8Transceive(Copy_u8Crc);          				// Valid CRC for CMD0

}

u8 HSD_u8Init(void)
{
	u8 Local_u8CardInitialised=0;

	/*Initialize CS PIN*/
	MGPIO_voidSetPinMode(SD_PORT,SD_PIN,OUTPUT);
	MGPIO_voidSetOutputConfig(SD_PORT,SD_PIN,PUSH_PULL,LOW_SPEED);

	/*Set SPI Mode*/
	SD_CS_HIGH();	//CS Pin HIGH

	// Send HIGH on MOSI for 72+ clocks
	for(u8 i = 0; i < 10; i++)
	{
		MSPI_u8Transceive(0xFF);
	}

	/*..........CMD0 - Reset..........*/
	volatile u8 response = 0xFF;

	SD_CS_LOW();	//CS Pin LOW

	HSD_voidSendCommand(CMD0,0x00000000,0x95);	//CMD0 to Reset and enter Idle Mode

	volatile u16 timeout = 10000;
	response = 0xFF;

	/*Loop for response*/
	do {
		response = MSPI_u8Transceive(0xFF);
		timeout--;
	} while ((response != 0x01) && timeout);

	/*Extra Clock*/
	SD_CS_HIGH();	//CS Pin HIGH
	MSPI_u8Transceive(0xFF);

	if(response==0x01)
	{
		/*..........CMD8 - Check voltage range..........*/
		SD_CS_LOW();	//CS Pin LOW

		HSD_voidSendCommand(CMD8,0x000001AA,0x87);

		timeout = 1000;
		response = 0xFF;
		do {
			response = MSPI_u8Transceive(0xFF);
			timeout--;
		} while ((response & 0x80) && timeout);

		// Read R7 response (4 additional bytes for CMD8)
		volatile u8 cmd8_response[4];
		cmd8_response[0] = MSPI_u8Transceive(0xFF);
		cmd8_response[1] = MSPI_u8Transceive(0xFF);
		cmd8_response[2] = MSPI_u8Transceive(0xFF);
		cmd8_response[3] = MSPI_u8Transceive(0xFF);

		/*Extra Clock*/
		SD_CS_HIGH();	//CS Pin HIGH
		MSPI_u8Transceive(0xFF);

		/*Check Range and Version*/
		volatile u8 cmd8_check = 0;
		if(response == 0x01 && cmd8_response[2] == 0x01 && cmd8_response[3] == 0xAA) {
			cmd8_check = 1;
		}


		/*..........CMD55 + ACMD41 Loop..........*/
		volatile u16 init_timeout = 1000;
		do {
			/*..........CMD55..........*/
			SD_CS_LOW();	//CS Pin LOW

			HSD_voidSendCommand(CMD55,0x00000000,0xFF);

			timeout = 1000;
			response = 0xFF;
			do {
				response = MSPI_u8Transceive(0xFF);
				timeout--;
			} while ((response & 0x80) && timeout);

			/*Extra Clock*/
			SD_CS_HIGH();	//CS Pin HIGH
			MSPI_u8Transceive(0xFF);

			if(response != 0x01) {
				break; // CMD55 failed
			}

			/*..........ACMD41..........*/
			SD_CS_LOW();//CS Pin LOW

			/*Check that SD card is V2+ and accepts voltage range */
			u32 acmd14_arg=0;
			if(cmd8_check)
			{
				acmd14_arg=0x40000000;
			}
			else
			{
				acmd14_arg=0x00000000;
			}

			/*Send Command*/
			HSD_voidSendCommand(ACMD41,acmd14_arg,0XFF);

			timeout = 1000;
			response = 0xFF;
			do {
				response = MSPI_u8Transceive(0xFF);
				timeout--;
			} while ((response & 0x80) && timeout);

			/*Extra Clock*/
			SD_CS_HIGH();	//CS Pin HIGH
			MSPI_u8Transceive(0xFF);

			init_timeout--;
		} while ((response != 0x00) && init_timeout);
	}
	if(response == 0x00)
	{
		Local_u8CardInitialised=1;
	}
	return Local_u8CardInitialised;
}

u8 HSD_u8GetCardType(void)
{
	u8 Card_Type=0;
	/*..........CMD58..........*/
	SD_CS_LOW();	//CS Pin LOW

	/*Send Command*/
	HSD_voidSendCommand(CMD58,0x00000000,0xFF);

	volatile u8 ocr[4];
	volatile u16 timeout = 1000;
	volatile u8 response = 0xFF;
	do {
		response = MSPI_u8Transceive(0xFF);
		timeout--;
	} while ((response & 0x80) && timeout);

	// Read OCR register (4 bytes) - ALWAYS read
	ocr[0] = MSPI_u8Transceive(0xFF);
	ocr[1] = MSPI_u8Transceive(0xFF);
	ocr[2] = MSPI_u8Transceive(0xFF);
	ocr[3] = MSPI_u8Transceive(0xFF);

	/*Extra Clock*/
	SD_CS_HIGH();	//CS Pin HIGH
	MSPI_u8Transceive(0xFF);

	/*Get Card Type*/
	if(ocr[0] & 0x40)
	{
		Card_Type=SDHC;	//SDHC/SDXC
	}
	else
	{
		Card_Type=SDSC;	//SDSC
	}
	return Card_Type;
}

void HSD_voidReadBlock(u32 Copy_u32BlockIndex, u8* Copy_u8Buffer)
{
	/*Select Address Format*/
	u32 Local_u32Address;
	if (HSD_u8GetCardType()==SDHC)
	{
		Local_u32Address=Copy_u32BlockIndex;
	}
	else
	{
		Local_u32Address=Copy_u32BlockIndex*512;
	}

	/*..........CMD17..........*/
	SD_CS_LOW();	//CS Pin LOW

	/*Send Command*/
	HSD_voidSendCommand(CMD17,Local_u32Address,0XFF);

	volatile u16 timeout = 1000;
	volatile u8 response = 0xFF;
	do {
		response = MSPI_u8Transceive(0xFF);
		timeout--;
	} while ((response & 0x80) && timeout);

	/*Wait for Start Token 0xFE*/
	timeout = 1000;
	response = 0xFF;
	do {
		response = MSPI_u8Transceive(0xFF);
		timeout--;
	} while ((response != 0xFE) && timeout);

	if(response==0XFE)
	{
		for (u16 i=0;i<512;i++)
		{
			Copy_u8Buffer[i]=MSPI_u8Transceive(0xFF);
		}
		/*Extra Clock*/
		SD_CS_HIGH();	//CS Pin HIGH
		MSPI_u8Transceive(0xFF);
	}

	/*Read and Ignore two CRC Bytes*/
	MSPI_u8Transceive(0xFF);
	MSPI_u8Transceive(0xFF);

}

void HSD_voidReadBlocks(u32 Copy_u32BlockIndex, u8* Copy_u8Buffer, u32 Copy_u32BlockCount)
{
	/*Select Address Format*/
	u32 Local_u32Address;
	if (HSD_u8GetCardType()==SDHC)
	{
		Local_u32Address=Copy_u32BlockIndex;
	}
	else
	{
		Local_u32Address=Copy_u32BlockIndex*512;
	}

	/*..........CMD18..........*/
	SD_CS_LOW();	//CS Pin LOW

	/*Send Command*/
	HSD_voidSendCommand(CMD18,Local_u32Address,0XFF);

	volatile u16 timeout = 1000;
	volatile u8 response = 0xFF;
	do {
		response = MSPI_u8Transceive(0xFF);
		timeout--;
	} while ((response & 0x80) && timeout);

	for(u16 i=0;i<Copy_u32BlockCount;i++)
	{
		/*Wait for Start Token 0xFE*/
		timeout = 1000;
		response = 0xFF;
		do {
			response = MSPI_u8Transceive(0xFF);
			timeout--;
		} while ((response != 0xFE) && timeout);

		if(response==0XFE)
		{
			for (u16 j=0;j<512;j++)
			{
				Copy_u8Buffer[i*512 + j]=MSPI_u8Transceive(0xFF);
			}
		}

		/*Read and Ignore two CRC Bytes*/
		MSPI_u8Transceive(0xFF);
		MSPI_u8Transceive(0xFF);
	}

	/*Send CMD12 to stop reading*/
	HSD_voidSendCommand(CMD12,0,0XFF);
	timeout = 1000;
	response = 0xFF;
	do {
		response = MSPI_u8Transceive(0xFF);
		timeout--;
	} while ((response & 0x80) && timeout);

	/*Extra Clock*/
	SD_CS_HIGH();	//CS Pin HIGH
	MSPI_u8Transceive(0xFF);

}

u8 HSD_u8WriteBlock(u32 Copy_u32BlockIndex, u8* Copy_u8Buffer)
{
    u8 Local_u8WriteStatus = 0;
    u32 Local_u32Address;

    // Addressing depends on card type
    if (HSD_u8GetCardType() == SDHC)
        Local_u32Address = Copy_u32BlockIndex;      // SDHC uses block number
    else
        Local_u32Address = Copy_u32BlockIndex * 512; // Standard SD uses byte address

    SD_CS_LOW();

    // ---------- Send CMD24 ----------
    HSD_voidSendCommand(CMD24, Local_u32Address, 0xFF);

    // Read R1 response
    volatile u16 timeout = 1000;
    u8 response;
    do {
        response = MSPI_u8Transceive(0xFF);
        timeout--;
    } while ((response & 0x80) && timeout);

    // If CMD24 not accepted, abort
    if (response != 0x00) {
        SD_CS_HIGH();
        MSPI_u8Transceive(0xFF);
        return 0;
    }

    // Short delay before data token
    MSPI_u8Transceive(0xFF);

    // ---------- Send start-of-data token ----------
    MSPI_u8Transceive(0xFE);

    // ---------- Send 512 bytes ----------
    for (u16 i = 0; i < 512; i++)
        MSPI_u8Transceive(Copy_u8Buffer[i]);

    // ---------- Send 2 CRC bytes ----------
    MSPI_u8Transceive(0xFF);
    MSPI_u8Transceive(0xFF);

    // ---------- Read data response ----------
    timeout = 10000;
    u8 dataResponse;
    do {
        dataResponse = MSPI_u8Transceive(0xFF);
        timeout--;
    } while ((dataResponse & 0x10) && timeout); // wait until not busy

    if ((dataResponse & 0x1F) == 0x05) { // 0x05 = Data accepted
        // Wait until card is ready (0xFF)
        timeout = 10000;
        u8 busy;
        do {
            busy = MSPI_u8Transceive(0xFF);
            timeout--;
        } while (busy == 0x00 && timeout);
        Local_u8WriteStatus = 1;
    }

    // Extra clock
    SD_CS_HIGH();
    MSPI_u8Transceive(0xFF);

    return Local_u8WriteStatus;
}


u8 HSD_u8WriteBlocks(u32 Copy_u32BlockIndex, u8* Copy_u8Buffer, u32 Copy_u32BlockCount)
{
    u8 Local_u8WriteStatus = 0;
    u32 Local_u32Address;

    // Select address format
    if (HSD_u8GetCardType() == SDHC) {
        Local_u32Address = Copy_u32BlockIndex;
    } else {
        Local_u32Address = Copy_u32BlockIndex * 512;
    }

    SD_CS_LOW();  // CS low for entire sequence
    MSPI_u8Transceive(0xFF); // extra clock

    // Send CMD25 (Write Multiple Blocks)
    HSD_voidSendCommand(CMD25, Local_u32Address, 0xFF);

    // Wait for card to respond (response R1, should be 0x00)
    u16 timeout = 1000;
    u8 response = 0xFF;
    do {
        response = MSPI_u8Transceive(0xFF);
        timeout--;
    } while ((response & 0x80) && timeout);

    if (response != 0x00) {  // CMD25 rejected
        SD_CS_HIGH();
        return 0;
    }

    // Write each block
    for (u32 i = 0; i < Copy_u32BlockCount; i++) {
        // Send start-of-block token
        MSPI_u8Transceive(0xFC);

        // Send 512 bytes of data
        for (u16 j = 0; j < 512; j++) {
            MSPI_u8Transceive(Copy_u8Buffer[i * 512 + j]);
        }

        // Send dummy CRC
        MSPI_u8Transceive(0xFF);
        MSPI_u8Transceive(0xFF);

        // Read data response token
        timeout = 1000;
        response = 0xFF;
        do {
            response = MSPI_u8Transceive(0xFF);
            timeout--;
        } while (response == 0xFF && timeout);

        // Mask lower 5 bits
        u8 dataResponse = response & 0x1F;
        if (dataResponse != 0x05) { // 0x05 = data accepted
            SD_CS_HIGH();
            return 0;
        }

        // Wait until card is no longer busy
        timeout = 10000;
        do {
            response = MSPI_u8Transceive(0xFF);
            timeout--;
        } while (response == 0x00 && timeout);
    }

    // Send stop transmission token
    MSPI_u8Transceive(0xFD);

    // Wait until card is not busy after stop
    timeout = 10000;
    do {
        response = MSPI_u8Transceive(0xFF);
        timeout--;
    } while (response == 0x00 && timeout);

    SD_CS_HIGH(); // CS high
    MSPI_u8Transceive(0xFF); // extra clock

    Local_u8WriteStatus = 1;
    return Local_u8WriteStatus;
}





