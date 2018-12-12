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
		e = -32;
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
					field[count] = saveCellType(temp, count/field_width, count%field_width);
					temp.clear();
				}
				else if(e == ',') {
					field[count] = saveCellType(temp, count/field_width, count%field_width);
					temp.clear();
					count++;
				}
				else
					temp += e;
			}

			if(!temp.empty())
				field[count] = saveCellType(temp, count/field_width, count%field_width);

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
		std::cout << "bixie\n";
	}
	else if(!aux.compare("move")) {
		tree->run();
	}
}

void Game::move() {
	if(!moves.empty()) {
		std::cout << moves.top() << "\n";
		moves.pop();
	}
	else 
		std::cout << "pass\n";
}

void Game::calculateDanger(size_t row, size_t col) {
	danger[row*field_width + col] = 0;
	std::queue<size_t> queue;
	queue.push(row*field_width + col);

	while(!queue.empty()) {
		size_t v = queue.front();
		queue.pop();
		for(auto &w : getAdj(v, false)) {
			if(w != row*field_width+col) {
				if(!danger[w]) {
					danger[w] = danger[v]-1;
					queue.push(w);
				}
				else if(danger[v]-1 >= danger[w]) {
					danger[w] = danger[v]-1;
					queue.push(w);
				}
			}
		}
	}
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

int Game::dangerAt(size_t row, size_t col) {
	return danger[row*field_width+col];
}

std::vector<size_t> Game::getAdj(size_t pos, bool gate = true) {
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

	if(gate) {
		// Move from Left Gate to Right Gate
		if(row == leftGate.getRow() and col == leftGate.getCol())
			adj.push_back(rightGate.getRow()*field_width + rightGate.getCol());

		// Move from Right Gate to Left Gate
		if(row == rightGate.getRow() and col == rightGate.getCol())
			adj.push_back(leftGate.getRow()*field_width + leftGate.getCol());	
	}

	return adj;
}

int Game::heuristic(size_t row, size_t col, bool bomb) {
	int h;
	if(!snippets.empty()) {
		h = (
			row-snippets[0].getRow() < 0 ? 
			-(row-snippets[0].getRow()) :
			row-snippets[0].getRow()
		);

		h += (
			col-snippets[0].getCol() < 0 ? 
			-(col-snippets[0].getCol()) :
			col-snippets[0].getCol()
		);
	}
	else if(bomb and !bombs.empty()) {
		h = (
			row-bombs[0].getRow() < 0 ? 
			-(row-bombs[0].getRow()) :
			row-bombs[0].getRow()
		);

		h += (
			col-bombs[0].getCol() < 0 ? 
			-(col-bombs[0].getCol()) :
			col-bombs[0].getCol()
		);	
	}
	else
		return 0;

	h += danger[row*field_width+col] + 32;

	for(size_t i = 1u; i < snippets.size(); i++) {
		int _h = (
			row-snippets[i].getRow() < 0 ? 
			-(row-snippets[i].getRow()) :
			row-snippets[i].getRow()
		);

		_h += (
			col-snippets[i].getCol() < 0 ? 
			-(col-snippets[i].getCol()) :
			col-snippets[i].getCol()
		);

		_h += danger[row*field_width+col] + 32;

		if(_h < h)
			h = _h;
	}

	if(bomb) {
		for(size_t i = 1u; i < bombs.size(); i++) {
			int _h = (
				row-bombs[i].getRow() < 0 ? 
				-(row-bombs[i].getRow()) :
				row-bombs[i].getRow()
			);

			_h += (
				col-bombs[i].getCol() < 0 ? 
				-(col-bombs[i].getCol()) :
				col-bombs[i].getCol()
			);

			_h += danger[row*field_width+col] + 32;

			if(_h < h)
				h = _h;
		}
	}

	return h;
}

std::string Game::getMove(size_t beginRow, size_t beginCol, size_t endRow, size_t endCol) {
	if(endRow == beginRow-1)
		return "up";
	if(endRow == beginRow+1)
		return "down";
	if(endCol == beginCol-1)
		return "left";
	if(endCol == beginCol+1)
		return "right";
	
	// From left gate to right gate
	if(beginRow == leftGate.getRow() 
		and beginCol == leftGate.getCol() 
		and endRow == rightGate.getRow()
		and endCol == rightGate.getCol())
		return "left";

	// From right gate to left gate
	if(beginRow == rightGate.getRow() 
		and beginCol == rightGate.getCol() 
		and endRow == leftGate.getRow()
		and endCol == leftGate.getCol())
		return "right";
	return "pass";
}

std::string Game::getMoveOfLesserDanger(size_t row, size_t col) {
	
	size_t min = row*field_width + col;

	for(auto &e: getAdj(min))
		if(field[e] and danger[e] < danger[min])
			min = e;

	return getMove(row, col, min/field_width, min%field_width);
}

void Game::discardMoves() {
	while(!moves.empty())
		moves.pop();
}

bool Game::hasMoves() {
	return !moves.empty();
}

bool Game::isThereTheTargetStill() {
	for(auto &e : snippets)
		if(e.getRow() == target.getRow() and e.getCol() == target.getCol())
			return true;
	for(auto &e : bombs)
		if(e.getRow() == target.getRow() and e.getCol() == target.getCol())
			return true;
	return false;
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

Game::Node::Node(size_t pos, int g, int h) : 
	pos(pos),
	g(g),
	h(h) {}

bool Game::Node::operator<(const Node &node) const {
	return g+h < node.g+node.h;
}

bool Game::goal(size_t row, size_t col) {
	for(auto &e: snippets)
		if(e.getRow() == row and e.getCol() == col)
			return true;
	for(auto &e: bombs)
		if(e.getRow() == row and e.getCol() == col)
			return true;
	return false;
}

void Game::findPath(bool bomb) {
	Node start(
		me.getRow()*field_width+me.getCol(),
		0,
		heuristic(me.getRow(), me.getCol(), bomb)
	);

	std::priority_queue<Node> open;
	open.push(start);

	std::map<size_t, size_t> parent;
	parent[me.getRow()*field_width+me.getCol()] = me.getRow()*field_width+me.getCol();

	std::map<size_t, bool> closed;

	while(!open.empty()) {
		Node n = open.top();
		open.pop();


		if(goal(n.pos/field_width, n.pos%field_width)) {
			// return path to n
			size_t pos = n.pos;
			while(pos != parent[pos]) {
				moves.push(
					getMove(
						parent[pos]/field_width, 
						parent[pos]%field_width,
						pos/field_width,
						pos%field_width
					)
				);

				pos = parent[pos];
			}
		}

		closed[n.pos] = true;

		for(size_t adj_pos : getAdj(n.pos)) {
			if(!closed[adj_pos]) {
				Node m(
					adj_pos,
					n.g + danger[adj_pos] + 32,
					heuristic(adj_pos/field_width, adj_pos%field_width, bomb)
				);
				parent[m.pos] = n.pos;
				open.push(m);
			}
		}
	}
}

void Game::setBehaviorTree(BehaviorTree *tree) {
	this->tree = tree;
}

/*
void Game::findPath() {
	// Create open queue
	std::queue<size_t> open;

	// Insert the start
	open.push(me.getRow()*field_width+me.getCol());

	// Create the parent map
	std::map<size_t, size_t> parent;

	// Set start like parent of itself
	parent[me.getRow()*field_width+me.getCol()] = me.getRow()*field_width+me.getCol();

	// While open queue is not empty
	while(!open.empty()) {
		// Get and Pop the front
		size_t v = open.front();
		open.pop();

		// For each adjacent of v
		for(size_t w : getAdj(v)) {

		}
	}


	// Salvar target
}
*/