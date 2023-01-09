//
// Created by wojte on 28-Dec-22.
//
#ifndef CHECKERSDUMMYPIECE_CPP
#define CHECKERSDUMMYPIECE_CPP

#include "Game.cpp"
#include "Piece.cpp"

class CheckersDummyPiece : public Piece {
public:
	CheckersDummyPiece(Board* b, Player* loyalty) : Piece(b, loyalty, '-', "Other Actions", "../Resources/Empty Space.jpg") {}
	CheckersDummyPiece* clone() const override {
		return new CheckersDummyPiece(*this);
	};
	std::vector<BoardMove*> getMoves() {
		std::vector<BoardMove*> out;
		BoardMove* m = new BoardMove("surrender", "Surrender");
		m->push_back([this](Board* b) {
			auto pp = b->PlayersPieces(this->loyalty);
		for (auto p : pp) {
			p->addTag("surrendered");
		}
			});
		out.push_back(m);
		return out;
	}

	std::string toString() {
		return name;
	}
};

#endif