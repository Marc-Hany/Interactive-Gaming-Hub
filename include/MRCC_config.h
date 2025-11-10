/*
 * MRCC_config.h
 *
 *  Created on: Jul 19, 2025
 *      Author: march
 */

#ifndef MRCC_CONFIG_H_
#define MRCC_CONFIG_H_

/* Choose Clk source:
 * 				1-HSI
 * 				2-HSE
 * 				3-PLL_HSI
 * 				4-PLL_HSE
 */
#define SYSTEM_CLOCK		HSI //Default is HSI

/* Choose HSE Oscillator:
 * 				1-MECHANICAL
 * 				2-ELECTRICAL
 */
#define HSE_SOURCE_TYPE		MECHANICAL //Default is MECHANICAL



#endif /* MRCC_CONFIG_H_ */
