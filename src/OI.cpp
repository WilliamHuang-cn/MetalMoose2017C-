#include "OI.h"

using namespace frc;

OI::OI() {
	/*
	frc::SmartDashboard::PutData("Open Claw", new OpenClaw());
	frc::SmartDashboard::PutData("Close Claw", new CloseClaw());

	// Connect the buttons to commands
	d_up.WhenPressed(new SetElevatorSetpoint(0.2));
	d_down.WhenPressed(new SetElevatorSetpoint(-0.2));
	d_right.WhenPressed(new CloseClaw());
	d_left.WhenPressed(new OpenClaw());

	r1.WhenPressed(new PrepareToPickup());
	r2.WhenPressed(new Pickup());
	l1.WhenPressed(new Place());
	l2.WhenPressed(new Autonomous());*/
}

frc::Joystick* OI::GetDriverJoystick() {
	return &driver;
}

frc::Joystick* OI::GetOperatorJoystick() {
	return &operatorJoy;
}
