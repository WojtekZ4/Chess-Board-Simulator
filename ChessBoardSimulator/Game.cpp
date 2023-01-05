//
// Created by wojte on 24-Dec-22.
//
#ifndef GAME_CPP
#define GAME_CPP

#include "Coordinates.cpp"
#include "Player.cpp"
#include "Board.cpp"
#include "GameDrawer.cpp"
#include "BoardMove.cpp"


class Game {
public:
    Board* gameboard;
    std::pair<Player*, Player*> players;
    Player* activePlayer;
    GameDrawer* myDrawer = new GameDrawer();
    bool gameEnded = false;
    std::map<Piece*, std::set<BoardMove*>> rememberedMovesMap;

    Game(std::string player1Name, std::string player2Name) {
        players.first = new Player(player1Name, true);
        players.second = new Player(player2Name, false);
        activePlayer = players.first;

    }

    Player* OtherPlayer(Player* p) {
        if (p == players.first)
            return players.second;
        else
            return players.first;
    }

    void WinGame(Player* winner) {
        std::cout << "gracz " + winner->name + " wygral!" << std::endl;
    }

    void RunGame() {
        while (!gameEnded) {
            //            std::cout << gameboard->DrawBoard();
            MakeMove(activePlayer);
            PostMoveUpdates();
            CheckGameEndConditions();
            activePlayer = OtherPlayer(activePlayer);
        }
    }

    virtual void PostMoveUpdates() {

    };

    virtual void CheckGameEndConditions() = 0;

    void MakeMove(Player* toMove) {
        //        std::map<Piece *, std::set<Move *>> allPosibleMoves;
        //        for (Piece *p: gameboard->PlayersPieces(toMove)) {
        //            allPosibleMoves.insert(std::pair<Piece *, std::set<Move *>>(p, p->getMoves()));
        //        }
        CalculateAllPosibleMoves(toMove);
        std::map<Piece*, std::set<BoardMove*>> allPosibleMoves = rememberedMovesMap;
        BoardMove* selectedMove = myDrawer->DetermineMove(gameboard->bo, toMove, allPosibleMoves);
        selectedMove->execute();
        //        Piece *selectedPiece = myDrawer->DeterminePiece(toMove, gameboard->PlayersPieces(toMove));
        //        std::set<Move *> posibleMoves = selectedPiece->getMoves(gameboard);
        //        Move *selectedMove = myDrawer->DetermineMove(posibleMoves);
        //        selectedMove->execute();
    }
    void ExecuteMove(BoardMove* m) {
        m->execute();
        PostMoveUpdates();
        CheckGameEndConditions();
        activePlayer = OtherPlayer(activePlayer);
        CalculateAllPosibleMoves(activePlayer);
    }


    virtual void CalculateAllPosibleMoves(Player* toMove) {
        std::map<Piece*, std::set<BoardMove*>> allPosibleMoves;
        for (Piece* p : gameboard->PlayersPieces(toMove)) {
            allPosibleMoves.insert(std::pair<Piece*, std::set<BoardMove*>>(p, p->getMoves()));
        }
        rememberedMovesMap = allPosibleMoves;
    }
};

#endif