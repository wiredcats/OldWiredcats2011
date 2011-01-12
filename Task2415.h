#include "WPILib.h"

#define TASK2415_DEFAULT_PRIORITY (200) // 1 = highest, 255 = lowest
#define TASK2415_STACKSIZE (1024 * 64)  // 64kb, memory allocated for the task

/*
 * Task2415
 * ========
 * 
 * (vxWorks is the name of the operating system on the cRIO)
 * 
 * Multitasking in vxWorks works as follows:
 * 		1) First, we add a task to the internal queue of tasks
 * 		2) Any number of tasks with the same priority will be carried out
 * 		   by order of when they are called. The next task in the queue
 * 		   will not begin until the task before it is completed
 * 				2b) Tasks are ordered in the queue by priority. If a task is
 * 					called with a higher priority than any other task, then
 * 					vxWorks will instantly switch to that task no matter
 * 					if the task its working on is complete or not.
 * 		3) vxWorks does NOT partition the CPU to different tasks. We gotta
 * 		   find a way to simulate that by switching from task to task at a
 * 		   quick enough rate that it might as well be truly multitasking.
 * 		4) How do we do this? We let a task carry out a portion of its work
 * 		   then tell vxWorks that we don't care if it switches to a different
 * 		   task or not for a set amount of time (a few nanoseconds). vxWorks 
 * 		   will then switch to a different task, who will do the same thing.
 * 		   Eventually, all the tasks in the queue will do this, and the few
 * 		   nanoseconds will be up, so vxWorks will switch back the the first
 * 		   task and the cycle starts again.
 * 
 * Codewise, it looks something like this (greatly simplified):
 * 		taskSpawn("deploy_minibot", (FUNCPTR) minibotCode()); // add task to queue
 * 		int minibotCode() {
 * 			while (IsOperatorControl()) {
 * 				// robot related code here!
 * 				taskUnlock();	// tell vxWorks that it can switch tasks
 * 				nanosleep(20);  // sleep the task for 20ns. vxWorks marks the task
 * 								// as inactive and moves on to the next one
 * 				taskLock();		// lock vxWorks back to this task
 * 			} 	// do it all over again!
 * 		}
 * 
 * All tasks must inherit from Task2415. The robot specific code (running motors,
 * etc.) will take place in the Main() method, that any subclass of Task2415
 * MUST implement to work sucessfully.
 * 
 */

class Task2415 {
public:
	Task2415(void);
	
	// Incites taskSpawn(), tells vxWorks to add this task to the queue
	void Start(char * id);
	
	// Generic wrapper class that links superclass to subclass defined code
	static int TaskWrapper(void *this_p, int a2, int a3, int a4, int a5,
							int a6, int a7, int a8, int a9, int a10);
	
	// Where the magic happens! Must be implemented by subclass
	virtual int Main(int a2, int a3, int a4, int a5, int a6, int a7,
					  int a8, int a9, int a10) = 0;
};
