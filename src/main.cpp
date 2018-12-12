#include <iostream>
#include "Game.h"
#include "BehaviorTree.h"
#include "Action.h"
#include "Condition.h"
#include "Sequence.h"
#include "Selector.h"

const int LIMIT_DANGER = -3;

int main(int argc, char const *argv[]) {
	Game g;

	// ----------------- Run Away Sequence ----------------- //

	Condition isThereDanger([&g]() -> bool {
		return g.dangerAt(g.getMe().getRow(), g.getMe().getCol()) > LIMIT_DANGER;
	});

	Action clearMoves([&g]() -> void {
		g.discardMoves();
	});

	Action runAway([&g]() -> void {
		std::cout << g.getMoveOfLesserDanger(g.getMe().getRow(), g.getMe().getCol()) << "\n";
	});

	Sequence runAwaySequence;
	runAwaySequence.addChild(&isThereDanger);
	runAwaySequence.addChild(&clearMoves);
	runAwaySequence.addChild(&runAway);


	// ----------------- Run Plan Sequence ----------------- //

	Condition isThereAPlanning([&g]() -> bool {
		return g.hasMoves();
	});

	Condition isThereATarget([&g]() -> bool {
		return g.isThereTheTargetStill();
	});

	Action runMovesStackTop([&g]() -> void {
		g.move();
	});

	Sequence runPlanSequence;
	runPlanSequence.addChild(&isThereAPlanning);
	runPlanSequence.addChild(&isThereATarget);
	runPlanSequence.addChild(&runMovesStackTop);

	// ----------------- Planning Selector ----------------- //

		// ------------ Bomb Planning Sequence ----------------- //
		Condition isThereABomb([&g]() -> bool {
			return !g.getBombs().empty();
		});

		Condition fourMoreBombsThanMyEnemy([&g]() -> bool {
			return g.getEnemy().getBombs()+4 < g.getMe().getBombs();
		});

		Condition isThereABombNear([&g]() -> bool {
			/* Calculate distance using Manhattan distance */
			size_t bomb = 10000000; // Big number
			for(auto &e : g.getBombs()){
				size_t dist = (
					e.getRow()-g.getMe().getRow() < 0 ?
					-(e.getRow()-g.getMe().getRow()) :
					e.getRow()-g.getMe().getRow()
				);

				dist += (
					e.getCol()-g.getMe().getCol() < 0 ?
					-(e.getCol()-g.getMe().getCol()) :
					e.getCol()-g.getMe().getCol()
				);

				if(dist < bomb)
					bomb = dist;
			}

			size_t snippet = 10000000; // Big number
			for(auto &e : g.getSnippets()) {
				size_t dist = (
					e.getRow()-g.getMe().getRow() < 0 ?
					-(e.getRow()-g.getMe().getRow()) :
					e.getRow()-g.getMe().getRow()
				);

				dist += (
					e.getCol()-g.getMe().getCol() < 0 ?
					-(e.getCol()-g.getMe().getCol()) :
					e.getCol()-g.getMe().getCol()
				);

				if(dist < snippet)
					snippet = dist;
			}

			return bomb < snippet;
		});

		Action planAPath([&g]() -> void {
			g.findPath();
		});

		Sequence bombPlanningSequence;
		bombPlanningSequence.addChild(&isThereABomb);
		bombPlanningSequence.addChild(&fourMoreBombsThanMyEnemy);
		bombPlanningSequence.addChild(&isThereABombNear);
		bombPlanningSequence.addChild(&planAPath);
		bombPlanningSequence.addChild(&runMovesStackTop);

		// ------------ Snippet Planning Sequence -------------- //

		Condition isThereASnippet([&g]() -> bool {
			return !g.getSnippets().empty();
		});

		Sequence snippetPlanningSequence;
		snippetPlanningSequence.addChild(&isThereASnippet);
		snippetPlanningSequence.addChild(&planAPath);
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

	g.setBehaviorTree(&root);
	g.run();
	
	return 0;
}