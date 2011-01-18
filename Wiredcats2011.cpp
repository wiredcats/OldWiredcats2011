#include "Wiredcats2011.h"

Global global;

#include "Tasks.h"

Wiredcats2011::Wiredcats2011(void) {
	global = Global::GetInstance();
	global->SetRobotStatus(STATUS_CONST);
}

void Wiredcats2011::Disabled(void) {
	global->SetRobotStatus(STATUS_DISABLED);
	
	// disabled shiz
}

void Wiredcats2011::Autonomous(void) {
	global->SetRobotStatus(STATUS_AUTONOMOUS);
}

void Wiredcats2011::OperatorControl(void) {
	global->SetRobotStatus(STATUS_TELEOP);
}

START_ROBOT_CLASS(Wiredcats2011);
