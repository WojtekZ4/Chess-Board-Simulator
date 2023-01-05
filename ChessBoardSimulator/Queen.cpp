//
// Created by wojte on 28-Dec-22.
//
#ifndef QUEEN_CPP
#define QUEEN_CPP

#include "BoardMove.cpp"
#include "ChessKing.cpp"

class Queen : public Piece {
public:

    Queen(Game* g, Player* loyalty, Coordinates location) : Piece(g, loyalty, 'q', "Queen",
        location,
        loyalty->lowerBoardSide ? "../Resources/source_1/White/Queen.jpg" : "../Resources/source_1/Black/Queen.jpg") {
    }


    std::set<BoardMove*> getMoves() {
        std::set<BoardMove*> out;
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

    void checkPositionAndBoardMove(std::set<BoardMove*>* out, Coordinates direction) {
        ;
        Coordinates checkedLocation = location + direction;
        while (g->gameboard->containsPiece(checkedLocation) &&
            g->gameboard->bo[checkedLocation.value]->name == "empty") {
            BoardMove* m = new BoardMove("move", "Move to " + checkedLocation.toString());
            m->push_back(
                [this, location = new Coordinates(location), checkedLocation = new Coordinates(checkedLocation)] {
                    g->gameboard->MovePiece(*location, *checkedLocation);
                });
            out->insert(m);
            checkedLocation += direction;
        }
        if (g->gameboard->containsPiece(checkedLocation) &&
            g->gameboard->bo[checkedLocation.value]->loyalty != this->loyalty) {
            BoardMove* m = new BoardMove("attack", "Attack " + g->gameboard->bo[checkedLocation.value]->toString());
            m->push_back(
                [this, location = new Coordinates(location), checkedLocation = new Coordinates(checkedLocation)] {
                    g->gameboard->RemovePiece(*checkedLocation);
            g->gameboard->MovePiece(*location, *checkedLocation);
                });
            out->insert(m);
        }
    }
};

#endif