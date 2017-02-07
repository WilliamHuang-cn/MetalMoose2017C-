#ifndef OI_H
#define OI_H

//#include <WPILib.h>
#include <Buttons/JoystickButton.h>
#include <Joystick.h>

class OI {
private:

	Joystick _driver {0};
	Joystick _operator {1};

	JoystickButton _driverX {&_driver,0};
	JoystickButton _driverA {&_driver,1};
	JoystickButton _driverB {&_driver,2};
	JoystickButton _driverY {&_driver,3};

	JoystickButton _driverLB {&_driver,4};
	JoystickButton _driverRB {&_driver,5};
	JoystickButton _driverLT {&_driver,6};
	JoystickButton _driverRT {&_driver,7};

	JoystickButton _operatorX {&_operator,0};
	JoystickButton _operatorA {&_operator,1};
	JoystickButton _operatorB {&_operator,2};
	JoystickButton _operatorY {&_operator,3};

	JoystickButton _operatorLB {&_operator,4};
	JoystickButton _operatorRB {&_operator,5};
	JoystickButton _operatorLT {&_operator,6};
	JoystickButton _operatorRT {&_operator,7};

//DRIVE CODE

//	JoystickTrigger joystickTrigger = JoystickTrigger();
public:
	OI();
	Joystick *driver;
	Joystick *operatorJoy;

	JoystickButton *driverX;
	JoystickButton *driverA;
	JoystickButton *driverB;
	JoystickButton *driverY;

	JoystickButton *driverLB;
	JoystickButton *driverRB;
	JoystickButton *driverLT;
	JoystickButton *driverRT;

	JoystickButton *operatorX;
	JoystickButton *operatorA;
	JoystickButton *operatorB;
	JoystickButton *operatorY;

	JoystickButton *operatorLB;
	JoystickButton *operatorRB;
	JoystickButton *operatorLT;
	JoystickButton *operatorRT;
};

#endif  // OI_H
