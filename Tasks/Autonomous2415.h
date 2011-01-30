#ifndef AUTONOMOUS2415_H_
#define AUTONOMOUS2415_H_

#include "WPILib.h"
#include "CANJaguar.h"
#include "../Task2415.h"
#include "../Global.h"

class Autonomous2415 : public Task2415 {
public:
	Autonomous2415(void);
	
	virtual int Main(int a2, int a3, int a4, int a5, int a6, int a7,
					  int a8, int a9, int a10);
	
private:
	Global *global;
	
	RobotAutonomous *drive;
};

#endif
