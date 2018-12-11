#include "Composite.h"

void Composite::addChild(BehaviorTree *child) {
	children.push_back(child);
}

std::vector<BehaviorTree*>& Composite::getChildren() {
	return children;
}