#include "MecanumDrive.h"
#include "Robot.h"
#include "OI.h"

MecanumDrive::MecanumDrive() : CommandBase("MecanumDrive"){
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::driveBase.get());
}

// Called just before this Command runs the first time
void MecanumDrive::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void MecanumDrive::Execute() {
	double xIn = Robot::oi->GetDriverJoystick()->GetAxis(frc::Joystick::AxisType::kXAxis);
	double yIn = Robot::oi->GetDriverJoystick()->GetAxis(frc::Joystick::AxisType::kThrottleAxis);
	double zIn = Robot::oi->GetDriverJoystick()->GetAxis(frc::Joystick::AxisType::kZAxis);

	Robot::driveBase->mecanumDrive(xIn, yIn, zIn);
}

// Make this return true when this Command no longer needs to run execute()
bool MecanumDrive::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void MecanumDrive::End() {

	driveBase->stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MecanumDrive::Interrupted() {
	End();
}
