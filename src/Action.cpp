#include "Action.h"

Action::Action(std::function<bool()> actionFunc) {
	this->actionFunc = actionFunc;
}

bool Action::run() {
	return actionFunc();
}