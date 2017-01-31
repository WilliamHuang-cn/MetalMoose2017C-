#ifndef RopeHang_H
#define RopeHang_H

#include "../CommandBase.h"

class RopeHang : public CommandBase {
public:
	RopeHang();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // RopeHang_H
