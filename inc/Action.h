#ifndef ACTION_H
#define ACTION_H

#include <functional>
#include "BehaviorTree.h"

class Action : public BehaviorTree {
private:
	std::function<bool()> actionFunc;
	
public:
	Action(std::function<bool()>);
	bool run();
};

#endif