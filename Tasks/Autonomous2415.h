#ifndef AUTONOMOUS2415_H_
#define AUTONOMOUS2415_H_

#include "WPILib.h"
#include "CANJaguar.h"
#include "../Task2415.h"
#include "../Global.h"
#include "Drive2415.h"

const float AUTO2415_TANK_SPEED = 0.425;
const float AUTO2415_DELAY_TIME = 0.8;
const float AUTO2415_KILLSWITCH_TIME = 2 * AUTO2415_DELAY_TIME;

class Autonomous2415 : public Task2415 {
public:
	Autonomous2415(void);
	
	virtual int Main(int a2, int a3, int a4, int a5, int a6, int a7,
					  int a8, int a9, int a10);
	
private:
	Global *global;
	RobotDrive *drive;
	
	Timer *delayTimer, *killTimer;
	
	DigitalInput *lightL, *lightM, *lightR;
};

#endif
