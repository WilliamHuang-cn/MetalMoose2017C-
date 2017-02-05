#include "OI.h"

//#include <WPILib.h>

OI::OI() {
	// Process operator interface input here.
//	driver = new Joystick(0);
	operatorJoy = new Joystick(1);

	//

	driverX = new JoystickButton(driver, 0);
	driverA = new JoystickButton(driver, 1);
	driverB = new JoystickButton(driver, 2);
	driverY = new JoystickButton(driver, 3);
	driverLB = new JoystickButton(driver, 4);
	driverRB = new JoystickButton(driver, 5);
	driverLT = new JoystickButton(driver, 6);
	driverRT = new JoystickButton(driver, 7);

	operatorX = new JoystickButton(operatorJoy, 0);
	operatorA = new JoystickButton(operatorJoy, 1);
	operatorB = new JoystickButton(operatorJoy, 2);
	operatorY = new JoystickButton(operatorJoy, 3);

	operatorLB = new JoystickButton(operatorJoy, 4);
	operatorRB = new JoystickButton(operatorJoy, 5);
	operatorLT = new JoystickButton(operatorJoy, 6);
	operatorRT = new JoystickButton(operatorJoy, 7);
}
