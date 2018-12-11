#include <iostream>
#include "Game.h"
#include "BehaviorTree.h"
#include "Action.h"
#include "Condition.h"
#include "Sequence.h"
#include "Selector.h"

int main(int argc, char const *argv[]) {
	Game g;

	// ----------------- Run Away Sequence ----------------- //

	Condition isThereDanger([g]() {
		std::cout << "Is there danger?\n";
		return true;
	});

	Action clearMoves([g]{
		std::cout << "Clear moves!\n";
		return true;
	});

	Action runAway([g]{
		std::cout << "Run away!\n";
		return true;
	});

	Sequence runAwaySequence;
	runAwaySequence.addChild(&isThereDanger);
	runAwaySequence.addChild(&clearMoves);
	runAwaySequence.addChild(&runAway);


	// ----------------- Run Plan Sequence ----------------- //

	Condition hasPlanning([g](){
		std::cout << "Does it have a planning?\n";
		return true;
	});

	Condition isThereATarget([g]() {
		std::cout << "Is there a target already?\n";
		return true;
	});

	Action runMovesStackTop([g]() {
		std::cout << "Run move from Moves Stack top!\n";
		return true;
	});

	Sequence runPlanSequence;
	runPlanSequence.addChild(&hasPlanning);
	runPlanSequence.addChild(&isThereATarget);
	runPlanSequence.addChild(&runMovesStackTop);

	// ----------------- Planning Selector ----------------- //

		// ------------ Bomb Planning Sequence ----------------- //
		Condition isThereABomb([g]() {
			std::cout << "Is there a bomb?\n";
			return true;
		});

		Condition fourMoreBombsThanEnemy([g]() {
			std::cout << "Do I have four more bombs than my enemy?\n";
			return true;
		});

		Condition isThereABombNear([g]() {
			std::cout << "Is there a bomb near?\n";
			return true;
		});

		Action planPath([g]() {
			std::cout << "Plan a new path!\n";
			return true;
		});

		Sequence bombPlanningSequence;
		bombPlanningSequence.addChild(&isThereABomb);
		bombPlanningSequence.addChild(&fourMoreBombsThanEnemy);
		bombPlanningSequence.addChild(&isThereABombNear);
		bombPlanningSequence.addChild(&planPath);
		bombPlanningSequence.addChild(&runMovesStackTop);

		// ------------ Snippet Planning Sequence -------------- //

		Condition isThereASnippet([g]() {
			std::cout << "Is there a snippet?\n";
			return true;
		});

		Sequence snippetPlanningSequence;
		snippetPlanningSequence.addChild(&isThereASnippet);
		snippetPlanningSequence.addChild(&planPath);
		snippetPlanningSequence.addChild(&runMovesStackTop);

	Selector planningSelector;
	planningSelector.addChild(&bombPlanningSequence);
	planningSelector.addChild(&snippetPlanningSequence);
	planningSelector.addChild(&runAway);

	// ------------------------- Root -------------------------- //
	Selector root;
	root.addChild(&runAwaySequence);
	root.addChild(&runPlanSequence);
	root.addChild(&planningSelector);

	root.run();
	
	return 0;
}