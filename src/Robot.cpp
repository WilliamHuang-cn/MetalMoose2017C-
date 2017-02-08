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

#include "rplidarAPI.h"

extern rplidar_date_t datum[360*2];

class Robot: public frc::IterativeRobot {

public:

	void RobotInit() override {
		// chooser.AddObject("My Auto", new MyAutoCommand());
		frc::SmartDashboard::PutData("Auto Modes", &chooser);
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

	static void USBVisionThread() {
	    char lastDistance[30];

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

			int temp = -1;

			processLidarDatum(&RPdrv, mat, lastDistance);

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
			if (isDrawingRplidarMapEnabled) drawrpLidarDatum(image, lastDistance);
		}
		else closeLidar(drv);
	}

	static void drawrpLidarDatum(cv::Mat& image, char* lastDistance) {
		cv::Point beginPoint;
		cv::Point endPoint;
		unsigned i;
		float pi =3.1415926;
		float distance;
		cv::Scalar lineColor;
		float theata;
		std::string tempString;

		cv::Scalar RedColor = cv::Scalar(0,0,255);
		cv::Scalar GreenColor = cv::Scalar(0,255,0);
		cv::Scalar BlueColor = cv::Scalar(255,0,0);
		cv::Scalar GreyColor = cv::Scalar(200,200,200);
		cv::Scalar ValidColor = BlueColor;
		cv::Scalar InValidColor = GreyColor;

		// scale for display mm * scale
		float scale = 0.04;
		// center of Image (default is 640 X 480)
		int center_x = 320;
		int center_y =240;
		// Center point
		beginPoint = cv::Point(center_x,center_y);

		cv::putText(image, lastDistance, cv::Point(10,50), cv::FONT_HERSHEY_SIMPLEX, 1, GreenColor);

		for (i = 0; i < nodescount ; i++) {
			theata = datum[i].theta;

			// display zero degree distance value at upleft corner if changed
			if ((theata < 0.5) || (theata > 359.5)) {
				if (datum[i].quality > 0)
				{
					// formate display string
					sprintf(lastDistance, "%.3f",datum[i].distance / 1000.0 );
				}
				cv::putText(image, lastDistance, cv::Point(10,50), cv::FONT_HERSHEY_SIMPLEX, 1, GreenColor);
			}

			if (datum[i].quality > 0) {
				lineColor = ValidColor;
				distance = datum[i].distance;
			}
			else {
				lineColor = InValidColor;
				distance = 500;
			}

			endPoint = cv::Point(distance*cos((datum[i].theta - 90)*pi/180)*scale + center_x,
								distance*sin((datum[i].theta - 90)*pi/180)*scale + center_y);
			cv::line(image,beginPoint,endPoint,lineColor,1);
		}

		// Distances Mark 2m, 4m, 6m, 8m
		for (i = 1; i <= 4; i++)
		{
			distance = 2000*i ;
			endPoint = cv::Point(distance*cos(- 45*pi/180)*scale + center_x,
							distance*sin(-45*pi/180)*scale + center_y);

			// draw circle
			cv::circle(image,beginPoint,distance*scale,GreenColor,1);
			tempString = std::to_string(i*2) + "m";

			// draw scale
			cv::putText(image, tempString, endPoint, cv::FONT_HERSHEY_SIMPLEX, 0.4, GreenColor);

			// draw zero scale
			int segLine = 10;
			endPoint = cv::Point(distance*cos(- 90*pi/180)*scale + center_x,
										distance*sin(-90*pi/180)*scale + center_y);

			cv::line(image, cv::Point(endPoint.x, endPoint.y - segLine),
					cv::Point(endPoint.x, endPoint.y + segLine), RedColor, 2);
		}

		//cv::line(image,beginPoint,endPoint,lineColor,2);
	}


};

START_ROBOT_CLASS(Robot)
