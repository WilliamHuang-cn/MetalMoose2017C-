#ifndef Hanger_H
#define Hanger_H

#include <Commands/Subsystem.h>

class Hanger : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

public:
	Hanger();
	void InitDefaultCommand();
};

#endif  // Hanger_H
