#include "Robot.h"

#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

std::shared_ptr<DriveBase> Robot::driveBase = std::shared_ptr<DriveBase>(nullptr);
std::shared_ptr<Gear> Robot::gear = std::shared_ptr<Gear>(nullptr);
std::shared_ptr<Hanger> Robot::hanger = std::shared_ptr<Hanger>(nullptr);
std::shared_ptr<Shooter> Robot::shooter = std::shared_ptr<Shooter>(nullptr);
std::unique_ptr<OI> Robot::oi = std::make_unique<OI>();

//std::unique_ptr<DriveBase> Robot::driveBase = std::unique_ptr<DriveBase>(nullptr);		// unique pointer

std::shared_ptr<DriveBase> Robot::GetdriveBase() {
	if (driveBase.get() == nullptr)
		driveBase = std::make_shared<DriveBase>();
	return driveBase;
}

// Note: unique pointer can not be return by GetdriveBase !
//void Robot::GetdriveBase() {
//	if (driveBase.get() == nullptr)
//		driveBase = std::move(std::make_unique<DriveBase>());
//}

void Robot::RobotInit() {
	// chooser.AddObject("My Auto", new MyAutoCommand());
	frc::SmartDashboard::PutData("Auto Modes", &chooser);
}

/**
 * This function is called once each time the robot enters Disabled mode.
 * You can use it to reset any subsystem information you want to clear when
 * the robot is disabled.
 */
void Robot::DisabledInit() {

}

void Robot::DisabledPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable
 * chooser code works with the Java SmartDashboard. If you prefer the
 * LabVIEW Dashboard, remove all of the chooser code and uncomment the
 * GetString code to get the auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional commands to the
 * chooser code above (like the commented example) or additional comparisons
 * to the if-else structure below with additional strings & commands.
 */
void Robot::AutonomousInit() {
	/* std::string autoSelected = frc::SmartDashboard::GetString("Auto Selector", "Default");
	if (autoSelected == "My Auto") {
		autonomousCommand.reset(new MyAutoCommand());
	}
	else {
		autonomousCommand.reset(new ExampleCommand());
	} */

	autonomousCommand.reset(chooser.GetSelected());

	if (autonomousCommand.get() != nullptr) {
		autonomousCommand->Start();
	}
}

void Robot::AutonomousPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// this line or comment it out.
	if (autonomousCommand != nullptr) {
		autonomousCommand->Cancel();
	}
}

void Robot::TeleopPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

void Robot::TestPeriodic() {
//		frc::LiveWindow::GetInstance()->Run();
}

START_ROBOT_CLASS(Robot)
