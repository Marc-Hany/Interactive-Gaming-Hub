/*
 * OS_interface.h
 *
 *  Created on: Aug 15, 2025
 *      Author: march
 */

#ifndef OS_INTERFACE_H_
#define OS_INTERFACE_H_

typedef enum
{
	DORMANT=0,
	READY,
	RUNNING,
	SUSPENDED
}TASK_STATE;

/*
 * OS_program.c
 *
 *  Created on: Aug 15, 2025
 *      Author: march
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "OS_private.h"
#include "OS_interface.h"
#include "OS_config.h"



#include "SYSTICK_interface.h"
u8 OS_u8CreateTask(void(*Func)(void),u16 Copy_u16Periodicity, u8 Copy_u8Priority, u16 Copy_u16FirstDelay);
void OS_voidScheduler(void);
void OS_voidTaskSuspend(u8 Copy_u8Priority);

void OS_voidTaskResume(u8 Copy_u8Priority);

void OS_voidTaskDelete(u8 Copy_u8Priority);

void OS_voidStartScheduler(u32 Copy_u32Periodicity_us);




#endif /* OS_INTERFACE_H_ */
