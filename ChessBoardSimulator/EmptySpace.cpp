//
// Created by wojte on 28-Dec-22.
//
#ifndef EMPTYSPACE_CPP
#define EMPTYSPACE_CPP

#include "Piece.cpp"

class EmptySpace : public Piece {
public:
	EmptySpace(Board* b) : Piece(b, nullptr, '.', "empty", "../Resources/Empty Space.jpg") {}
	EmptySpace* clone() const override {
		return new EmptySpace(*this);
	};
	std::vector<BoardMove*> getMoves() {
		std::vector<BoardMove*> out;
		return out;
	}
};

#endif