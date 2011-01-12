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
	return ((Task2415 *)this_p)->Main(a2, a3, a4, a5, a6, a7, a8, a9, a10);
}
