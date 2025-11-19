/*
 * OS_private.h
 *
 *  Created on: Aug 15, 2025
 *      Author: march
 */

#ifndef OS_PRIVATE_H_
#define OS_PRIVATE_H_

typedef struct
{
	void(*Task_Func)(void);
	u16 Periodicity;
	u8 Priority;
	u16 FirstDelay;
	u8 State;

}TASK_t;



#endif /* OS_PRIVATE_H_ */
