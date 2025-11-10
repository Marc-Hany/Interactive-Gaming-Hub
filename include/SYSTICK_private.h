/*
 * SYSTICK_private.h
 *
 *  Created on: Jul 26, 2025
 *      Author: march
 */

#ifndef SYSTICK_PRIVATE_H_
#define SYSTICK_PRIVATE_H_

#define SYSTICK_BASE_ADDRESS	0xE000E010

/*Define Registers*/
typedef struct
{
	u32 STK_CTRL;
	u32 STK_LOAD;
	u32 STK_VAL;
	u32 STK_CALIB;
} SYSTICK_t;

/*Define CTRL Bits*/
typedef enum
{
	CTRL_ENABLE=0,
	CTRL_TICKINT,
	CTRL_CLKSOURCE,
	CTRL_COUNTFLAG=16
}CTRL_BIT;

#define SYSTICK	((volatile SYSTICK_t*)SYSTICK_BASE_ADDRESS)


/*Define Clock Sources*/
#define AHB_CLOCK_SOURCE	1
#define AHB_DIVIDED_BY_8	0




#endif /* SYSTICK_PRIVATE_H_ */
