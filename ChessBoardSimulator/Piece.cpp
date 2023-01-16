//
// Created by wojte on 24-Dec-22.
//
#ifndef PIECE_CPP
#define PIECE_CPP

#include <map>
#include <string>
#include "Player.cpp"
#include "BoardMove.cpp"
#include <cctype>
#include "Coordinates.cpp"

class Game;

class Player;

class Piece {
public:
	Coordinates location;
	std::string name;
	std::set<std::string> tags;
	Player* loyalty;
	char symbol;
	Board* b;
	std::string icon;

	Piece(Board* b, Player* loyalty, char symbol, std::string name, std::string icon) {
		this->b = b;
		this->loyalty = loyalty;
		this->name = name;
		this->location = Coordinates();
		//this->icon = icon;
		if (loyalty != nullptr && loyalty->lowerBoardSide) {
			this->symbol = (char)toupper(symbol);
			this->icon = this->name + "_White";
		}
		else {
			this->symbol = (char)tolower(symbol);
			this->icon = this->name + "_Black";
		}
	}


	virtual Piece* clone() const = 0;

	void addTag(std::string tag) {
		tags.insert(tag);
	}

	void removeTag(std::string tag) {
		tags.erase(tag);
	}

	bool hasTag(std::string tag) {
		return std::find(tags.begin(), tags.end(), tag) != tags.end();
	}

	virtual std::vector<BoardMove*> getMoves() = 0;

	virtual std::string toString() {
		return "" + name + " at " + location.toString();
	}

};

#endif