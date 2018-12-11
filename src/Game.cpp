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

		if(field_height != 0u) {
			field.resize(field_height*field_width);
			danger.resize(field_height*field_width);
		}
	}
	else if(!aux.compare("field_height")) {
		std::cin >> field_height;

		if(field_width != 0u) {
			field.resize(field_height*field_width);
			danger.resize(field_height*field_width);
		}
	}
	else if(!aux.compare("max_rounds"))
		std::cin >> max_rounds;
}

void Game::resetField() {
	snippets.clear();
	bugs.clear();
	spawns.clear();
	bombs.clear();
	for(auto &e: danger)
		e = 0;
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
	else if(cell[0] == 'G' and cell.size() == 2){
		if(cell[1] == 'l') {
			leftGate.setRow(row);
			leftGate.setCol(col);
		}
		else {
			rightGate.setRow(row);
			rightGate.setCol(col);
		}
	}
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

			for(auto &bug: bugs)
				calculateDanger(bug.getRow(), bug.getCol());
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
	/* Executar a árvore aqui */
}

void Game::calculateDanger(size_t row, size_t col) {
	/*danger[row*field_width + col] = 0;
	std::queue<size_t> queue;
	queue.push(row*field_width + col);
	while(!queue.empty()) {
		size_t v = queue.front();
		queue.pop();
		for(auto &w : getAdj(v)) {
			if(w != row*field_width+col) {
				if(!danger[w]) {
					danger[w] = danger[v]+1;
					queue.push(w);
				}
				else if(danger[v]+1 < danger[w]) {
					danger[w] = danger[v]+1;
					queue.push(w);
				}
			}
		}
	}*/
}

Game::Game() : 
	timebank(0),
	time_per_move(0),
	max_rounds(0),
	field_width(0),
	field_height(0),
	round(0) {}

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

size_t Game::dangerAt(size_t row, size_t col) {
	return danger[row*field_width+col];
}

std::vector<size_t> Game::getAdj(size_t pos) {
	size_t row = pos/field_width;
	size_t col = pos%field_width;

	std::vector<size_t> adj;

	// Move up
	if(row > 0 and field[(row-1)*field_width + col])
		adj.push_back((row-1)*field_width + col);
	
	// Move down
	if(row < field_height-1 and field[(row+1)*field_width + col])
		adj.push_back((row+1)*field_width + col);
	
	// Move left
	if(col > 0 and field[row*field_width + col-1])
		adj.push_back(row*field_width + col-1);

	// Move right
	if(col < field_width-1 and field[row*field_width + col+1])
		adj.push_back(row*field_width + col+1);

	// Move from Left Gate to Right Gate
	if(row == leftGate.getRow() and col == leftGate.getCol())
		adj.push_back(rightGate.getRow()*field_width + rightGate.getCol());

	// Move from Right Gate to Left Gate
	if(row == rightGate.getRow() and col == rightGate.getCol())
		adj.push_back(leftGate.getRow()*field_width + leftGate.getCol());

	return adj;
}

size_t Game::getAdjWithLessDanger(size_t row, size_t col) {
	size_t min = row*field_width + col;

	for(auto &e: getAdj(min))
		if(danger[e] < danger[min])
			min = e;
	return min;
}

void Game::discardMoves() {
	while(!moves.empty())
		moves.pop();
}

bool Game::hasMoves() {
	return !moves.empty();
}

Point Game::getMyTarget() {
	return target;
}

std::vector<Bomb>& Game::getBombs() {
	return bombs;
}

std::vector<Snippet>& Game::getSnippets() {
	return snippets;
}

Player& Game::getMe() {
	return me;
}

Player& Game::getEnemy() {
	return enemy;
}

void Game::AStar() {
	/* Nothing yet */
}