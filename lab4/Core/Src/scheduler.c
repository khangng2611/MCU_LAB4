/*
 * scheduler.c
 *
 *  Created on: Nov 29, 2022
 *      Author: HP
 */

#include "scheduler.h"

sTasks SCH_tasks_G[SCH_MAX_TASKS];
uint8_t current_index_task = 0;

void SCH_Init(void) {
//	for (int i = 0; i < SCH_MAX_TASKS; i++) {
//		SCH_Delete_Task(i);
//	}
	//reset the global error available
	// SCH_Delete_Task() will generate an error code.
	//(because the task array is empty)

//	Error_code_G = 0;
//	Timer_init();
//	Watchdog_init();

	current_index_task = 0;
}

//setTimer
void SCH_Add_Task (void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD) {
	if (current_index_task < SCH_MAX_TASKS) {
		SCH_tasks_G[current_index_task].pTask = pFunction;
		SCH_tasks_G[current_index_task].Delay = DELAY/TICK;
		SCH_tasks_G[current_index_task].Period = PERIOD/TICK;
		SCH_tasks_G[current_index_task].RunMe = 0;

		SCH_tasks_G[current_index_task].TaskID = current_index_task;
		current_index_task ++;
//	} else {
//		Error_code_G = ERROR_SCH_TOO_MANY_TASKS;
		}
}

//timerRun
void SCH_Update(void) {
	for (int i=0; i < current_index_task; i++) {
		if (SCH_tasks_G[i].Delay > 0) {
			SCH_tasks_G[i].Delay --;
		} else {
			SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period;
			SCH_tasks_G[i].RunMe += 1;
		}
	}
}

//check timer_flag
void SCH_Dispatch_Tasks(void) {
	for (int i = 0; i < current_index_task; i++) {
		if (SCH_tasks_G[i].RunMe > 0) {
			SCH_tasks_G[i].RunMe --;
			(*SCH_tasks_G[i].pTask)();
			//if this is a one shot task, remove it from the array
			if (SCH_tasks_G[i].Period == 0) {
				SCH_Delete_Task(i);
			}
		}
	}
	//report system status
	//SCH_Report_Status();
	//the scheduler enters idle mode this point
	//SCH_Go_To_Sleep();
}

void SCH_Delete_Task(uint32_t ID) {
	SCH_tasks_G[ID].pTask = 0x0000;
	SCH_tasks_G[ID].Delay = 0;
	SCH_tasks_G[ID].Period = 0;
	SCH_tasks_G[ID].RunMe = 0;
	for (int i = ID; i < current_index_task - 1; i++) {
		SCH_tasks_G[i].pTask = SCH_tasks_G[i+1].pTask ;
		SCH_tasks_G[i].Delay = SCH_tasks_G[i+1].Delay;
		SCH_tasks_G[i].Period = SCH_tasks_G[i+1].Period;
		SCH_tasks_G[i].RunMe = SCH_tasks_G[i+1].RunMe;
	}
	current_index_task --;
}

