//
// Created by wojte on 28-Dec-22.
//
#ifndef KNIGHT_CPP
#define KNIGHT_CPP

#include "Piece.cpp"
#include "ChessKing.cpp"

class Knight : public Piece {
public:

	Knight(Board* b, Player* loyalty) : Piece(b, loyalty, 'k', "Knight",
		loyalty->lowerBoardSide ? "../Resources/source_1/White/Knight.jpg" : "../Resources/source_1/Black/Knight.jpg") {
	}
	Knight* clone() const override {
		return new Knight(*this);
	};

	std::vector<BoardMove*> getMoves() {
		std::vector<BoardMove*> out;

		checkPositionAndMove(&out, location.up().up().right());
		checkPositionAndMove(&out, location.up().up().left());

		checkPositionAndMove(&out, location.right().right().up());
		checkPositionAndMove(&out, location.right().right().down());

		checkPositionAndMove(&out, location.down().down().right());
		checkPositionAndMove(&out, location.down().down().left());

		checkPositionAndMove(&out, location.left().left().up());
		checkPositionAndMove(&out, location.left().left().down());

		return out;
	}

	void checkPositionAndMove(std::vector<BoardMove*>* out, Coordinates checkedLocation) {
		if (b->containsPiece(checkedLocation)) {
			if (b->getPiece(checkedLocation)->name == "empty") {
				BoardMove* m = new BoardMove("move", "Move to " + checkedLocation.toString());
				m->push_back([location = new Coordinates(location), checkedLocation = new Coordinates(
					checkedLocation)](Board* b) {
						b->MovePiece(*location, *checkedLocation);
					});
				out->push_back(m);
			}
			else if (b->getPiece(checkedLocation)->loyalty != this->loyalty) {
				checkChecking(checkedLocation);
				BoardMove* m = new BoardMove("attack", "Attack " + b->getPiece(checkedLocation)->toString());
				m->push_back([location = new Coordinates(location), checkedLocation = new Coordinates(
					checkedLocation)](Board* b) {
						b->RemovePiece(*checkedLocation);
						b->MovePiece(*location, *checkedLocation);
					});
				out->push_back(m);
			}
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