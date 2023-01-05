//
// Created by wojte on 28-Dec-22.
//
#ifndef CHECKERSDUMMYPIECE_CPP
#define CHECKERSDUMMYPIECE_CPP

#include "Game.cpp"
#include "Piece.cpp"

class CheckersDummyPiece : public Piece {
public:
    CheckersDummyPiece(Game* g, Player* loyalty) : Piece(g, loyalty, '-', "Other Actions", Coordinates(), "../Resources/Empty Space.jpg") {}

    std::set<BoardMove*> getMoves() {
        std::set<BoardMove*> out;
        out.insert(surrenderMove());
        return out;
    }

    BoardMove* surrenderMove() {
        BoardMove* m = new BoardMove("Surrender", "Surrender");
        std::set<Piece*> pp = g->gameboard->PlayersPieces(loyalty);
        for (auto ppp : pp) {
            m->push_back([ObjectPtr = g, ppp] {
                ObjectPtr->gameboard->RemovePiece(ppp->location.value);
                });
        }
        return m;
    }

    std::string toString() {
        return name;
    }
};

#endif