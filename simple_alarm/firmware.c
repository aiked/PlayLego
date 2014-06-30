#include "alarm.h"

//#include "aclock.h"

int main(void) {

//	LedSwitchOn(2);

	initAlarm();


	while(1) {
		I2CTransfer();
		DisplayErase();

		btnVal = ButtonRead();
		tchFrontVal = InputGetSensorValue(PORT_TOUCHFRONT);
		tchBackVal = InputGetSensorValue(PORT_TOUCHBACK);

		manageButton();
		manageTouch();
		manageMotors();
		
		manageMonitor();
		DisplayUpdateSync();
	}

	return 0;
}
