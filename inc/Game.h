#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include "Snippet.h"
#include "Bug.h"
#include "Spawn.h"
#include "Gate.h"
#include "Bomb.h"
#include "Player.h"

class Game {
private:
	int timebank;
	int time_per_move;
	int max_rounds;
	int field_width;
	int field_height;
	int round;
	std::vector<bool> field;

	std::vector<Snippet> snippets;
	std::vector<Bug> bugs;
	std::vector<Spawn> spawns;
	std::vector<Gate> gates;
	std::vector<Bomb> bombs;

	Player me;
	Player enemy;

	void settings();
	void resetField();
	bool saveCellType(std::string &, size_t, size_t);
	void update();
	void action();
	void move();
public:
	Game();
	void run();
};

#endif