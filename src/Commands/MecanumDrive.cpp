#include "MecanumDrive.h"
#include "OI.h"

MecanumDrive::MecanumDrive() : CommandBase("MecanumDrive"){
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
//	Requires(driveBase.get());

	// if driveBase is shared_ptr
	Requires(CommandBase::GetdriveBase().get());

	// if driveBase is unique_ptr
//	Robot::GetdriveBase();
//	Requires(Robot::driveBase.get());
}

// Called just before this Command runs the first time
void MecanumDrive::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void MecanumDrive::Execute() {
	double xIn = CommandBase::oi->GetDriverJoystick()->GetAxis(frc::Joystick::AxisType::kXAxis);
	double yIn = CommandBase::oi->GetDriverJoystick()->GetAxis(frc::Joystick::AxisType::kThrottleAxis);
	double zIn = CommandBase::oi->GetDriverJoystick()->GetAxis(frc::Joystick::AxisType::kZAxis);

	CommandBase::driveBase->mecanumDrive(xIn, yIn, zIn);
}

// Make this return true when this Command no longer needs to run execute()
bool MecanumDrive::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void MecanumDrive::End() {

	CommandBase::driveBase->stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MecanumDrive::Interrupted() {
	End();
}
