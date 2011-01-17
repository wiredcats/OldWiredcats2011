#pragma once

#include "WPILib.h"
#include "Task2415.h"
#include "TaskOne.h"
#include "Global.h"

class Wiredcats2011 : public SimpleRobot {
private:
	Global *global;
public:
	Wiredcats2011();
	void Disabled();
	void Autonomous();
	void OperatorControl();
};
