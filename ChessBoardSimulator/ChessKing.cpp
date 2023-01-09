//
// Created by wojte on 30-Dec-22.
//

#ifndef CHESSKING2_CPP
#define CHESSKING2_CPP

#include "Piece.cpp"
#include "Game.cpp"

class ChessKing : public Piece {
public:
	ChessKing(Board* b, Player* loyalty) : Piece(b, loyalty, 'x', "King",
		loyalty->lowerBoardSide ? "../Resources/source_1/White/King.jpg" : "../Resources/source_1/Black/King.jpg") {
		addTag("castlable");
	}
	ChessKing* clone() const override {
		return new ChessKing(*this);
	};
	std::vector<BoardMove*> getMoves() {
		std::vector<BoardMove*> out;
		checkPositionAndMove(&out, location.up());
		checkPositionAndMove(&out, location.down());
		checkPositionAndMove(&out, location.right());
		checkPositionAndMove(&out, location.left());
		checkPositionAndMove(&out, location.up().right());
		checkPositionAndMove(&out, location.up().left());
		checkPositionAndMove(&out, location.down().right());
		checkPositionAndMove(&out, location.down().left());
		std::vector<BoardMove*> out2;
		checkPositionAndMove(&out2, location);
		return out;
	}

	void checkPositionAndMove(std::vector<BoardMove*>* out, Coordinates checkedLocation) {
		if (b->containsPiece(checkedLocation)) {
			if (b->getPiece(checkedLocation)->name == "empty") {
				BoardMove* m = new BoardMove("move", "Move to " + checkedLocation.toString());
				m->push_back([location = new Coordinates(location), checkedLocation = new Coordinates(
					checkedLocation)](Board* b) {
						b->getPiece(*location)->removeTag("castlable");
						b->MovePiece(*location, *checkedLocation);
					});
				out->push_back(m);
			}
			else if (b->getPiece(checkedLocation)->loyalty != this->loyalty) {
				checkChecking(checkedLocation);
				BoardMove* m = new BoardMove("attack", "Attack " + b->getPiece(checkedLocation)->toString());
				m->push_back([location = new Coordinates(location), checkedLocation = new Coordinates(
					checkedLocation)](Board* b) {
						b->getPiece(*location)->removeTag("castlable");
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