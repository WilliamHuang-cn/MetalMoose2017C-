#ifndef JoystickTrigger_H
#define JoystickTrigger_H

#include <Buttons/Trigger.h>

class JoystickTrigger : public Trigger {
public:
	JoystickTrigger();
	bool Get() const;
};

#endif  // JoystickTrigger_H
