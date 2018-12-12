#include "Action.h"

Action::Action(std::function<void()> actionFunc) {
	this->actionFunc = actionFunc;
}

bool Action::run() {
	actionFunc();
	return true;
}