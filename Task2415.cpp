#include "Task2415.h"

Task2415::Task2415(void) {
	// task default values
	isAwake = false;
	keepTaskAlive = true;
}

void Task2415::Start(char * id) {
	// throws the task in the vxWorks task queue
	taskSpawn(id, TASK2415_DEFAULT_PRIORITY, VX_FP_TASK, TASK2415_STACKSIZE,
			  (FUNCPTR) Task2415::TaskWrapper, (int)this, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

int Task2415::TaskWrapper(void *this_p, int a2, int a3, int a4, int a5,
						   int a6, int a7, int a8, int a9, int a10) {
	return ((Task2415 *)this_p)->Main(a2, a3, a4, a5, a6, a7, a8, a9, a10);
}

void Task2415::ChillTillAwake(R_STATUS rstat) {
	// Once the robot goes into teleop, jump into the main part of the task
	if (rstat == STATUS_TELEOP) { isAwake = true; }
	SwapAndWait();
}

void Task2415::SwapAndWait(void) {
	// tell vxWorks that it can switch over to some other task now!
	taskUnlock();

	// sleep this task for a while, vxWorks will mark this task as inactive
	// and switch over!
	taskDelay(2);

	// tell vxWorks that we wanna get back to this task
	taskLock();
}
