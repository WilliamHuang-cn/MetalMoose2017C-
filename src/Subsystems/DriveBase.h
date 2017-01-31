#ifndef DriveBase_H
#define DriveBase_H

#include <Commands/PIDSubsystem.h>
#include "RobotMap.h"

class DriveBase: public PIDSubsystem {
public:

	// Flag for PID controller input type

	enum class PIDInput {
		NoPIDInput, EncoderPIDInput, GyroPIDInput
	};

	PIDInput currentInputType;

	// Motors driving front-left mecanum wheel
	Victor leftFA = Victor(leftFA);
	Victor leftFB = Victor(leftFB);

	// Motors driving back-left mecanum wheel
	Victor leftBA = Victor(leftBA);
	Victor leftBB = Victor(leftBB);

	// Motors driving front-right mecanum wheel
	Victor rightFA = Victor(rightFA);
	Victor rightFB = Victor(rightFB);

	// Motors driving back-right mecanum wheel
	Victor rightBA = Victor(rightBA);
	Victor rightBB = Victor(rightBB);

	//Encoder encoderLeftF = new Encoder(RobotMap.encoderLeftF[0], RobotMap.encoderLeftF[0], false, Encoder.EncodingType.k4X);

//		AHRS ahrs;

	// PID control variables
	static double gyroP = 0.03;
	static double gyroI = 0.00;
	static double gyroD = 0.00;
	//double kF = 0.00;

	double kToleranceDegrees = 2.0;

	DriveBase();
	double ReturnPIDInput();
	void UsePIDOutput(double output);
	void InitDefaultCommand();
};

#endif  // DriveBase_H
