#include "Drive2415.h"

Drive2415::Drive2415(void) {
	global = Global::GetInstance();
	
	jUL = new CANJaguar(DRIVE2415_JUL_PORT);
	jDL = new CANJaguar(DRIVE2415_JDL_PORT);
	jUR = new CANJaguar(DRIVE2415_JUR_PORT);
	jDR = new CANJaguar(DRIVE2415_JDR_PORT);
	
	drive = new RobotDrive(jUL, jDL, jUR, jDR);
	glbDrive = drive;
	
	Start("drive2415");
}

int Drive2415::Main(int a2, int a3, int a4, int a5, int a6,
				 int a7, int a8, int a9, int a10) {
	// We don't want to start until the robot is in teleop mode
	while (!isAwake) { ChillTillAwake(*global->GetRobotStatus()); }	

	while (*global->GetRobotStatus() == STATUS_TELEOP) {
		drive->TankDrive(global->GetJLeft()->GetY(), global->GetJRight()->GetY());
		
		SwapAndWait();
		Wait(STALL_LOOP_TIME);
	}
	return 0;
}

RobotDrive* Drive2415::SendPublicRobotDrive(void) {
	return glbDrive;
}
