//
// Created by wojte on 28-Dec-22.
//
#ifndef CHESS_DUMMYPIECE_CPP
#define CHESS_DUMMYPIECE_CPP

#include "Piece.cpp"

class ChessDummyPiece : public Piece {
public:
    ChessDummyPiece(Game* g, Player* loyalty) : Piece(g, loyalty, '-', "Other Actions", Coordinates(), "../Resources/Empty Space.jpg") {}

    std::set<BoardMove*> getMoves() {
        std::set<BoardMove*> out;
        BoardMove* m = new BoardMove("Surrender", "Surrender");
        m->push_back([this] {
            addTag("surrender");
            });
        return out;
    }

    std::string toString() {
        return name;
    }
};

#endif