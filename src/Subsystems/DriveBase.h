#ifndef DriveBase_H
#define DriveBase_H

#include <Commands/PIDSubsystem.h>
#include "RobotMap.h"
#include <WPILib.h>
#include "AHRS.h"

class DriveBase: public PIDSubsystem {
public:

	// Flag for PID controller input type

	enum class PIDInputType {
		NoPIDInput, EncoderPIDInput, GyroPIDInput
	};

	PIDInputType currentInputType;

	AHRS *ahrs;

private:
	// Motors driving front-left mecanum wheel
	Victor leftFA {leftFAChannel};
	Victor leftFB {leftFBChannel};

	// Motors driving back-left mecanum wheel
	Victor leftBA {leftBAChannel};
	Victor leftBB {leftBBChannel};

	// Motors driving front-right mecanum wheel
	Victor rightFA {rightFAChannel};
	Victor rightFB {rightFBChannel};

	// Motors driving back-right mecanum wheel
	Victor rightBA {rightBAChannel};
	Victor rightBB {rightBBChannel};

	//Encoder encoderLeftF = new Encoder(RobotMap.encoderLeftF[0], RobotMap.encoderLeftF[0], false, Encoder.EncodingType.k4X);

//		AHRS ahrs;

	// PID control variables
	const double gyroP = 0.03;
	const double gyroI = 0.00;
	const double gyroD = 0.00;
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
