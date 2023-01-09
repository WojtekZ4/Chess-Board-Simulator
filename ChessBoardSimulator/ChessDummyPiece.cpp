//
// Created by wojte on 28-Dec-22.
//
#ifndef CHESS_DUMMYPIECE_CPP
#define CHESS_DUMMYPIECE_CPP

#include "Piece.cpp"
#include "Game.cpp"

class ChessDummyPiece : public Piece {
public:
	ChessDummyPiece(Board* b, Player* loyalty) : Piece(b, loyalty, '-', "Other Actions", "../Resources/Empty Space.jpg") {}
	ChessDummyPiece* clone() const override {
		return new ChessDummyPiece(*this);
	};

	std::vector<BoardMove*> getMoves() {

		std::vector<BoardMove*> out;
		BoardMove* m = new BoardMove("surrender", "Surrender");
		m->push_back([this](Board* b) {
			auto pp=b->PlayersPieces(this->loyalty);
			for (auto p : pp) {
				if(p->name=="King")
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