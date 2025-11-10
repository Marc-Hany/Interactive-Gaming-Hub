/*
 * MSPI_interface.h
 *
 *  Created on: Aug 29, 2025
 *      Author: march
 */

#ifndef MSPI_INTERFACE_H_
#define MSPI_INTERFACE_H_

void MSPI_voidMasterInit(void);
void MSPI_voidSlaveInit(void);

u8 MSPI_u8Transceive(u8 Copy_u8Data);




#endif /* MSPI_INTERFACE_H_ */
