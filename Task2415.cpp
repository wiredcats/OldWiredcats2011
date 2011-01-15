#include "Task2415.h"

Task2415::Task2415(void) {
	// task default values
}

void Task2415::Start(char * id) {
	// throws the task in the vxWorks task queue
	taskSpawn(id, TASK2415_DEFAULT_PRIORITY, VX_FP_TASK, TASK2415_STACKSIZE,
			  (FUNCPTR) Task2415::TaskWrapper, (int)this, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

int Task2415::TaskWrapper(void *this_p, int a2, int a3, int a4, int a5,
						   int a6, int a7, int a8, int a9, int a10) {
	// entire purpose of this function is to send the task over to the
	// subclass's Main() function
	return ((Task2415 *)this_p)->Main(a2, a3, a4, a5, a6, a7, a8, a9, a10);
}

void Task2415::SwapAndWait(void) {
	/*
	 * struct timespec ts; // nanosleep takes the struct timespec for some reason
	 * ts.tv_nsec = 10 * 1000 * 1000; // 10ms
	 * 
	 * (the above will be implemented when the code gets more complicated)
	 */
	
	// tell vxWorks that it can switch over to some other task now!
	taskUnlock();
	
	// sleep this task for a while, vxWorks will mark this task as inactive
	// and switch over!
	/*
	 * nanosleep((const struct timespec *)&ts, NULL);
	 *
	 * (the above etc...)
	 */
	taskDelay(1); // temporary implementation
	
	// tell vxWorks that we wanna get back to this task
	taskLock();
}
