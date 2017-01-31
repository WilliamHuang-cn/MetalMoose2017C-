#ifndef Gear_H
#define Gear_H

#include <Commands/Subsystem.h>

class Gear : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

public:
	Gear();
	void InitDefaultCommand();
};

#endif  // Gear_H
