#ifndef WIREDCATS2011_H_
#define WIREDCATS2011_H_

#include "WPILib.h"
#include "Task2415.h"
#include "TaskOne.h"
#include "TaskTwo.h"
#include "TaskThree.h"

class Wiredcats2011 : public SimpleRobot {
public:
	Wiredcats2011();
	void RobotMain();
	void Autonomous();
	void OperatorControl();
};

#endif
