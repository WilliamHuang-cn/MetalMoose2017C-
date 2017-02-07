#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H

#include <memory>
#include <string>

#include <Commands/Command.h>

#include "OI.h"
#include "Subsystems/DriveBase.h"
#include "Subsystems/Gear.h"
#include "Subsystems/Hanger.h"
#include "Subsystems/Shooter.h"

/**
 * The base for all commands. All atomic commands should subclass CommandBase.
 * CommandBase stores creates and stores each control system. To access a
 * subsystem elsewhere in your code in your code use
 * CommandBase::exampleSubsystem
 */
class CommandBase: public frc::Command {
public:
	CommandBase(const std::string& name);
	CommandBase() = default;

	// Create a single static instance of all of your subsystems
	static std::unique_ptr<DriveBase> driveBase;
	static std::unique_ptr<Gear> gear;
	static std::unique_ptr<Hanger> hanger;
	static std::unique_ptr<Shooter> shooter;

	static std::unique_ptr<OI> oi;
};

#endif  // COMMAND_BASE_H
