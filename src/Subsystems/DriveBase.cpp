#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Subsystems/DriveBase.h>

#include "../RobotMap.h"

DriveBase::DriveBase() : PIDSubsystem("DriveBase", 0.0, 0.0, 0.0) {
	// Use these to get going:
	// SetSetpoint() -  Sets where the PID controller should move the system
	//                  to
	// Enable() - Enables the PID controller.
	currentInputType = PIDInputType::NoPIDInput;
	ahrs = new AHRS(SerialPort::kUSB);
}

double DriveBase::ReturnPIDInput() {
	// Return your input value for the PID loop
	// e.g. a sensor, like a potentiometer:
	// yourPot->SetAverageVoltage() / kYourMaxVoltage;

	switch (currentInputType) {
	case PIDInputType::NoPIDInput:
		return 0;
	case PIDInputType::EncoderPIDInput:

		// Put Encoder input

		return 0;
	case PIDInputType::GyroPIDInput:
		// Use the Yaw values provided by NavX interface
		return ahrs->GetYaw();
		return 0;
	default:
		return 0;
	}
}

void DriveBase::UsePIDOutput(double output) {
	// Use output to drive your system, like a motor
	// e.g. yourMotor->Set(output);
}

void DriveBase::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

void DriveBase::mecanumDrive(double xIn, double yIn, double rotation){

    	setLeftFSpeed(xIn-yIn+rotation);
    	setLeftBSpeed(xIn-yIn-rotation);
    	setRightFSpeed(xIn+yIn+rotation);
    	setRightBSpeed(xIn+yIn-rotation);
    }

void DriveBase::setLeftFSpeed(double speed) {
    	leftFA.Set(speed);
    	leftFB.Set(speed);
    }

void DriveBase::setLeftBSpeed(double speed) {
    	leftBA.Set(speed);
    	leftBA.Set(speed);
    }

void DriveBase::setRightFSpeed(double speed) {
    	rightFA.Set(speed);
    	rightFB.Set(speed);
    }

void DriveBase::setRightBSpeed(double speed) {
    	rightBA.Set(speed);
    	rightBB.Set(speed);
    }



void DriveBase::stop() {
    	setLeftFSpeed(0);
    	setLeftBSpeed(0);
    	setRightFSpeed(0);
    	setRightBSpeed(0);
    }

    // Set the PID controller to get input from the gyro
void DriveBase::setGyroPIDControl(double setpoint) {

    	if(currentInputType != PIDInputType::GyroPIDInput){
    	GetPIDController()->SetInputRange(-180.0,  180.0);
    	GetPIDController()->SetAbsoluteTolerance(kToleranceDegrees);
    	// set PID input from gyro
        currentInputType = PIDInputType::GyroPIDInput;
    	// set PID setpoint

    	// set PID values for gyro
        GetPIDController()->SetPID(gyroP, gyroI, gyroD);
    	// set PID continues
        GetPIDController()->SetContinuous(true);
        GetPIDController()->Enable();
        GetPIDController()->SetSetpoint(setpoint);
    	}

    	SmartDashboard::PutNumber("YAW", ahrs->GetYaw());

    	if(GetPIDController()->OnTarget()){
    		setNoPid();
    	}

    }

    // Set the PID controller to get input from the encoders
void DriveBase::setEncoderPIDControl(double setpoint) {

    	// set PID input from encoder
    	// set PID setpoint
    	// set PID values for encoder
    	// set PID output
    }

void DriveBase::setNoPid(){
    	currentInputType = PIDInputType::NoPIDInput;
    	GetPIDController()->Disable();
    }

void DriveBase::usePIDOutput(double output) {

    	switch (currentInputType) {
    	case PIDInputType::NoPIDInput:
    		break;
		case PIDInputType::EncoderPIDInput:
			break;
		case PIDInputType::GyroPIDInput:
	    	mecanumDrive(output, 0, 0);
	    	break;
		default:
			break;
		}
    }
