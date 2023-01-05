//
// Created by wojte on 28-Dec-22.
//
#ifndef ROOK_CPP
#define ROOK_CPP

#include "Piece.cpp"
#include "ChessKing.cpp"

class Rook : public Piece {
public:


    Rook(Game* g, Player* loyalty, Coordinates location) : Piece(g, loyalty, 'r', "Rook", location,
        loyalty->lowerBoardSide ? "../Resources/source_1/White/Rook.jpg" : "../Resources/source_1/Black/Rook.jpg") {
        addTag("can castle");
    }

    std::set<BoardMove*> getMoves() {
        std::set<BoardMove*> out;
        checkPositionAndMove(&out, Coordinates().up());
        checkPositionAndMove(&out, Coordinates().down());
        checkPositionAndMove(&out, Coordinates().right());
        checkPositionAndMove(&out, Coordinates().left());
        checkCastle(out);
        return out;
    }

    void checkCastle(std::set<BoardMove*> out) {
    }

    void checkPositionAndMove(std::set<BoardMove*>* out, Coordinates direction) {
        Coordinates checkedLocation = location + direction;
        while (g->gameboard->containsPiece(checkedLocation) &&
            g->gameboard->bo[checkedLocation.value]->name == "empty") {
            BoardMove* m = new BoardMove("BoardMove", "BoardMove to " + checkedLocation.toString());
            m->push_back(
                [this, location = new Coordinates(location), checkedLocation = new Coordinates(checkedLocation)] {
                    g->gameboard->MovePiece(*location, *checkedLocation);
            this->removeTag("can castle");
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
            this->removeTag("can castle");
                });
            out->insert(m);
        }
        if (g->gameboard->containsPiece(checkedLocation) &&
            g->gameboard->bo[checkedLocation.value]->loyalty == this->loyalty &&
            g->gameboard->bo[checkedLocation.value]->name == "King" &&
            g->gameboard->bo[checkedLocation.value]->hasTag("castlable") && hasTag("can castle")) {
            BoardMove* m = new BoardMove("castle", "Castle with " + g->gameboard->bo[checkedLocation.value]->toString());
            m->push_back([this, location = new Coordinates(location), checkedLocation = new Coordinates(
                checkedLocation), direction = new Coordinates(direction)] {
                    g->gameboard->bo[checkedLocation->value]->removeTag("castlable");
            removeTag("can castle");

            g->gameboard->MovePiece(*location, *checkedLocation - *direction);
            g->gameboard->MovePiece(*checkedLocation, *checkedLocation - *direction - *direction);
                });
            out->insert(m);
        }
    }
};

#endif