#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Point.h"

class Player : public Point {
private:
	size_t snippets;
	size_t bombs;
	size_t id;
	std::string name;
public:
	Player(size_t = 0u, size_t = 0u, size_t id = 0u, std::string = "");

	// Used
	size_t getId();
	void setId(size_t);
	void setPosition(size_t, size_t);
	void setName(std::string &);
	std::string getName();
	size_t getBombs();
	void setBombs(size_t);
	size_t getSnippets();
	void setSnippets(size_t);
};

#endif