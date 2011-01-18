#include "Drive2415.h"

Drive2415::Drive2415(void):
			jagUpLeft(DRIVE2415_JUL_PORT), jagUpRight(DRIVE2415_JUR_PORT),
			jagDownLeft(DRIVE2415_JDL_PORT), jagDownRight(DRIVE2415_JDR_PORT) {
	global = Global::GetInstance();
	
	drive = new RobotDrive(jagUpLeft, jagUpRight, jagDownLeft, jagDownRight);
	
	Start("drive2415");
}

int Drive2415::Main(int a2, int a3, int a4, int a5, int a6,
				 int a7, int a8, int a9, int a10) {
	while (*global->GetRobotStatus() == STATUS_TELEOP) {
		drive->TankDrive(global->GetJLeft(), global->GetJRight());
		
		SwapAndWait();
	}
	return 0;
}
