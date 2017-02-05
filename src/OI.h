#ifndef OI_H
#define OI_H


#include <WPILib.h>

class OI {
public:

	static const Joystick* driver;
	static const Joystick* operatorJoy;

	static const JoystickButton* driverX;
	static const JoystickButton* driverA;
	static const JoystickButton* driverB;
	static const JoystickButton* driverY;

	static const JoystickButton* driverLB;
	static const JoystickButton* driverRB;
	static const JoystickButton* driverLT;
	static const JoystickButton* driverRT;

	static const JoystickButton* operatorX;
	static const JoystickButton* operatorA;
	static const JoystickButton* operatorB;
	static const JoystickButton* operatorY;

	static const JoystickButton* operatorLB;
	static const JoystickButton* operatorRB;
	static const JoystickButton* operatorLT;
	static const JoystickButton* operatorRT;

//DRIVE CODE

//	JoystickTrigger joystickTrigger = JoystickTrigger();

	OI();
};

#endif  // OI_H
