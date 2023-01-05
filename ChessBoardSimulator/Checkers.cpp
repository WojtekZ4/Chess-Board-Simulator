//
// Created by wojte on 24-Dec-22.
//
#ifndef CHECKERS_CPP
#define CHECKERS_CPP

#include "Game.cpp"
#include "Soldier.cpp"
#include "CheckersKing.cpp"
#include "CheckersDummyPiece.cpp"
#include <iostream>
#include <functional>

class Checkers : public Game {
public:

    Checkers(std::string player1Name, std::string player2Name) : Game(player1Name, player2Name) {
        players.first->dummyPiece = new CheckersDummyPiece(this, players.first);
        players.second->dummyPiece = new CheckersDummyPiece(this, players.second);

        std::map<int, Piece*> piec;
        piec = {
                {Coordinates("a1").value, new Soldier(this, players.first, Coordinates("a1"))},
                {Coordinates("c1").value, new Soldier(this, players.first, Coordinates("c1"))},
                {Coordinates("e1").value, new Soldier(this, players.first, Coordinates("e1"))},
                {Coordinates("g1").value, new Soldier(this, players.first, Coordinates("g1"))},

                {Coordinates("b2").value, new Soldier(this, players.first, Coordinates("b2"))},
                {Coordinates("d2").value, new Soldier(this, players.first, Coordinates("d2"))},
                {Coordinates("f2").value, new Soldier(this, players.first, Coordinates("f2"))},
                {Coordinates("h2").value, new Soldier(this, players.first, Coordinates("h2"))},

                {Coordinates("a3").value, new Soldier(this, players.first, Coordinates("a3"))},
                {Coordinates("c3").value, new Soldier(this, players.first, Coordinates("c3"))},
                {Coordinates("e3").value, new Soldier(this, players.first, Coordinates("e3"))},
                {Coordinates("g3").value, new Soldier(this, players.first, Coordinates("g3"))},

                {Coordinates("b8").value, new Soldier(this, players.second, Coordinates("b8"))},
                {Coordinates("d8").value, new Soldier(this, players.second, Coordinates("d8"))},
                {Coordinates("f8").value, new Soldier(this, players.second, Coordinates("f8"))},
                {Coordinates("h8").value, new Soldier(this, players.second, Coordinates("h8"))},

                {Coordinates("a7").value, new Soldier(this, players.second, Coordinates("a7"))},
                {Coordinates("c7").value, new Soldier(this, players.second, Coordinates("c7"))},
                {Coordinates("e7").value, new Soldier(this, players.second, Coordinates("e7"))},
                {Coordinates("g7").value, new Soldier(this, players.second, Coordinates("g7"))},

                {Coordinates("b6").value, new Soldier(this, players.second, Coordinates("b6"))},
                {Coordinates("d6").value, new Soldier(this, players.second, Coordinates("d6"))},
                {Coordinates("f6").value, new Soldier(this, players.second, Coordinates("f6"))},
                {Coordinates("h6").value, new Soldier(this, players.second, Coordinates("h6"))},
        };
        gameboard = new Board(piec, this);
        CalculateAllPosibleMoves(activePlayer);
    };

    virtual void CalculateAllPosibleMoves(Player* toMove) {
        std::map<Piece*, std::set<BoardMove*>> allPosibleMoves;
        for (Piece* p : gameboard->PlayersPieces(toMove)) {
            allPosibleMoves.insert(std::pair<Piece*, std::set<BoardMove*>>(p, p->getMoves()));
        }
        rememberedMovesMap = allPosibleMoves;
    }

    void CheckGameEndConditions() {
    }


};

#endif