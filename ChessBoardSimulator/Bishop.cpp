//
// Created by wojte on 28-Dec-22.
//
#ifndef BISHOP_CPP
#define BISHOP_CPP

#include "Piece.cpp"
#include "ChessKing.cpp"

class Bishop : public Piece {
public:


	Bishop(Board* b, Player* loyalty)
		: Piece(b, loyalty, 'b', "Bishop",
			loyalty->lowerBoardSide ? "../Resources/source_1/White/Bishop.jpg" : "../Resources/source_1/Black/Bishop.jpg") {
	}
	Bishop* clone() const override {
		return new Bishop(*this);
	};

	std::vector<BoardMove*> getMoves() {
		std::vector<BoardMove*> out;
		checkPositionAndMove(&out, Coordinates().right().up());
		checkPositionAndMove(&out, Coordinates().left().up());
		checkPositionAndMove(&out, Coordinates().right().down());
		checkPositionAndMove(&out, Coordinates().left().down());
		return out;
	}

	void checkPositionAndMove(std::vector<BoardMove*>* out, Coordinates direction) {
		Coordinates checkedLocation = location + direction;
		while (b->containsPiece(checkedLocation) &&
			b->getPiece(checkedLocation)->name == "empty") {
			BoardMove* m = new BoardMove("move", "Move to " + checkedLocation.toString());
			m->push_back(
				[location = new Coordinates(location), checkedLocation = new Coordinates(checkedLocation)](Board* b) {
					b->MovePiece(*location, *checkedLocation);
				});
			out->push_back(m);
			checkedLocation += direction;
		}
		if (b->containsPiece(checkedLocation) &&
			b->getPiece(checkedLocation)->loyalty != this->loyalty) {
			checkChecking(checkedLocation);
			BoardMove* m = new BoardMove("attack", "Attack " + b->getPiece(checkedLocation)->toString());
			m->push_back(
				[location = new Coordinates(location), checkedLocation = new Coordinates(checkedLocation)](Board* b) {
					b->RemovePiece(*checkedLocation);
					b->MovePiece(*location, *checkedLocation);
				});
			out->push_back(m);
		}
	}
	void checkChecking(Coordinates checkedLocation) {
		if (b->containsPiece(checkedLocation) &&
			b->getPiece(checkedLocation)->loyalty != this->loyalty &&
			b->getPiece(checkedLocation)->name =="King") {
			addTag("checking");
		}
	}
};

#endif