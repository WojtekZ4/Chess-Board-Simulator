//
// Created by wojte on 28-Dec-22.
//
#ifndef CHESSKING_CPP
#define CHESSKING_CPP

#include "Piece.cpp"
#include "Coordinates.cpp"
#include "Game.cpp"

class CheckersKing : public Piece {
public:
    CheckersKing(Game* g, Player* loyalty, Coordinates location) : Piece(g, loyalty, 'k', "king", location,
        loyalty->lowerBoardSide ? "../Resources/source_1/White/Queen.jpg" : "../Resources/source_1/Black/Queen.jpg") {}

    std::set<BoardMove*> getMoves() {
        std::set<BoardMove*> out;

        checkMoves(&out, Coordinates().up().right(), location);
        checkMoves(&out, Coordinates().up().left(), location);
        checkMoves(&out, Coordinates().down().right(), location);
        checkMoves(&out, Coordinates().down().left(), location);

        checkPositionAndJump(&out, new BoardMove("jump", "jump to " + location.down().down().left().left().toString()),
            location,
            location.down().left(), location.down().down().left().left());
        checkPositionAndJump(&out, new BoardMove("jump", "jump to " + location.up().up().left().left().toString()), location,
            location.up().left(), location.up().up().left().left());
        checkPositionAndJump(&out, new BoardMove("jump", "jump to " + location.down().down().right().right().toString()),
            location,
            location.down().right(), location.down().down().right().right());
        checkPositionAndJump(&out, new BoardMove("jump", "jump to " + location.up().up().right().right().toString()),
            location,
            location.up().right(), location.up().up().right().right());
        return out;
    }

    //    void checkPositionAndMove(std::set<Move *> out, int position, std::string moveName, std::string moveDescription) {
    //        if (g->gameboard->bo.contains(position) && g->gameboard->bo[position]->name == "empty") {
    //            Move *m = new Move(moveName, moveDescription);
    //
    //            m->push_back([this, position] {
    //                g->gameboard->MovePiece(location, position);
    //            });
    //            out.insert(m);
    //        }
    //    }

    void
        checkMoves(std::set<BoardMove*>* out, Coordinates difrence, Coordinates currentPosition) {
        Coordinates checking_position = location + difrence;
        while (g->gameboard->containsPiece(checking_position) &&
            g->gameboard->bo[checking_position.value]->name == "empty") {
            BoardMove* m = new BoardMove("move", "Move to" + checking_position.toString());

            m->push_back([this, &currentPosition, &checking_position] {
                g->gameboard->MovePiece(currentPosition.value, checking_position.value);
                });
            out->insert(m);

            checking_position += location + difrence;
        }

        //        if (g->gameboard->bo.contains(checking_position) && g->gameboard->bo[checking_position]->loyalty != this->loyalty) {
        //            checkPositionAndJump2(new Move("skok", "skok do" + std::to_string(
        //                    checking_position + difrence)), , location, out, checking_position, checking_position + difrence);
        //        }
        //        if (g->gameboard->bo.contains(emptyPosition) && g->gameboard->bo[emptyPosition]->name == "empty") {
        //            Move *m = new Move("move","move do"+ std::to_string(emptyPosition));
        //
        //            m->push_back([this, currentPosition, emptyPosition] {
        //                g->gameboard->MovePiece(currentPosition, emptyPosition);
        //            });
        //            out.insert(m);
        //
        //            m->description = m->description + "potem skok do " + std::to_string(emptyPosition - 2 - 20);
        //            checkPositionAndJump(m, out, emptyPosition, emptyPosition - 1 - 10, emptyPosition - 2 - 20);
        //            m->description = m->description + "potem skok do " + std::to_string(emptyPosition - 2 + 20);
        //            checkPositionAndJump(m, out, emptyPosition, emptyPosition - 1 + 10, emptyPosition - 2 + 20);
        //            m->description = m->description + "potem skok do " + std::to_string(emptyPosition + 2 - 20);
        //            checkPositionAndJump(m, out, emptyPosition, emptyPosition + 1 - 10, emptyPosition + 2 - 20);
        //            m->description = m->description + "potem skok do " + std::to_string(emptyPosition + 2 + 20);
        //            checkPositionAndJump(m, out, emptyPosition, emptyPosition + 1 + 10, emptyPosition + 2 + 20);
        //
        //
        //        }

    }

    void
        JumpAdder(BoardMove* oldMove, Coordinates difrence, std::set<BoardMove*>* out, Coordinates enemyPosition,
            Coordinates currentPosition,
            std::set<int> Jumped) {
        Coordinates checking_position = enemyPosition + difrence;
        while (g->gameboard->containsPiece(checking_position) &&
            g->gameboard->bo[checking_position.value]->name == "empty") {
            BoardMove* m = new BoardMove(*oldMove);
            m->description = m->description + "jump to " + (checking_position + difrence).toString() + " ";
            m->push_back([this, currentPosition = new Coordinates(currentPosition), enemyPosition = new Coordinates(
                enemyPosition), checking_position = new Coordinates(checking_position)] {
                    g->gameboard->RemovePiece(*enemyPosition);
            g->gameboard->MovePiece(*currentPosition, *checking_position);
                });
            out->insert(m);

            JumpSeeker(oldMove, Coordinates().up().right(), out, currentPosition, Jumped);
            JumpSeeker(oldMove, Coordinates().up().left(), out, currentPosition, Jumped);
            JumpSeeker(oldMove, Coordinates().down().right(), out, currentPosition, Jumped);
            JumpSeeker(oldMove, Coordinates().down().left(), out, currentPosition, Jumped);

            checking_position += location + difrence;
        }
    }

