#include "Selector.h"

bool Selector::run() {
	for(BehaviorTree *child : this->getChildren())
		if(child->run())
			return true;
	return false;
}