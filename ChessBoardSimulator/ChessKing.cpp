//
// Created by wojte on 30-Dec-22.
//

#ifndef CHESSKING2_CPP
#define CHESSKING2_CPP

#include "Piece.cpp"
#include "Game.cpp"

class ChessKing : public Piece {
public:
    ChessKing(Game* g, Player* loyalty, Coordinates location) : Piece(g, loyalty, 'x', "King", location,
        loyalty->lowerBoardSide ? "../Resources/source_1/White/King.jpg" : "../Resources/source_1/Black/King.jpg") {
        addTag("castlable");
    }

    std::set<BoardMove*> getMoves() {
        std::set<BoardMove*> out;
        checkPositionAndMove(&out, location.up());
        checkPositionAndMove(&out, location.down());
        checkPositionAndMove(&out, location.right());
        checkPositionAndMove(&out, location.left());
        checkPositionAndMove(&out, location.up().right());
        checkPositionAndMove(&out, location.up().left());
        checkPositionAndMove(&out, location.down().right());
        checkPositionAndMove(&out, location.down().left());
        std::set<BoardMove*> out2;
        checkPositionAndMove(&out2, location);
        return out;
    }

    void checkPositionAndMove(std::set<BoardMove*>* out, Coordinates checkedLocation) {
        if (g->gameboard->containsPiece(checkedLocation)) {
            if (g->gameboard->bo[checkedLocation.value]->name == "empty") {
                BoardMove* m = new BoardMove("move", "Move to " + checkedLocation.toString());
                m->push_back([this, location = new Coordinates(location), checkedLocation = new Coordinates(
                    checkedLocation)] {
                        g->gameboard->MovePiece(*location, *checkedLocation);
                removeTag("castlable");
                    });
                out->insert(m);
            }
            else if (g->gameboard->bo[checkedLocation.value]->loyalty != this->loyalty) {
                BoardMove* m = new BoardMove("attack", "Attack " + g->gameboard->bo[checkedLocation.value]->toString());
                m->push_back([this, location = new Coordinates(location), checkedLocation = new Coordinates(
                    checkedLocation)] {
                        g->gameboard->RemovePiece(*checkedLocation);
                g->gameboard->MovePiece(*location, *checkedLocation);
                removeTag("castlable");
                    });
                out->insert(m);
            }
        }
    }
};

#endif