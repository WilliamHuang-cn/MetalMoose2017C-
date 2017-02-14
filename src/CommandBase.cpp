#include "CommandBase.h"

#include <Commands/Scheduler.h>


// Initialize a single static instance of all of your subsystems. The following
// line should be repeated for each subsystem in the project.
//std::unique_ptr<ExampleSubsystem> CommandBase::exampleSubsystem =
//		std::make_unique<ExampleSubsystem>();

std::shared_ptr<DriveBase> CommandBase::driveBase = std::shared_ptr<DriveBase>(nullptr);
//std::unique_ptr<DriveBase> CommandBase::driveBase = std::make_unique<DriveBase>();
std::shared_ptr<Gear> CommandBase::gear = std::shared_ptr<Gear>(nullptr);
std::shared_ptr<Hanger> CommandBase::hanger = std::shared_ptr<Hanger>(nullptr);
std::shared_ptr<Shooter> CommandBase::shooter = std::shared_ptr<Shooter>(nullptr);
std::unique_ptr<OI> CommandBase::oi = std::make_unique<OI>();

//std::unique_ptr<DriveBase> Robot::driveBase = std::unique_ptr<DriveBase>(nullptr);		// unique pointer

std::shared_ptr<DriveBase> CommandBase::GetdriveBase() {
	if (driveBase.get() == nullptr)
		driveBase = std::make_shared<DriveBase>();
	return driveBase;
}

// Note: unique pointer can not be return by GetdriveBase !
//void Robot::GetdriveBase() {
//	if (driveBase.get() == nullptr)
//		driveBase = std::move(std::make_unique<DriveBase>());
//}

CommandBase::CommandBase(const std::string &name) :
		frc::Command(name) {
}