    void
        JumpSeeker(BoardMove* oldMove, Coordinates difrence, std::set<BoardMove*>* out, Coordinates currentPosition,
            std::set<int> Jumped) {
        Coordinates checking_position = currentPosition + difrence;
        while (g->gameboard->containsPiece(checking_position) &&
            g->gameboard->bo[checking_position.value]->name == "empty") {
            //            Move *m = new Move(*oldMove);
            //            m->description = m->description + "skok do " + std::to_string(checking_position+difrence)+" ";
            //            m->push_back([this,currentPosition, enemyPosition,checking_position] {
            //                g->gameboard->RemovePiece(enemyPosition);
            //                g->gameboard->MovePiece(currentPosition, checking_position);
            //            });
            //            out.insert(m);
            //
            //            czujka(Move *oldMove, int difrence, std::set<Move *> out, int currentPosition)

            checking_position += location + difrence;
        }
        if (g->gameboard->containsPiece(checking_position) &&
            g->gameboard->bo[checking_position.value]->loyalty != this->loyalty &&
            Jumped.find(currentPosition.value) != Jumped.end()) {
            Jumped.insert(currentPosition.value);
            JumpAdder(oldMove, difrence, out, currentPosition, currentPosition + difrence, Jumped);
        }
    }

    void
        checkPositionAndJump(std::set<BoardMove*>* out, BoardMove* oldMove, Coordinates currentPosition, Coordinates enemyPosition,
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

            m->description = m->description + " jump to " + emptyPosition.up().right().up().right().toString();
            checkPositionAndJump(out, m, emptyPosition, emptyPosition.up().right(),
                emptyPosition.up().right().up().right());
            m->description = m->description + " jump to " + emptyPosition.up().left().up().left().toString();
            checkPositionAndJump(out, m, emptyPosition, emptyPosition.up().left(),
                emptyPosition.up().left().up().left());
            m->description = m->description + " jump to " + emptyPosition.down().right().down().right().toString();
            checkPositionAndJump(out, m, emptyPosition, emptyPosition.down().right(),
                emptyPosition.down().right().down().right());
            m->description = m->description + " jump to " + emptyPosition.down().left().down().left().toString();
            checkPositionAndJump(out, m, emptyPosition, emptyPosition.down().left(),
                emptyPosition.down().left().down().left());


        }
    }

    //    void
    //    checkPositionAndJump2(Move *oldMove, int difrence, std::set<Move *> out, int currentPosition, int enemyPosition,
    //                          int emptyPosition) {
    //        int checking_position = enemyPosition + difrence;
    //        while (g->gameboard->bo.contains(checking_position) && g->gameboard->bo[checking_position]->name == "empty") {
    //            Move *m = new Move("skok", "skok do" + std::to_string(checking_position));
    //
    //            m->push_back([this, currentPosition, checking_position] {
    //                g->gameboard->MovePiece(currentPosition, checking_position);
    //            });
    //            out.insert(m);
    //            checkPositionAndJump3(Move * oldMove, int
    //            difrence, std::set<Move *>
    //            out, int
    //            currentPosition, int
    //            enemyPosition)
    //            checkPositionAndJump3(Move * oldMove, int
    //            difrence, std::set<Move *>
    //            out, int
    //            currentPosition, int
    //            enemyPosition)
    //            checkPositionAndJump3(Move * oldMove, int
    //            difrence, std::set<Move *>
    //            out, int
    //            currentPosition, int
    //            enemyPosition)
    //            checkPositionAndJump3(Move * oldMove, int
    //            difrence, std::set<Move *>
    //            out, int
    //            currentPosition, int
    //            enemyPosition)
    //            checking_position += location + difrence;
    //        }
    //    }
    //
    //    void
    //    checkPositionAndJump3(Move *oldMove, int difrence, std::set<Move *> out, int currentPosition) {
    //        int checking_position = currentPosition + difrence;
    //        while (g->gameboard->bo.contains(checking_position) && g->gameboard->bo[checking_position]->name == "empty") {
    //            checking_position += location + difrence;
    //        }
    //        if (g->gameboard->bo.contains(checking_position) && g->gameboard->bo[checking_position]->loyalty != this->loyalty &&
    //            g->gameboard->bo.contains(checking_position+difrence) && g->gameboard->bo[checking_position+difrence]->name == "empty") {
    //
    //            Move *m = new Move(*oldMove);
    //            m->description = m->description + "skok do " + std::to_string(checking_position+difrence)+" ";
    //            m->push_back([this,currentPosition, checking_position, difrence] {
    //                g->gameboard->RemovePiece(checking_position);
    //                g->gameboard->MovePiece(currentPosition, checking_position+difrence);
    //            });
    //            out.insert(m);
    //
    //            checkPositionAndJump2(m, , location, out, checking_position, checking_position + difrence);
    //        }
    //    }



};

#endif