#ifndef CONDITION_H
#define CONDITION_H

#include <functional>
#include "BehaviorTree.h"

class Condition : public BehaviorTree {
private:
	std::function<bool()> conditionFunc;
	
public:
	Condition(std::function<bool()>);
	bool run();
};

#endif