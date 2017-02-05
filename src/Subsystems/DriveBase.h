#ifndef DriveBase_H
#define DriveBase_H

#include <Commands/PIDSubsystem.h>
#include "RobotMap.h"
#include <WPILib.h>
#include <Victor.h>

class DriveBase: public PIDSubsystem {
public:

	// Flag for PID controller input type

	enum class PIDInputType {
		NoPIDInput, EncoderPIDInput, GyroPIDInput
	};

	PIDInputType currentInputType;

private:
	// Motors driving front-left mecanum wheel
	Victor* leftFA = new Victor(leftFAChannel);
	Victor* leftFB = new Victor(leftFBChannel);

	// Motors driving back-left mecanum wheel
	Victor* leftBA = new Victor(leftBAChannel);
	Victor* leftBB = new Victor(leftBBChannel);

	// Motors driving front-right mecanum wheel
	Victor* rightFA = new Victor(rightFAChannel);
	Victor* rightFB = new Victor(rightFBChannel);

	// Motors driving back-right mecanum wheel
	Victor* rightBA = new Victor(rightBAChannel);
	Victor* rightBB = new Victor(rightBBChannel);

	//Encoder encoderLeftF = new Encoder(RobotMap.encoderLeftF[0], RobotMap.encoderLeftF[0], false, Encoder.EncodingType.k4X);

//		AHRS ahrs;

	// PID control variables
	static constexpr double gyroP = 0.03;
	static constexpr double gyroI = 0.00;
	static constexpr double gyroD = 0.00;
	//double kF = 0.00;

	double kToleranceDegrees = 2.0;

public:
	DriveBase();
	void UsePIDOutput(double output);
	void InitDefaultCommand();
	void mecanumDrive(double xIn, double yIn, double rotation);
	void stop();
	void setGyroPIDControl(double setpoint);
	void setEncoderPIDControl(double setpoint);
	void setNoPid();
	double ReturnPIDInput();
	void usePIDOutput(double output);

protected:
	void setLeftFSpeed(double speed);
	void setLeftBSpeed(double speed);
	void setRightFSpeed(double speed);
	void setRightBSpeed(double speed);
};

#endif  // DriveBase_H
