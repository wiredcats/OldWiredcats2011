#include "Global.h"

Global *Global::myself = 0;

Global::Global(void) {
	printf("in global const\n");
	static bool alreadyRun = false;
	
	if (!alreadyRun) {
		printf("in global already run!\n");
		
		if (GLOBAL_JLEFT_EXISTS)  jLeft  = new Joystick(GLOBAL_JLEFT_PORT);
		if (GLOBAL_JRIGHT_EXISTS) jRight = new Joystick(GLOBAL_JRIGHT_PORT);
		if (GLOBAL_JFAKEX_EXISTS) jFakeX = new Joystick(GLOBAL_JFAKEX_PORT);
		if (GLOBAL_JFAKEY_EXISTS) jFakeY = new Joystick(GLOBAL_JFAKEY_PORT);

		*robotStatus = STATUS_BLANK;
		
		myself = this;
		
		alreadyRun = true;
	}
}

Joystick* Global::GetJLeft()  { return jLeft;  }
Joystick* Global::GetJRight() { return jRight; }
Joystick* Global::GetJFakeX() { return jFakeX; }
Joystick* Global::GetJFakeY() { return jFakeY; }

R_STATUS* Global::GetRobotStatus() { return robotStatus; }
void	  Global::SetRobotStatus(R_STATUS rstat) { printf("chillin\n"); *robotStatus = rstat; }

Global* Global::GetInstance() {
	return myself;
}
