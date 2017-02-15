
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
#include "rplidarAPI.h"

extern rplidar_date_t datum[360*2];

class Robot: public frc::IterativeRobot {
public:

/*
std::shared_ptr<DriveBase> Robot::driveBase = std::shared_ptr<DriveBase>(nullptr);
std::shared_ptr<Gear> Robot::gear = std::shared_ptr<Gear>(nullptr);
std::shared_ptr<Hanger> Robot::hanger = std::shared_ptr<Hanger>(nullptr);
std::shared_ptr<Shooter> Robot::shooter = std::shared_ptr<Shooter>(nullptr);
std::unique_ptr<OI> Robot::oi = std::make_unique<OI>();
>>>>>>> refs/heads/master

<<<<<<< HEAD
*/

//std::unique_ptr<DriveBase> Robot::driveBase = std::unique_ptr<DriveBase>(nullptr);		// unique pointer

/*
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
*/

void RobotInit() override {
		// chooser.AddObject("My Auto", new MyAutoCommand());
		frc::SmartDashboard::PutData("Auto Modes", &chooser);

//		std::thread usbvisionThread(USBVisionThread);
}

/**
 * This function is called once each time the robot enters Disabled mode.
 * You can use it to reset any subsystem information you want to clear when
 * the robot is disabled.
 */
void DisabledInit() override {

}

void DisabledPeriodic() override {
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
void AutonomousInit() override {
	/* std::string autoSelected = frc::SmartDashboard::GetString("Auto Selector", "Default");
	if (autoSelected == "My Auto") {
		autonomousCommand.reset(new MyAutoCommand());
>>>>>>> refs/heads/master
	}
	else {
		autonomousCommand.reset(new ExampleCommand());
	} */

	autonomousCommand.reset(chooser.GetSelected());

	if (autonomousCommand.get() != nullptr) {
		autonomousCommand->Start();
	}
}

void AutonomousPeriodic() override {
	frc::Scheduler::GetInstance()->Run();
}

void TeleopInit() override {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// this line or comment it out.
	if (autonomousCommand != nullptr) {
		autonomousCommand->Cancel();
	}
}

void TeleopPeriodic() override {
	frc::Scheduler::GetInstance()->Run();
}

void TestPeriodic() override {
//		frc::LiveWindow::GetInstance()->Run();
}

private:
	std::unique_ptr<frc::Command> autonomousCommand;
	frc::SendableChooser<frc::Command*> chooser;

	static bool isScanRplidarEnabled;
	static bool isDrawingRplidarMapEnabled;
	static bool isPiplineEnabled;
	static RPlidarDriver *RPdrv;

	static u_int nodescount;

	static void USBVisionThread() {
//	    char lastDistance[30];

		// Get the USB camera from CameraServer
		// Using default cam0
		cs::UsbCamera camera = CameraServer::GetInstance()->StartAutomaticCapture();
		// Set the resolution
		camera.SetResolution(640, 480);

		// Get a CvSink. This will capture Mats from the Camera
		cs::CvSink cvSink = CameraServer::GetInstance()->GetVideo();
		// Setup a CvSource. This will send images back to the Dashboard
		cs::CvSource outputStream = CameraServer::GetInstance()->
				PutVideo("USBFeed", 640, 480);

		// Mats are very memory expensive. Lets reuse this Mat.
		cv::Mat mat;

		// Set up Pipeline

		while (true) { 		// May need to end vision while disabled
			// Tell the CvSink to grab a frame from the camera and put it in the source mat.  If there is an error notify the output.
			if (cvSink.GrabFrame(mat) == 0) {
				// Send the output the error.
				outputStream.NotifyError(cvSink.GetError());
				// skip the rest of the current iteration
				continue;
			}
			// Put a rectangle on the image
			//rectangle(mat, cv::Point(100, 100), cv::Point(400, 400),cv::Scalar(255, 255, 255), 5);

//			int temp = -1;

			std::cout << mat;
			std::cout << mat.type();

//			processLidarDatum(&RPdrv, mat, lastDistance);

			// Give the output stream a new image to display
			outputStream.PutFrame(mat);
		}

	    closeLidar(&RPdrv);
	    DriverStation::ReportError("end thread, closeLidar \n");
	}

	static void processLidarDatum(RPlidarDriver** drv, cv::Mat& image, char* lastDistance) {
		const char * opt_com_path;
		int errorCode;
	    opt_com_path = "/dev/ttyUSB0";
	    std::string tempString;
	    bool debugInfo = false;

		if (drv == NULL) return;
		if (isScanRplidarEnabled) {
			if (*drv == NULL) *drv = openLidar(errorCode,opt_com_path,debugInfo);
			if (*drv) {
				if (readData(*drv,debugInfo)) tempString = std::to_string(datum[0].distance);
			}
			if (isDrawingRplidarMapEnabled) drawrpLidarDatum(image, lastDistance,true);
		}
		else closeLidar(drv);
	}

};

START_ROBOT_CLASS(Robot)
