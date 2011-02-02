#include "Autonomous2415.h"

Autonomous2415::Autonomous2415(void) {
	global = Global::GetInstance();
	drive = Drive2415::SendPublicRobotDrive();
	
	lightL = new DigitalInput(2);
	lightM = new DigitalInput(1);
	lightR = new DigitalInput(3);
	
	drive->SetExpiration(0.1);
	
	// IMPORTANT! Choose whether robot should go left or right at the fork
	goRight = true;
	
	driveState = AUTO2415_DRIVE_TILL_OFF;
	polaritySign = 0;
	
	motorSpeed = 0;
	
	Start("auto2415");
}

int Autonomous2415::Main(int a2, int a3, int a4, int a5, int a6,
				 int a7, int a8, int a9, int a10) {
	while (keepTaskAlive) {
		// we don't want to start until the robot is in teleop mode
		while (!isAwake) {
			ResetTask();
			ChillTillAwake(*global->GetRobotStatus());
		}	
	
		bool left, middle, right;
		bool goRight = true;
		
		int driveState = AUTO2415_DRIVE_TILL_OFF;
		int polaritySign = 0;
		
		float speed = 0;
		
		drive->SetSafetyEnabled(true);
		
		while (*global->GetRobotStatus() == STATUS_AUTONOMOUS) {
			// grab photosensor values
			left = lightL->Get() ? 1 : 0;
			middle = lightM->Get() ? 1 : 0;
			right = lightR->Get() ? 1 : 0;
			
			switch (driveState) {
			case AUTO2415_DRIVE_TILL_OFF: 
				motorSpeed = AUTO2415_TANK_SPEED;
				
				// here we are either on the middle or have nothing
				// either way, go straight till we find something
				if (left || right) {
					if (goRight) polaritySign = right ? 1 : -1; // decide if we want to go left or right
					else		 polaritySign = left ? -1 : 1;  // at the fork
					
					driveState = 1;
					killTimer->Start();
				}
				
				drive->TankDrive(-motorSpeed, -motorSpeed);
				break;
			case AUTO2415_TURN_TILL_ON:
				motorSpeed = polaritySign * AUTO2415_TANK_SPEED;		// pick polarity, go left or right
				
				// if we hit the middle, we wanna go straight again
				if (middle) {
					printf("entering driveState [0] from [1]\n");
					driveState = 0;
					killTimer->Stop();
					killTimer->Reset();
				} else {
					// keep turning until we hit the middle, but if we go too long
					// kill the autonomous (something probably messed up)
					if (killTimer->HasPeriodPassed(AUTO2415_KILLSWITCH_TIME)) {
						printf("entering driveState [2] from [1]\n");
						driveState = 2;
					} else {
						drive->TankDrive(motorSpeed, -motorSpeed);
					}
				}
				break;
			case AUTO2415_KILL_AUTO:
				// we've been turning too long with no middle value, let's cut our losses here
				drive->Drive(0.0, 0.0);
				break;
			default:
				drive->Drive(0.0, 0.0);
				break;
			}
	
			SwapAndWait();
		}
	}
	
	return 0;
}

void Autonomous2415::ForceAwake(void) {
	isAwake = true;
}
