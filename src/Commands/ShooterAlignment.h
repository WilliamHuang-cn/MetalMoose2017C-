#ifndef ShooterAlignment_H
#define ShooterAlignment_H

#include "../CommandBase.h"

class ShooterAlignment : public CommandBase {
public:
	ShooterAlignment();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // ShooterAlignment_H
