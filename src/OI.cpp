#include "OI.h"

using namespace frc;

OI::OI() {
	// Process operator interface input here.
	OI::driver = &_driver;
	OI::operatorJoy = &_operator;

	OI::driverX = &_driverX;
	OI::driverA = &_driverA;
	OI::driverB = &_driverB;
	OI::driverY = &_driverY;
	OI::driverLB = &_driverLB;
	OI::driverRB = &_driverRB;
	OI::driverLT = &_driverLT;
	OI::driverRT = &_driverRT;

	OI::operatorX = &_operatorX;
	OI::operatorA = &_operatorA;
	OI::operatorB = &_operatorB;
	OI::operatorY = &_operatorY;

	OI::operatorLB = &_operatorLB;
	OI::operatorRB = &_operatorRB;
	OI::operatorLT = &_operatorLT;
	OI::operatorRT = &_operatorRT;
}
