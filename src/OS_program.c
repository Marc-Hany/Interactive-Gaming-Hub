/*
 * OS_program.c
 *
 *  Created on: Aug 15, 2025
 *      Author: march
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SYSTICK_interface.h"

#include "OS_private.h"
#include "OS_interface.h"
#include "OS_config.h"



TASK_t System_Tasks[TASKS_NUM]={{0}};

u8 OS_u8CreateTask(void(*Func)(void),u16 Copy_u16Periodicity, u8 Copy_u8Priority, u16 Copy_u16FirstDelay)
{
	u8 Local_u8ErrorState=0;	//0=No error
	if (Copy_u8Priority<TASKS_NUM)
	{
		if(Func != NULL)
		{
			for (u8 i=0;i<TASKS_NUM;i++)
			{
				if(System_Tasks[i].Task_Func == NULL)
				{
					System_Tasks[i].Periodicity=Copy_u16Periodicity;
					System_Tasks[i].Priority=Copy_u8Priority;
					System_Tasks[i].Task_Func=Func;
					System_Tasks[i].State = READY;
					System_Tasks[i].FirstDelay = Copy_u16FirstDelay;
					break;
				}
				else
				{
					continue;
				}
			}

		}
		else
		{
			Local_u8ErrorState=2;	//Pointer to NULL
		}
	}
	else
	{
		Local_u8ErrorState=1;	//Priority Error
	}


	return Local_u8ErrorState;
}


void OS_voidScheduler(void)
{
    static u32 tick = 0;
    tick++;

    for (u8 pr = 0; pr < TASKS_NUM; pr++)
    {
        for (u8 i = 0; i < TASKS_NUM; i++)
        {
            if (System_Tasks[i].Task_Func != NULL &&
                System_Tasks[i].Priority == pr &&
                System_Tasks[i].State == READY)
            {
                if (System_Tasks[i].FirstDelay > 0)
                {
                    System_Tasks[i].FirstDelay--;  // wait for first delay to finish
                }
                else
                {
                    if (tick % System_Tasks[i].Periodicity == 0)
                    {
                        System_Tasks[i].Task_Func();
                    }
                }
            }
        }
    }

    if (tick == 65535) tick = 0; // prevent overflow
}


void OS_voidTaskSuspend(u8 Copy_u8Priority)
{
	for(u8 i=0;i<TASKS_NUM;i++)
	{
		if(System_Tasks[i].Priority==Copy_u8Priority)
		{
			System_Tasks[i].State = SUSPENDED;
			break;
		}
	}

}

void OS_voidTaskResume(u8 Copy_u8Priority)
{
	for(u8 i=0;i<TASKS_NUM;i++)
	{
		if(System_Tasks[i].Priority==Copy_u8Priority)
		{
			System_Tasks[i].State = READY;
			break;
		}
	}
}

void OS_voidTaskDelete(u8 Copy_u8Priority)
{
	for(volatile u8 i=0;i<TASKS_NUM;i++)
	{
		if(System_Tasks[i].Priority==Copy_u8Priority)
		{
			System_Tasks[i].Task_Func = NULL;
			System_Tasks[i].Periodicity = 0;
			System_Tasks[i].Priority = 255;   // mark as "no task"
			System_Tasks[i].FirstDelay = 0;
			System_Tasks[i].State = DORMANT;
			break;
		}
	}

}

void OS_voidStartScheduler(u32 Copy_u32Periodicity_us)
{
	SYSTCICK_voidInit();
	SYSTICK_SetCallback(OS_voidScheduler,Copy_u32Periodicity_us);
	SYSTICK_voidConfigInterruptState(INT_ENABLE);
}


