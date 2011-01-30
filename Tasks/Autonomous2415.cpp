#include "Autonomous2415.h"

Autonomous2415::Autonomous2415(void) {
	global = Global::GetInstance();
	
	Start("auto2415");
}

int Autonomous2415::Main(int a2, int a3, int a4, int a5, int a6,
				 int a7, int a8, int a9, int a10) {
	// We don't want to start until the robot is in teleop mode
	while (!isAwake) { ChillTillAwake(global->GetRobotStatus()); }	

	while (*global->GetRobotStatus() == STATUS_AUTONOMOUS) {
		

		SwapAndWait();
	}
	return 0;
}
