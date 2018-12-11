#include "Sequence.h"

bool Sequence::run() {
	for(BehaviorTree *child: this->getChildren())
		if(!child->run())
			return false;
	return true;
}