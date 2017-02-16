#ifndef ROBOT_H_
#define ROBOT_H_
#include <memory>

#include <thread>

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <stdlib.h>

#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

#include <CameraServer.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/types.hpp>

#include "CommandBase.h"
#include "LaserRadar.h"

class Robot: public frc::IterativeRobot {
public:

	/*
	// Create a single static instance of all of your subsystems
	static std::shared_ptr<DriveBase> driveBase;
	static std::shared_ptr<Gear> gear;
	static std::shared_ptr<Hanger> hanger;
	static std::shared_ptr<Shooter> shooter;
	static std::unique_ptr<OI> oi;

	static std::shared_ptr<LaserRadar> laserRadar;

//	static std::shared_ptr<DriveBase> GetdriveBase();

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
	static std::shared_ptr<LaserRadar> laserRadar;

	static bool isScanRplidarEnabled;
	static bool isDrawingRplidarMapEnabled;
	static bool isPiplineEnabled;
	static bool isVideoEnabled;
	static void USBVisionThread();
	static void processLidarDatum(cv::Mat& image, char* lastDistance);

	void setauxFeature();
	void setScanRplidarEnabled();
	void setDrawingRplidarMapEnabled();
	void setPiplineEnabled();
};

#endif  // ROBOT_H_
