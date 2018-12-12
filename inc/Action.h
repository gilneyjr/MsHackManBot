#ifndef ACTION_H
#define ACTION_H

#include <functional>
#include "BehaviorTree.h"

class Action : public BehaviorTree {
private:
	std::function<void()> actionFunc;
	
public:
	Action(std::function<void()>);
	bool run();
};

#endif