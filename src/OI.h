#ifndef OI_H
#define OI_H

#include <Buttons/JoystickButton.h>
#include <Joystick.h>

class OI {
public:
	OI();
	frc::Joystick* GetDriverJoystick();
	frc::Joystick* GetOperatorJoystick();

private:
	frc::Joystick driver { 0 };
	frc::Joystick operatorJoy { 1 };

	frc::JoystickButton driverX { &driver, 0 };
	frc::JoystickButton driverA { &driver, 1 };
	frc::JoystickButton driverB { &driver, 2 };
	frc::JoystickButton driverY { &driver, 3 };

	frc::JoystickButton driverLB { &driver, 4 };
	frc::JoystickButton driverRB { &driver, 5 };
	frc::JoystickButton driverLT { &driver, 6 };
	frc::JoystickButton driverRT { &driver, 7 };

	frc::JoystickButton operatorX { &operatorJoy, 0 };
	frc::JoystickButton operatorA { &operatorJoy, 1 };
	frc::JoystickButton operatorB { &operatorJoy, 2 };
	frc::JoystickButton operatorY { &operatorJoy, 3 };

	frc::JoystickButton operatorLB { &operatorJoy, 4 };
	frc::JoystickButton operatorRB { &operatorJoy, 5 };
	frc::JoystickButton operatorLT { &operatorJoy, 6 };
	frc::JoystickButton operatorRT { &operatorJoy, 7 };

/*
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
*/

//DRIVE CODE

//	JoystickTrigger joystickTrigger = JoystickTrigger();
};

#endif  // OI_H
