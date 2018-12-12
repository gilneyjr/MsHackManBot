#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include "Point.h"
#include "Snippet.h"
#include "Bug.h"
#include "Spawn.h"
#include "Bomb.h"
#include "Player.h"
#include "BehaviorTree.h"

class Game {
private:
	int timebank;
	int time_per_move;
	int max_rounds;
	size_t field_width;
	size_t field_height;
	int round;
	std::vector<bool> field;
	std::vector<int> danger;
	std::vector<Snippet> snippets;
	std::vector<Bug> bugs;
	std::vector<Spawn> spawns;
	std::vector<Bomb> bombs;
	std::stack<std::string> moves;
	BehaviorTree* tree;

	Player me;
	Player enemy;

	Point leftGate;
	Point rightGate;
	Point target;

	void settings();
	void resetField();
	bool saveCellType(std::string &, size_t, size_t);
	void update();
	void action();
	void calculateDanger(size_t, size_t);
	std::vector<size_t> getAdj(size_t pos, bool gate);
	int heuristic(size_t, size_t, bool);
	std::string getMove(size_t, size_t, size_t, size_t);
	bool goal(size_t, size_t);

	struct Node {
		size_t pos;
		size_t parent;
		int g;
		int h;
		bool closed;

		Node(size_t, int = 0, int = 0);
		bool operator<(const Node &) const;
	};
public:
	Game();
	void run();
	int dangerAt(size_t row, size_t col);
	std::string getMoveOfLesserDanger(size_t row, size_t col);
	void discardMoves();
	bool hasMoves();
	bool isThereTheTargetStill();
	void move();
	std::vector<Bomb>& getBombs();
	std::vector<Snippet>& getSnippets();
	Player& getMe();
	Player& getEnemy();
	void findPath(bool = false);
	void setBehaviorTree(BehaviorTree *);
};

#endif