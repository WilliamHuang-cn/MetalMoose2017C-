#ifndef GearRelease_H
#define GearRelease_H

#include "../CommandBase.h"

class GearRelease : public CommandBase {
public:
	GearRelease();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // GearRelease_H
