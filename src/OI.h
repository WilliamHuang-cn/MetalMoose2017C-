#ifndef OI_H
#define OI_H

#include <WPILib.h>
#include <Buttons/JoystickButton.h>
#include <Joystick.h>

//using namespace frc;

class OI {
public:

	static Joystick* driver;
	static Joystick* operatorJoy;

	static JoystickButton *driverX;
	static JoystickButton* driverA;
	static JoystickButton* driverB;
	static JoystickButton* driverY;

	static JoystickButton* driverLB;
	static JoystickButton* driverRB;
	static JoystickButton* driverLT;
	static JoystickButton* driverRT;

	static JoystickButton* operatorX;
	static JoystickButton* operatorA;
	static JoystickButton* operatorB;
	static JoystickButton* operatorY;

	static JoystickButton* operatorLB;
	static JoystickButton* operatorRB;
	static JoystickButton* operatorLT;
	static JoystickButton* operatorRT;

//DRIVE CODE

//	JoystickTrigger joystickTrigger = JoystickTrigger();

	OI();
};

#endif  // OI_H
