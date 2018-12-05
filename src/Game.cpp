#include "Game.h"

void Game::settings() {
	std::string aux;
	std::cin >> aux;

	if(!aux.compare("timebank"))
		std::cin >> timebank;
	else if(!aux.compare("time_per_move"))
		std::cin >> time_per_move;
	else if(!aux.compare("player_names"))
		/* Ignore player names */;
	else if(!aux.compare("your_bot")) {
		std::cin >> aux;
		me.setName(aux);
	}
	else if(!aux.compare("your_botid")) {
		size_t id;
		std::cin >> id;
		me.setId(id);
	}
	else if(!aux.compare("field_width")) {
		std::cin >> field_width;

		if(field_height != 0u)
			field.resize(field_height*field_width);
	}
	else if(!aux.compare("field_height")) {
		std::cin >> field_height;

		if(field_width != 0u)
			field.resize(field_height*field_width);
	}
	else if(!aux.compare("max_rounds"))
		std::cin >> max_rounds;
}

bool Game::saveCellType(std::string &cell, size_t row, size_t col) {
	if(cell[0] == 'P' and cell.size() == 2) {
		size_t id = cell[1] - '0';
		if(me.getId() == id)
			me.setPosition(row, col);
		else
			enemy.setPosition(row, col);
	}
	else if(cell[0] == 'S') {
		if(cell.size() == 1)
			spawns.emplace_back(row, col);
		else {
			int timeToSpawn = cell[1] - '0';
			spawns.emplace_back(row, col, timeToSpawn);
		}
	}
	else if(cell[0] == 'G' and cell.size() == 2)
		gates.emplace_back(row, col, cell[1]);
	else if(cell[0] == 'E' and cell.size() == 2) {
		int type = cell[1] - '0';
		bugs.emplace_back(row, col, type);
	}
	else if(cell[0] == 'B') {
		if(cell.size() == 1) {
			bombs.emplace_back(row, col);
		}
		else {
			int timeToExplode = cell[1] - '0';
			bombs.emplace_back(row, col, timeToExplode);
		}
	}
	else if(!cell.compare("C"))
		snippets.emplace_back(row, col);
	else if(cell[0] == '.')
		/* Nothing */;
	else /* 'x' or Invalid field value */
		return false;

	return true;
}

void Game::update() {
	std::string aux;
	std::cin >> aux;
	if(!aux.compare("game")) {
		std::cin >> aux;

		if(!aux.compare("field")) {
			/* Read the field */
			std::cin >> aux;

			resetField();

			size_t count = 0u;
			std::string temp = "";
			for(auto &e : aux) {
				if(e == ';') {
					field[count] = saveCellType(temp, count/field_width, count%field_height);
					temp.clear();
				}
				else if(e == ',') {
					field[count] = saveCellType(temp, count/field_width, count%field_height);
					temp.clear();
					count++;
				}
				else
					temp += e;
			}

			if(!temp.empty())
				field[count] = saveCellType(temp, count/field_width, count%field_height);
		}
		else if(!aux.compare("round"))
			std::cin >> round;
	}
	else if(!aux.compare(me.getName())) {
		std::cin >> aux;
		if(!aux.compare("bombs")) {
			size_t bombs;
			std::cin >> bombs;
			me.setBombs(bombs);
		}
		else if(!aux.compare("snippets")) {
			size_t snippets;
			std::cin >> snippets;
			me.setSnippets(snippets);
		}
	}
	else {
		std::cin >> aux;
		if(!aux.compare("bombs")) {
			size_t bombs;
			std::cin >> bombs;
			enemy.setBombs(bombs);
		}
		else if(!aux.compare("snippets")) {
			size_t snippets;
			std::cin >> snippets;
			enemy.setSnippets(snippets);
		}
	}
}

void Game::action() {
	std::string aux;
	std::cin >> aux;

	if(!aux.compare("character")) {
		std::cout << "bixie";
	}
	else if(!aux.compare("move")) {
		move();
	}
}

void Game::move() {
	// Finish it!
}

Game::Game() : 
	timebank(0),
	time_per_move(0),
	max_rounds(0),
	field_width(0),
	field_height(0),
	round(0),
	field(std::vector<bool>()),
	me(Player()),
	enemy(Player()) {}

void Game::run() {
	std::string command;
	while(std::cin >> command) {
		if(!command.compare("settings"))
			settings();
		else if(!command.compare("update"))
			update();
		else if(!command.compare("action"))
			action();

		// Ignores the line remainder
		std::getline(std::cin, command);
	}
}