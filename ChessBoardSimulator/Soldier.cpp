//
// Created by wojte on 28-Dec-22.
//
#ifndef SOLDIER_CPP
#define SOLDIER_CPP

#include <optional>
#include "Game.cpp"
#include "Piece.cpp"
#include "CheckersKing.cpp"

class Soldier : public Piece {
public:
    bool orientatedUp;
    Coordinates forward;
    Soldier(Game* g, Player* loyalty, Coordinates location) : Piece(g, loyalty, 'o', "soldier",
        location,
        loyalty->lowerBoardSide ? "../Resources/source_1/White/Pawn.jpg" : "../Resources/source_1/Black/Pawn.jpg") {
        this->orientatedUp = loyalty->lowerBoardSide;
        if (orientatedUp)
            forward = Coordinates().up();
        else
            forward = Coordinates().down();
    }


    std::set<BoardMove*> getMoves() {
        std::set<BoardMove*> out;

        if (orientatedUp) {
            checkPositionAndMove(&out, location.up().right());
            checkPositionAndMove(&out, location.up().left());
        }
        else {
            checkPositionAndMove(&out, location.down().right());
            checkPositionAndMove(&out, location.down().left());
        }

        if (orientatedUp) {
            checkPositionAndJump(new BoardMove("jump", "jump to " + location.up().right().up().right().toString()), &out,
                location,
                location.up().right(), location.up().right().up().right());
            checkPositionAndJump(new BoardMove("jump", "jump to " + location.up().left().up().left().toString()), &out,
                location,
                location.up().left(), location.up().left().up().left());
        }
        else {
            checkPositionAndJump(new BoardMove("jump", "jump to " + location.down().right().down().right().toString()), &out,
                location,
                location.down().right(), location.down().right().down().right());
            checkPositionAndJump(new BoardMove("jump", "jump to " + location.down().right().down().right().toString()), &out,
                location,
                location.down().right(), location.down().right().down().right());
        }
        return out;
    }

    void checkPositionAndMove(std::set<BoardMove*>* out, Coordinates position) {
        if (g->gameboard->containsPiece(position) && g->gameboard->bo[position.value]->name == "empty") {
            BoardMove* m = new BoardMove("jump", "Jump to " + position.toString());

            m->push_back([this, location = new Coordinates(location), position = new Coordinates(position)] {
                g->gameboard->MovePiece(*location, *position);
                });


            if (position.y() == 1 || position.y() == 8) {
                m->description = m->description + " and promote to King";
                m->push_back([this, position = new Coordinates(position)] {
                    g->gameboard->RemovePiece(*position);
                g->gameboard->PlacePiece(*position, new CheckersKing(g, loyalty, *position));
                    });
            }
            out->insert(m);
        }

    }

    void
        checkPositionAndJump(BoardMove* oldMove, std::set<BoardMove*>* out, Coordinates currentPosition, Coordinates enemyPosition,
            Coordinates emptyPosition) {
        if (g->gameboard->containsPiece(enemyPosition) &&
            g->gameboard->bo[enemyPosition.value]->loyalty != this->loyalty &&
            g->gameboard->containsPiece(emptyPosition) && g->gameboard->bo[emptyPosition.value]->name == "empty") {
            BoardMove* m = new BoardMove(*oldMove);

            m->push_back([this, enemyPosition = new Coordinates(enemyPosition), currentPosition = new Coordinates(
                currentPosition), emptyPosition = new Coordinates(emptyPosition)] {
                    g->gameboard->RemovePiece(*enemyPosition);
            g->gameboard->MovePiece(*currentPosition, *emptyPosition);
                });
            out->insert(m);
            if (orientatedUp) {
                m->description = m->description + "then jump to " + emptyPosition.up().right().up().right().toString();
                checkPositionAndJump(m, out, emptyPosition, emptyPosition.up().right(),
                    emptyPosition.up().right().up().right());
                m->description = m->description + "then jump to " + emptyPosition.up().left().up().left().toString();
                checkPositionAndJump(m, out, emptyPosition, emptyPosition.up().left(),
                    emptyPosition.up().left().up().left());
            }
            else {
                m->description =
                    m->description + "then jump to " + emptyPosition.down().right().down().right().toString();
                checkPositionAndJump(m, out, emptyPosition, emptyPosition.down().right(),
                    emptyPosition.down().right().down().right());
                m->description =
                    m->description + "then jump to " + emptyPosition.down().left().down().left().toString();
                checkPositionAndJump(m, out, emptyPosition, emptyPosition.down().left(),
                    emptyPosition.down().left().down().left());
            }

        }
    }
};

#endif