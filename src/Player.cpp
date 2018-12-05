#include "Player.h"

Player::Player(size_t row, size_t col, size_t id, std::string name) : 
	Point::Point(row, col),
	id(id),
	name(name)
{
	snippets = 0u;
	bombs = 0u;
}

size_t Player::getId() {
	return id;
}

void Player::setId(size_t id) {
	this->id = id;
}

void Player::setPosition(size_t row, size_t col) {
	setRow(row);
	setCol(col);
}

void Player::setName(std::string &name) {
	this->name = name;
}

std::string Player::getName() {
	return name;
}

size_t Player::getBombs() {
	return bombs;
}

void Player::setBombs(size_t bombs) {
	this->bombs = bombs;
}

size_t Player::getSnippets() {
	return snippets;
}

void Player::setSnippets(size_t snippets) {
	this->snippets = snippets;
}