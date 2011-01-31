#include "Autonomous2415.h"

Autonomous2415::Autonomous2415(void) {
	global = Global::GetInstance();
	drive = Drive2415::SendPublicRobotDrive();
	
	lightL = new DigitalInput(2);
	lightM = new DigitalInput(1);
	lightR = new DigitalInput(3);
	
	drive->SetExpiration(0.1);
	
	Start("auto2415");
}

int Autonomous2415::Main(int a2, int a3, int a4, int a5, int a6,
				 int a7, int a8, int a9, int a10) {
	// We don't want to start until the robot is in teleop mode
	while (!isAwake) { ChillTillAwake(*global->GetRobotStatus()); }	

	bool left, middle, right;
	
	int autoState = 0;
	int sign = 0;
	
	float speed = 0;
	
	drive->SetSafetyEnabled(true);
	
	while (*global->GetRobotStatus() == STATUS_AUTONOMOUS) {
		left = lightL->Get() ? 1 : 0;
		middle = lightM->Get() ? 1 : 0;
		right = lightR->Get() ? 1 : 0;
		
		switch (autoState) {
		case 0:
			if (left || right) {
				sign = right ? 1 : -1;
				
				autoState = 1;
				killTimer->Start();
				delayTimer->Start();
			}
			
			drive->TankDrive(-AUTO2415_TANK_SPEED, -AUTO2415_TANK_SPEED);
			break;
		case 1:
			speed = sign * AUTO2415_TANK_SPEED;
			
			if (middle) {
				printf("entering autoState [0] from [1]\n");
				autoState = 0;
				killTimer->Stop();
				killTimer->Reset();
			}
			
			if (!delayTimer->HasPeriodPassed(AUTO2415_DELAY_TIME)) {
				drive->TankDrive(speed, -speed);
			} else {
				delayTimer->Stop();
				delayTimer->Reset();
				if (killTimer->HasPeriodPassed(AUTO2415_KILLSWITCH_TIME)) {
					printf("entering autoState [2] from [1]\n");
					autoState = 2;
				} else {
					drive->TankDrive(speed, -speed);
				}
			}
			break;
		case 2:
			drive->Drive(0.0, 0.0);
			break;
		default:
			drive->Drive(0.0, 0.0);
			break;
		}

		SwapAndWait();
	}
	return 0;
}
