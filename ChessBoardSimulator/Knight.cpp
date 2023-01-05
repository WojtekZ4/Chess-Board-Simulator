//
// Created by wojte on 28-Dec-22.
//
#ifndef KNIGHT_CPP
#define KNIGHT_CPP

#include "Piece.cpp"
#include "ChessKing.cpp"

class Knight : public Piece {
public:

    Knight(Game* g, Player* loyalty, Coordinates location) : Piece(g, loyalty, 'k', "Knight", location,
        loyalty->lowerBoardSide ? "../Resources/source_1/White/Knight.jpg" : "../Resources/source_1/Black/Knight.jpg") {
    }


    std::set<BoardMove*> getMoves() {
        std::set<BoardMove*> out;

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

    void checkPositionAndMove(std::set<BoardMove*>* out, Coordinates checkedLocation) {
        if (g->gameboard->containsPiece(checkedLocation)) {
            if (g->gameboard->bo[checkedLocation.value]->name == "empty") {
                BoardMove* m = new BoardMove("move", "Move to " + checkedLocation.toString());
                m->push_back([this, location = new Coordinates(location), checkedLocation = new Coordinates(
                    checkedLocation)] {
                        g->gameboard->MovePiece(*location, *checkedLocation);
                    });
                out->insert(m);
            }
            else if (g->gameboard->bo[checkedLocation.value]->loyalty != this->loyalty) {
                BoardMove* m = new BoardMove("attack", "Attack " + g->gameboard->bo[checkedLocation.value]->toString());
                m->push_back([this, location = new Coordinates(location), checkedLocation = new Coordinates(
                    checkedLocation)] {
                        g->gameboard->RemovePiece(*checkedLocation);
                g->gameboard->MovePiece(*location, *checkedLocation);
                    });
                out->insert(m);
            }
        }
    }
};

#endif