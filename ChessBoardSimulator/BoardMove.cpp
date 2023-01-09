//
// Created by wojte on 28-Dec-22.
//

#ifndef BOARDMOVE_CPP
#define BOARDMOVE_CPP

#include <vector>
#include <functional>
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>

class Board;
class BoardMove {
public:
	//std::vector<std::function<void()>> moves;
	std::vector<std::function<void(Board*)>> moves;
	std::string name;
	std::string description;
	BoardMove(std::string name, std::string description) {
		this->name = name;
		this->description = description;
	}

	BoardMove(BoardMove& other) {
		this->name = other.name;
		this->description = other.description;
		copy(other.moves.begin(), other.moves.end(), std::back_inserter(this->moves));
		/*     this->moves =  other.moves;*/
	}

	void addDescription(std::string moreDescription) {
		description += moreDescription;
	}

	void push_back(std::function<void(Board*)> toInsert) {
		moves.push_back(toInsert);
	}

	//void execute() {
	//    for (auto m : moves) {
	//        m();
	//    }
	//}

	void execute(Board* gameboard) {
		for (auto m : moves) {
			m(gameboard);
		}
	}

	std::string toString() {
		return description;
	}
};

#endif