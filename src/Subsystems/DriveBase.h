#ifndef DriveBase_H
#define DriveBase_H

#include <Commands/Subsystem.h>

class DriveBase : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

public:
	DriveBase();
	void InitDefaultCommand();
};

#endif  // DriveBase_H
