#include "alarm.h"

//#include "aclock.h"

int main(void) {

//	LedSwitchOn(2);

	initAlarm();


	while(1) {
		I2CTransfer();
		DisplayErase();

		btnVal = ButtonRead();
		tchVal = InputGetSensorValue(PORT_TOUCH);

		manageButton();
		manageTouchFront();
		manageMotors();
		
		manageMonitor();
		DisplayUpdateSync();
	}

	return 0;
}
