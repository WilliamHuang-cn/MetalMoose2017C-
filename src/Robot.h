#ifndef ROBOT_H_
#define ROBOT_H_

#include <Commands/Command.h>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>

#include "OI.h"
#include "Subsystems/DriveBase.h"
#include "Subsystems/Gear.h"
#include "Subsystems/Hanger.h"
#include "Subsystems/Shooter.h"

class Robot: public frc::IterativeRobot {
public:

	/*
	// Create a single static instance of all of your subsystems
	static std::shared_ptr<DriveBase> driveBase;
	static std::shared_ptr<Gear> gear;
	static std::shared_ptr<Hanger> hanger;
	static std::shared_ptr<Shooter> shooter;
	static std::unique_ptr<OI> oi;

	static std::shared_ptr<DriveBase> GetdriveBase();

//	static std::unique_ptr<DriveBase> driveBase;
//	static void GetdriveBase();

//	Autonomous autonomousCommand;
//	frc::LiveWindow* lw = frc::LiveWindow::GetInstance();
*/
	void RobotInit() override;
	void DisabledInit() override;
	void DisabledPeriodic() override;

	void AutonomousInit() override;
	void AutonomousPeriodic() override;
	void TeleopInit() override;
	void TeleopPeriodic() override;
	void TestPeriodic() override;

private:
	std::unique_ptr<frc::Command> autonomousCommand;
	frc::SendableChooser<frc::Command*> chooser;
};

#endif  // ROBOT_H_
