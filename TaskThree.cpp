#include "TaskThree.h"

TaskThree::TaskThree(void) {
	Start((char *) "taskThree");
	return;
}

int TaskThree::Main(int a2, int a3, int a4, int a5, int a6,
				   int a7, int a8, int a9, int a10) {
	int i = 0;
	while (i < 100) {
		printf("[%d] chillin' in TaskThree!\n", i);
		i++;
		SwapAndWait();
	}
	return 0;
}
