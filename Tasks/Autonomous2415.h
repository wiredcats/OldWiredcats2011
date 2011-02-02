#ifndef AUTONOMOUS2415_H_
#define AUTONOMOUS2415_H_

#include "WPILib.h"
#include "CANJaguar.h"
#include "../Task2415.h"
#include "../Global.h"
#include "Drive2415.h"

#define AUTO2415_DRIVE_TILL_OFF (1)
#define AUTO2415_TURN_TILL_ON (2)
#define AUTO2415_KILL_AUTO (3)

const float AUTO2415_TANK_SPEED = 0.425;
const float AUTO2415_KILLSWITCH_TIME = 1.8;

class Autonomous2415 : public Task2415 {
public:
	Autonomous2415(void);
	
	virtual int Main(int a2, int a3, int a4, int a5, int a6, int a7,
					  int a8, int a9, int a10);
	
	void ForceAwake();
	
private:
	Global *global;
	RobotDrive *drive;
	
	Timer *killTimer;
	
	DigitalInput *lightL, *lightM, *lightR;
	
	// performance specific variables
	bool left, middle, right;
	bool goRight;
	
	int driveState;
	int polaritySign;
	
	float motorSpeed;
};

#endif
