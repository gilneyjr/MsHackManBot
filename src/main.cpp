#include <iostream>
#include <algorithm>

using namespace std;

class Cell {
private:
	std::vector<std::string> types;

public:
	Cell(std::vector<std::string> &types) : types(types) {}

	Cell() {}

	bool contains(std::string &str) {
		for(auto &e: types)
			if(!e.compare(str))
				return true;
		return false;
	}

	void print() {
		for(size_t i = 0; i < types.size(); i++) {
			std::cout << types[i];
			if(i+1 < types.size())
				std::cout << ";";
		}
	}


	void clear() {
		types.clear();
	}

	void addType(std::string &type) {
		types.push_back(type);
	}
};

class Point
{
private:
	size_t row;
	size_t col;

public:
	Point(size_t row = 0u, size_t col = 0u) : row(row), col(col) {}

	size_t getRow() {
		return row;
	}
	void setRow(size_t row) {
		this->row = row;
	}
	size_t getCol() {
		return col;
	}
	void setCol(size_t col) {
		this->col = col;
	}
};

class Snippet : public Point {
public:
	Snippet(size_t row = 0u, size_t col = 0u) : Point::Point(row,col) {}
};

class Bomb : public Point {
private:
	int timeToExplode;
public:
	Bomb(size_t row = 0u, size_t col  0u, int timeToExplode = -1) :
			timeToExplode(timeToExplode),
			Point::Point(row, col) {}

	int getTimeToExplode() {
		return timeToExplode;
	}
};

class Spawn : public Point {
private:
	int timeToSpawn;
public:
	Bomb(size_t row = 0u, size_t col  0u, int timeToSpawn = -1) :
			timeToSpawn(timeToSpawn),
			Point::Point(row, col) {}

	int getTimeToSpawn() {
		return timeToSpawn;
	}
};

class Gate : public Point
{
private:
	char size;
public:
	Gate(size_t row = 0u, size_t col = 0u, char side = '\0') : 
			Point::Point(row, col)
			side(side) {}
};

class Bug : public Point
{
private:
	int type;
public:
	Bug(size_t row = 0u, size_t col  0u, int type = -1) :
			Point::Point(row, col)
			type(type) {}
};

class Player : public Point {
private:
	size_t snippets;
	size_t bombs;
	std::string name;
	size_t id;
public:
	Player(size_t id = 0u, std::string name = "", size_t row = 0u, size_t col = 0u) : 
			id(id),
			name(name),
			Point::Point(row, col)
	{
		snippets = 0u;
		bombs = 0u;
	}

	// Used
	int getId() {
		return id;
	}

	void setPosition(size_t row, size_t col) {
		this->row = row;
		this->col = col;
	}

	// Unused
	size_t getSnippets() {
		return snippets;
	}
	void setSnippets(size_t snippets) {
		this->snippets = snippets;
	}
	size_t getBombs() {
		return bombs;
	}
	void setBombs(size_t bombs) {
		this->bombs = bombs;
	}
};

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

	void settings() {
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
			std::cin >> aux;
			me.setId(aux);
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

	// REMOVE IT AFTER
	void print() {
		std::cout << "\n";
		for(auto &e: field) {
			e.print();
			std::cout << ",\n";
		}
	}

	void resetField() {
		
	}

	bool saveCellType(std::string &cell, size_t row, size_t col) {
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
			codes.emplace_back(row, col);
		else if(cell[0] == '.')
			/* Nothing */;
		else /* 'x' or Invalid field value */
			return false;

		return true;
	}

	void update() {
		std::string aux;
		std::cin >> aux;
		if(!aux.compare("game")) {
			std::cin >> aux;

			if(!aux.compare("field")) {
				/* Read the field */
				std::cin >> aux;

				resetField();

				size_t count = 0u;
				field[0].clear();
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

	void action() {
		std::string aux;
		std::cin >> aux;

		if(!aux.compare("character")) {
			std::cout << "bixie";
		}
		else if(!aux.compare("move")) {
			move();
		}
	}

	void move() {

	}

public:
	Game() : 
		timebank(0),
		time_per_move(0),
		your_botid(0),
		max_rounds(0),
		field_width(0),
		field_height(0),
		round(0),
		field(std::vector<Cell>()) {}

	void run() {
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
};


int main(int argc, char const *argv[]) {
	Game().run();
	return 0;
}