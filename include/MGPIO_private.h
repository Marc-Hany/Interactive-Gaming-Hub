/*
 * MGPIO_private.h
 *
 *  Created on: Jul 25, 2025
 *      Author: march
 */

#ifndef MGPIO_PRIVATE_H_
#define MGPIO_PRIVATE_H_

/*Base Addresses*/
#define GPIOA_BASE_ADDRESS	0x40020000
#define GPIOB_BASE_ADDRESS	0x40020400
#define GPIOC_BASE_ADDRESS	0x40020800



/*GPIO Registers*/
typedef struct
{
	u32 MODER;
	u32 OTYPER;
	u32 OSPEEDR;
	u32 PUPDR;
	u32 IDR;
	u32 ODR;
	u32 BSRR;
	u32 LCKR;
	u32 AFRL;
	u32 AFRH;

}GPIO_t;

#define GPIOA	((volatile GPIO_t*)GPIOA_BASE_ADDRESS)
#define GPIOB	((volatile GPIO_t*)GPIOB_BASE_ADDRESS)
#define GPIOC	((volatile GPIO_t*)GPIOC_BASE_ADDRESS)


#endif /* MGPIO_PRIVATE_H_ */
