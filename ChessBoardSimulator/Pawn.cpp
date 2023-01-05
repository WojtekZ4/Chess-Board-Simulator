//
// Created by wojte on 28-Dec-22.
//
#ifndef PAWN_CPP
#define PAWN_CPP

#include <optional>
#include "Piece.cpp"
#include "Game.cpp"
#include "Rook.cpp"
#include "Bishop.cpp"
#include "Knight.cpp"
#include "Queen.cpp"
#include "ChessKing.cpp"

class Pawn : public Piece {
public:
    bool orientatedUp;
    Coordinates forward;

    Pawn(Game* g, Player* loyalty, Coordinates location)
        : Piece(g, loyalty, 'p', "Pawn", location,
            loyalty->lowerBoardSide ? "../Resources/source_1/White/Pawn.jpg" : "../Resources/source_1/Black/Pawn.jpg") {
        this->orientatedUp = loyalty->lowerBoardSide;
        if (orientatedUp)
            forward = Coordinates().up();
        else
            forward = Coordinates().down();
    }

    std::set<BoardMove*> getMoves() {
        std::set<BoardMove*> out;
        checkForMove(&out);
        checkForCapture(&out);
        return out;
    }

    void checkPositionForMove(std::set<BoardMove*>* out, Coordinates checkedLocation) {
        if (g->gameboard->containsPiece(checkedLocation) &&
            g->gameboard->getPiece(checkedLocation)->name == "empty") {
            BoardMove* m = new BoardMove("move", "Move to " + checkedLocation.toString());
            m->push_back(
                [this, location = new Coordinates(location), checkedLocation = new Coordinates(
                    checkedLocation)] {
                        g->gameboard->MovePiece(*location, *checkedLocation);
                });
            checkPositionForDoubleMove(out, m, checkedLocation);
            if (!checkPositionForPromotion(out, m, checkedLocation))
                out->insert(m);
        }
    }

    void checkPositionForDoubleMove(std::set<BoardMove*>* out, BoardMove* oldMove, Coordinates checkedLocation) {
        if ((this->location + forward + forward) == checkedLocation) {
            oldMove->push_back([this] {this->addTag("En Pessant possible"); });
        }
    }

    void checkForMove(std::set<BoardMove*>* out) {
        Coordinates checkedLocation = location;

        checkedLocation += forward;
        checkPositionForMove(out, checkedLocation);

        checkedLocation += forward;
        if ((location.y() == 2 && orientatedUp) || (location.y() == 7 && !orientatedUp))
            checkPositionForMove(out, checkedLocation);
    }

    void checkPositionForEnPessantAttack(std::set<BoardMove*>* out, Coordinates enemyPosition, Coordinates emptyPosition) {
        if (g->gameboard->containsPiece(enemyPosition) &&
            g->gameboard->getPiece(emptyPosition)->name != "empty" &&
            g->gameboard->getPiece(emptyPosition)->loyalty != loyalty &&
            g->gameboard->getPiece(emptyPosition)->hasTag("En Pessant possible") &&
            g->gameboard->containsPiece(emptyPosition) &&
            g->gameboard->getPiece(emptyPosition)->name == "empty"
            ) {
            BoardMove* m = new BoardMove("attack", "Attack " + g->gameboard->getPiece(emptyPosition)->toString());
            m->push_back([this, location = new Coordinates(location), enemyPosition = new Coordinates(
                enemyPosition), emptyPosition = new Coordinates(emptyPosition)] {
                    g->gameboard->RemovePiece(*enemyPosition);
            g->gameboard->MovePiece(*location, *emptyPosition);
                });
            if (!checkPositionForPromotion(out, m, emptyPosition)) {
                out->insert(m);
            }
        }
    }

    bool checkPositionForPromotion(std::set<BoardMove*>* out, BoardMove* oldMove, Coordinates checkedLocation) {
        if ((location.y() == 8 && orientatedUp) || (location.y() == 1 && !orientatedUp)) {
            BoardMove* m;

            m = new BoardMove(*oldMove);
            m->addDescription(" and promote to Queen");
            m->push_back([this, location = new Coordinates(location), checkedLocation = new Coordinates(
                checkedLocation)] {
                    g->gameboard->RemovePiece(*checkedLocation);
            g->gameboard->PlacePiece(*checkedLocation, new Queen(g, loyalty, *checkedLocation));
                });
            out->insert(m);

            m = new BoardMove(*oldMove);
            m->addDescription(" and promote to Rook");
            m->push_back([this, location = new Coordinates(location), checkedLocation = new Coordinates(
                checkedLocation)] {
                    g->gameboard->RemovePiece(*checkedLocation);
            g->gameboard->PlacePiece(*checkedLocation, new Rook(g, loyalty, *location));
                });
            out->insert(m);

            m = new BoardMove(*oldMove);
            m->addDescription(" and promote to Bishop");
            m->push_back([this, location = new Coordinates(location), checkedLocation = new Coordinates(
                checkedLocation)] {
                    g->gameboard->RemovePiece(*checkedLocation);
            g->gameboard->PlacePiece(*checkedLocation, new Bishop(g, loyalty, *checkedLocation));
                });
            out->insert(m);

            m = new BoardMove(*oldMove);
            m->addDescription(" and promote to Knight");
            m->push_back([this, location = new Coordinates(location), checkedLocation = new Coordinates(
                checkedLocation)] {
                    g->gameboard->RemovePiece(*checkedLocation);
            g->gameboard->PlacePiece(*checkedLocation, new Knight(g, loyalty, *checkedLocation));
                });
            out->insert(m);
            return true;
        }
        else {
            return false;
        }
    }

    void checkPositionForCapture(std::set<BoardMove*>* out, Coordinates checkedLocation) {
        if (g->gameboard->containsPiece(checkedLocation) &&
            g->gameboard->getPiece(checkedLocation)->name != "empty" &&
            g->gameboard->getPiece(checkedLocation)->loyalty != loyalty) {
            BoardMove* m = new BoardMove("attack", "Attack " + g->gameboard->getPiece(checkedLocation)->toString());
            m->push_back(
                [this, location = new Coordinates(location), checkedLocation = new Coordinates(checkedLocation)] {
                    g->gameboard->RemovePiece(*checkedLocation);
            g->gameboard->MovePiece(*location, *checkedLocation);
                });
            if (!checkPositionForPromotion(out, m, checkedLocation))
                out->insert(m);
        }
    }

    void checkForCapture(std::set<BoardMove*>* out) {
        Coordinates checkedLocation = location;

        checkPositionForEnPessantAttack(out, checkedLocation.right(), checkedLocation.right() + forward);
        checkPositionForEnPessantAttack(out, checkedLocation.left(), checkedLocation.left() + forward);

        checkedLocation += forward;
        checkPositionForCapture(out, checkedLocation.right());
        checkPositionForCapture(out, checkedLocation.left());

    }
};

#endif