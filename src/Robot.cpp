#include "Robot.h"

void Robot::RobotInit() {
	// chooser.AddObject("My Auto", new MyAutoCommand());
	frc::SmartDashboard::PutData("Auto Modes Metal", &chooser);

	// start usbvision thread
	std::thread usbvisionThread(USBVisionThread);
	usbvisionThread.detach();
}

/**
 * This function is called once each time the robot enters Disabled mode.
 * You can use it to reset any subsystem information you want to" clear when
 * the robot is disabled.
 */
void Robot::DisabledInit() {

}

void Robot::DisabledPeriodic() {
	setauxFeature();
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
	setauxFeature();
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
	setauxFeature();
	frc::Scheduler::GetInstance()->Run();
}

void Robot::TestPeriodic() {
	setauxFeature();
//		frc::LiveWindow::GetInstance()->Run();
}

void Robot::setauxFeature() {
	setScanRplidarEnabled();
	setDrawingRplidarMapEnabled();
	setPiplineEnabled();
	sendRobotState();
}

void Robot::setScanRplidarEnabled() {
	isScanRplidarEnabled = IsEnabled();
}

void Robot::setDrawingRplidarMapEnabled() {
	isDrawingRplidarMapEnabled = true;
}

void Robot::setPiplineEnabled() {
	isPiplineEnabled = true;
}

void Robot::sendRobotState() {
	frc::SmartDashboard::PutBoolean("LaserRadarEnabled", isScanRplidarEnabled);
	frc::SmartDashboard::PutBoolean("LaserRadarMapEnabled", isDrawingRplidarMapEnabled);
	frc::SmartDashboard::PutBoolean("ImageProcessingEnabled", isPiplineEnabled);
	frc::SmartDashboard::PutBoolean("VideoEnabled", isVideoEnabled);
	// LaserRadar Status
	frc::SmartDashboard::PutBoolean("LaserRadarIsPoweron", Robot::laserRadar->isValid());
	frc::SmartDashboard::PutBoolean("LaserRadarIsScanning", Robot::laserRadar->isScanning());
}

void Robot::receiveRobotState() {
	isScanRplidarEnabled = frc::SmartDashboard::GetBoolean("LaserRadarEnabled", false);
	isDrawingRplidarMapEnabled = frc::SmartDashboard::GetBoolean("LaserRadarMapEnabled", false);
	isPiplineEnabled = frc::SmartDashboard::GetBoolean("ImageProcessingEnabled", false);
	isVideoEnabled = frc::SmartDashboard::GetBoolean("VideoEnabled", false);
}

bool Robot::isScanRplidarEnabled = true;
bool Robot::isDrawingRplidarMapEnabled = true;
bool Robot::isPiplineEnabled = false;
bool Robot::isVideoEnabled = true;
std::shared_ptr<LaserRadar> Robot::laserRadar = std::make_shared<LaserRadar>("/dev/ttyUSB0");

void Robot::processLidarDatum(cv::Mat& image, char* lastDistance) {

	std::string tempString;
	bool validDistance = false;
	float realtheta, distanceF;

	if (isScanRplidarEnabled) {
		if (laserRadar->Start()) {
			if (laserRadar->readData()) {
				validDistance = laserRadar->getDistanceAt(0, &realtheta, &distanceF,
						1);
				if (validDistance) {
					SmartDashboard::PutNumber("Distance", distanceF / 1000.0);
					sprintf(lastDistance, "%.2fm %dd.", distanceF / 1000.0,
							(int(realtheta + 0.5)) % 360);
				}
			}
			if (isDrawingRplidarMapEnabled)
				laserRadar->drawrRadarDatum(image, lastDistance, validDistance);
		}
		else std::cout << "start radar false.\n";
	} else
		if (! laserRadar->Stop()) std::cout << "stop radar false\n";
}

void Robot::USBVisionThread() {
	char lastDistance[30] = "0.0";

	// Get the USB camera from CameraServer
	// Using default cam0
	cs::UsbCamera camera("USB0", 0);
	CameraServer::GetInstance()->AddCamera(camera);
	// Set the resolution
	camera.SetResolution(640, 480);

//	cs::UsbCamera camera = CameraServer::GetInstance()->StartAutomaticCapture();
	// Set the resolution
//	camera.SetResolution(640, 480);

	// Get a CvSink. This will capture Mats from the Camera
	cs::CvSink cvSink = CameraServer::GetInstance()->GetVideo();
	// Setup a CvSource. This will send images back to the Dashboard
	cs::CvSource outputStream = CameraServer::GetInstance()->PutVideo("USBFeed",
			640, 480);

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

		if (mat.empty())
			std::cout << "image is empty \n";
		processLidarDatum(mat, lastDistance);

		// Give the output stream a new image to display
		if (isVideoEnabled)
			outputStream.PutFrame(mat);
	}

	laserRadar->Stop();
	std::cout << "end thread, closeLidar \n";
}

START_ROBOT_CLASS(Robot);
