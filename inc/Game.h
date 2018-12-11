#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include "Point.h"
#include "Snippet.h"
#include "Bug.h"
#include "Spawn.h"
#include "Bomb.h"
#include "Player.h"

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
	std::vector<size_t> getAdj(size_t pos);

	/*void print() {
		for(size_t i = 0; i < field_height; i++) {
			for (size_t j = 0; j < field_width; ++j)
				std::cout << std::right << std::setw(2) << danger[i*field_width + j] << " ";
			std::cout << '\n';
		}

		std::cout << "\nEnemies: " << bugs.size() << "\n";
	}*/
public:
	Game();
	void run();
	size_t dangerAt(size_t row, size_t col);
	size_t getAdjWithLessDanger(size_t row, size_t col);
	void discardMoves();
	bool hasMoves();
	Point getMyTarget();
	void move();
	std::vector<Bomb>& getBombs();
	std::vector<Snippet>& getSnippets();
	Player& getMe();
	Player& getEnemy();
	void AStar();
};

#endif