//
// Created by wojte on 28-Dec-22.
//
#ifndef QUEEN_CPP
#define QUEEN_CPP

#include "BoardMove.cpp"
#include "ChessKing.cpp"

class Queen : public Piece {
public:

	Queen(Board* b, Player* loyalty) : Piece(b, loyalty, 'q', "Queen",
		loyalty->lowerBoardSide ? "../Resources/source_1/White/Queen.jpg" : "../Resources/source_1/Black/Queen.jpg") {
	}
	Queen* clone() const override {
		return new Queen(*this);
	};

	std::vector<BoardMove*> getMoves() {
		std::vector<BoardMove*> out;
		checkPositionAndBoardMove(&out, Coordinates().up());
		checkPositionAndBoardMove(&out, Coordinates().down());
		checkPositionAndBoardMove(&out, Coordinates().right());
		checkPositionAndBoardMove(&out, Coordinates().left());
		checkPositionAndBoardMove(&out, Coordinates().up().right());
		checkPositionAndBoardMove(&out, Coordinates().up().left());
		checkPositionAndBoardMove(&out, Coordinates().down().right());
		checkPositionAndBoardMove(&out, Coordinates().down().left());
		return out;
	}

	void checkPositionAndBoardMove(std::vector<BoardMove*>* out, Coordinates direction) {
		;
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
			b->getPiece(checkedLocation)->name == "King") {
			addTag("checking");
		}
	}
};

#endif