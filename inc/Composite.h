#ifndef COMPOSITE_H
#define COMPOSITE_H

#include <vector>
#include "BehaviorTree.h"

class Composite : public BehaviorTree {
private:
	std::vector<BehaviorTree*> children;

public:
	void addChild(BehaviorTree*);
	std::vector<BehaviorTree*>& getChildren();
};

#endif