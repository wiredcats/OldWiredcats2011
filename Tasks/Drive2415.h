#ifndef DRIVE2415_H_
#define DRIVE2415_H_

#include "WPILib.h"
#include "CANJaguar.h"
#include "../Task2415.h"
#include "../Global.h"

#define DRIVE2415_JUL_PORT (1)
#define DRIVE2415_JUR_PORT (2)
#define DRIVE2415_JDL_PORT (3)
#define DRIVE2415_JDR_PORT (4)

class Drive2415 : public Task2415 {
public:
	Drive2415(void);
	
	virtual int Main(int a2, int a3, int a4, int a5, int a6, int a7,
					  int a8, int a9, int a10);
	
private:
	Global *global;
	
	CANJaguar  jagUpLeft;
	CANJaguar  jagUpRight;
	CANJaguar  jagDownLeft;
	CANJaguar  jagDownRight;
	
	RobotDrive *drive;
};

#endif
