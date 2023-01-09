//
// Created by wojte on 28-Dec-22.
//
#ifndef ROOK_CPP
#define ROOK_CPP

#include "Piece.cpp"
#include "ChessKing.cpp"

class Rook : public Piece {
public:


	Rook(Board* b, Player* loyalty) : Piece(b, loyalty, 'r', "Rook",
		loyalty->lowerBoardSide ? "../Resources/source_1/White/Rook.jpg" : "../Resources/source_1/Black/Rook.jpg") {
		addTag("can castle");
	}

	Rook* clone() const override {
		return new Rook(*this);
	};

	std::vector<BoardMove*> getMoves() {
		std::vector<BoardMove*> out;
		checkPositionAndMove(&out, Coordinates().up());
		checkPositionAndMove(&out, Coordinates().down());
		checkPositionAndMove(&out, Coordinates().right());
		checkPositionAndMove(&out, Coordinates().left());
		checkCastle(out);
		return out;
	}

	void checkCastle(std::vector<BoardMove*>out) {
	}

	void checkPositionAndMove(std::vector<BoardMove*>* out, Coordinates direction) {
		Coordinates checkedLocation = location + direction;
		while (b->containsPiece(checkedLocation) &&
			b->getPiece(checkedLocation)->name == "empty") {
			BoardMove* m = new BoardMove("Move", "Move to " + checkedLocation.toString());
			m->push_back(
				[location = new Coordinates(location), checkedLocation = new Coordinates(checkedLocation)](Board* b) {
					b->getPiece(*location)->removeTag("can castle");
					b->MovePiece(*location, *checkedLocation);
				});
			out->push_back(m);
			checkedLocation += direction;
		}
		if (b->containsPiece(checkedLocation) &&
			b->getPiece(checkedLocation)->name != "empty" &&
			b->getPiece(checkedLocation)->loyalty != this->loyalty) {
			checkChecking(checkedLocation);
			BoardMove* m = new BoardMove("attack", "Attack " + b->getPiece(checkedLocation)->toString());
			m->push_back(
				[location = new Coordinates(location), checkedLocation = new Coordinates(checkedLocation)](Board* b) {
					b->getPiece(*location)->removeTag("can castle");
					b->RemovePiece(*checkedLocation);
					b->MovePiece(*location, *checkedLocation);
					
				});
			out->push_back(m);
		}
		if (b->containsPiece(checkedLocation) &&
			b->getPiece(checkedLocation)->name != "empty" &&
			b->getPiece(checkedLocation)->loyalty == this->loyalty &&
			b->getPiece(checkedLocation)->name == "King" &&
			b->getPiece(checkedLocation)->hasTag("castlable") &&
			hasTag("can castle")) {
			BoardMove* m = new BoardMove("castle", "Castle with " + b->getPiece(checkedLocation)->toString());
			m->push_back([location = new Coordinates(location), checkedLocation = new Coordinates(
				checkedLocation), direction = new Coordinates(direction)](Board* b) {
					b->getPiece(*checkedLocation)->removeTag("castlable");
					b->getPiece(*location)->removeTag("can castle");

					b->MovePiece(*location, *checkedLocation - *direction);
					b->MovePiece(*checkedLocation, *checkedLocation - *direction - *direction);
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