//
// Created by wojte on 28-Dec-22.
//
#ifndef BISHOP_CPP
#define BISHOP_CPP

#include "Piece.cpp"
#include "ChessKing.cpp"

class Bishop : public Piece {
public:


    Bishop(Game* g, Player* loyalty, Coordinates location)
        : Piece(g, loyalty, 'b', "Bishop", location,
            loyalty->lowerBoardSide ? "../Resources/source_1/White/Bishop.jpg" : "../Resources/source_1/Black/Bishop.jpg") {
    }


    std::set<BoardMove*> getMoves() {
        std::set<BoardMove*> out;
        checkPositionAndMove(&out, Coordinates().right().up());
        checkPositionAndMove(&out, Coordinates().left().up());
        checkPositionAndMove(&out, Coordinates().right().down());
        checkPositionAndMove(&out, Coordinates().left().down());
        return out;
    }

    void checkPositionAndMove(std::set<BoardMove*>* out, Coordinates direction) {
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