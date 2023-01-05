//
// Created by wojte on 24-Dec-22.
//
#ifndef CHESS_CPP
#define CHESS_CPP

#include "Game.cpp"
#include "Pawn.cpp"
#include "Rook.cpp"
#include "Bishop.cpp"
#include "Queen.cpp"
#include "Knight.cpp"
#include "ChessDummyPiece.cpp"
#include "ChessKing.cpp"
#include <iostream>
#include <functional>
#include "Coordinates.cpp"

class Chess : public Game {
public:

    Chess(std::string player1Name, std::string player2Name) : Game(player1Name, player2Name) {
        players.first->dummyPiece = new ChessDummyPiece(this, players.first);
        players.second->dummyPiece = new ChessDummyPiece(this, players.second);

        std::map<int, Piece*> piec;
        piec = {
                {Coordinates("a1").value, new Rook(this, players.first, Coordinates("a1"))},
                {Coordinates("b1").value, new Knight(this, players.first, Coordinates("b1"))},
                {Coordinates("c1").value, new Bishop(this, players.first, Coordinates("c1"))},
                {Coordinates("d1").value, new Queen(this, players.first, Coordinates("d1"))},
                {Coordinates("e1").value, new ChessKing(this, players.first, Coordinates("e1"))},
                {Coordinates("f1").value, new Bishop(this, players.first, Coordinates("f1"))},
                {Coordinates("g1").value, new Knight(this, players.first, Coordinates("g1"))},
                {Coordinates("h1").value, new Rook(this, players.first, Coordinates("h1"))},

                {Coordinates("a2").value, new Pawn(this, players.first, Coordinates("a2"))},
                {Coordinates("b2").value, new Pawn(this, players.first, Coordinates("b2"))},
                {Coordinates("c2").value, new Pawn(this, players.first, Coordinates("c2"))},
                {Coordinates("d2").value, new Pawn(this, players.first, Coordinates("d2"))},
                {Coordinates("e2").value, new Pawn(this, players.first, Coordinates("e2"))},
                {Coordinates("f2").value, new Pawn(this, players.first, Coordinates("f2"))},
                {Coordinates("g2").value, new Pawn(this, players.first, Coordinates("g2"))},
                {Coordinates("h2").value, new Pawn(this, players.first, Coordinates("h2"))},

                {Coordinates("a8").value, new Rook(this, players.second, Coordinates("a8"))},
                {Coordinates("b8").value, new Knight(this, players.second, Coordinates("b8"))},
                {Coordinates("c8").value, new Bishop(this, players.second, Coordinates("c8"))},
                {Coordinates("d8").value, new Queen(this, players.second, Coordinates("d8"))},
                {Coordinates("e8").value, new ChessKing(this, players.second, Coordinates("e8"))},
                {Coordinates("f8").value, new Bishop(this, players.second, Coordinates("f8"))},
                {Coordinates("g8").value, new Knight(this, players.second, Coordinates("g8"))},
                {Coordinates("h8").value, new Rook(this, players.second, Coordinates("h8"))},

                {Coordinates("a7").value, new Pawn(this, players.second, Coordinates("a7"))},
                {Coordinates("b7").value, new Pawn(this, players.second, Coordinates("b7"))},
                {Coordinates("c7").value, new Pawn(this, players.second, Coordinates("c7"))},
                {Coordinates("d7").value, new Pawn(this, players.second, Coordinates("d7"))},
                {Coordinates("e7").value, new Pawn(this, players.second, Coordinates("e7"))},
                {Coordinates("f7").value, new Pawn(this, players.second, Coordinates("f7"))},
                {Coordinates("g7").value, new Pawn(this, players.second, Coordinates("g7"))},
                {Coordinates("h7").value, new Pawn(this, players.second, Coordinates("h7"))},
        };
        gameboard = new Board(piec, this);
        CalculateAllPosibleMoves(activePlayer);
    };

    void CalculateAllPosibleMoves(Player* toMove) {
        std::map<Piece*, std::set<BoardMove*>> allPosibleMoves;
        for (Piece* p : gameboard->PlayersPieces(toMove)) {
            allPosibleMoves.insert(std::pair<Piece*, std::set<BoardMove*>>(p, p->getMoves()));
        }
        rememberedMovesMap = allPosibleMoves;
    }

    void PostMoveUpdates() {
        for (auto p : gameboard->PlayersPieces(OtherPlayer(activePlayer))) {
            p->removeTag("En Pessant possible");
        }
    }

    bool checkIfPlayerInCheck(Player* toCheck) {
        Player* otherPlayer = this->OtherPlayer(toCheck);
        CalculateAllPosibleMoves(otherPlayer);
        std::set<Piece*> otherPlayerPieces = gameboard->PlayersPieces(this->OtherPlayer(otherPlayer));
        return any_of(otherPlayerPieces.begin(), otherPlayerPieces.end(),
            [](Piece* p) { return p->hasTag("Checking"); });
    }

    void CheckGameEndConditions() {
        CalculateAllPosibleMoves(OtherPlayer(activePlayer));
        std::map<Piece*, std::set<BoardMove*>> allPosibleMoves = rememberedMovesMap;
        bool playerHasAnyMoves = any_of(allPosibleMoves.begin(), allPosibleMoves.end(),
            [](std::pair<Piece*, std::set<BoardMove*>> p) { return !p.second.empty(); });

        std::set<Piece*> playerPieces = gameboard->PlayersPieces(OtherPlayer(activePlayer));

        bool playerHasKing = any_of(playerPieces.begin(), playerPieces.end(),
            [](Piece* p) { return p->name == "King"; });

        bool playerSurrendered = activePlayer->dummyPiece->hasTag("surrender");
        if (playerSurrendered) {
            gameEnded = true;
            std::cout << "Game ends in a a player " + OtherPlayer(activePlayer)->name + " wictory as player " +
                activePlayer->name + " has surrendered\n";
        }
        else if (!playerHasKing) {
            gameEnded = true;
            std::cout << "Game ends in a a player " + activePlayer->name + " wictory as player " +
                OtherPlayer(activePlayer)->name + " lost their king\n";
        }
        else if (!playerHasAnyMoves) {
            gameEnded = true;
            std::cout << "Game ends in a draw as player " + OtherPlayer(activePlayer)->name +
                "can not make a move on their turn\n";
        }
    }


};

#endif