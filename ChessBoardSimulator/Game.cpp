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

#include <string>
#include <iostream>

class Game {
public:
	Board* gameboard;
	std::pair<Player*, Player*> players;
	Player* activePlayer;
	GameDrawer* myDrawer = new GameDrawer();
	std::pair<bool,std::string> gameStatus = std::pair(false,"");
	std::map<Piece*, std::vector<BoardMove*>> rememberedMovesMap;
	std::string name;
	Game() {
		players.first = new Player("Player One", true);
		players.second = new Player("Player Two", false);
		activePlayer = players.first;
		gameboard = new Board(this);
		name = "";
	}

	virtual void setupBord() = 0;


	void setPlayersNames(std::string player1Name, std::string player2Name) {
		players.first->name = player1Name;
		players.second->name = player2Name;
	}

	Player* OtherPlayer(Player* p) {
		if (p == players.first)
			return players.second;
		else
			return players.first;
	}

	//void RunGame() {
	//	while (!gameEnded) {
	//		//            std::cout << gameboard->DrawBoard();
	//		MakeMove(activePlayer);
	//		PostMoveUpdates();
	//		CheckGameEndConditions();
	//		activePlayer = OtherPlayer(activePlayer);
	//	}
	//}

	virtual void PostMoveUpdates() = 0;

	virtual void PostCalculationUpdates() = 0;

	virtual void CheckGameEndConditions() = 0;

	void MakeMove(Player* toMove) {
		//        std::map<Piece *, std::set<Move *>> allPosibleMoves;
		//        for (Piece *p: gameboard->PlayersPieces(toMove)) {
		//            allPosibleMoves.insert(std::pair<Piece *, std::set<Move *>>(p, p->getMoves()));
		//        }
		//CalculateAllPosibleMoves(toMove);
		//std::map<Piece*, std::set<BoardMove*>> allPosibleMoves = rememberedMovesMap;
		//BoardMove* selectedMove = myDrawer->DetermineMove(gameboard->bo, toMove, allPosibleMoves);
		//selectedMove->execute();
		//        Piece *selectedPiece = myDrawer->DeterminePiece(toMove, gameboard->PlayersPieces(toMove));
		//        std::set<Move *> posibleMoves = selectedPiece->getMoves(gameboard);
		//        Move *selectedMove = myDrawer->DetermineMove(posibleMoves);
		//        selectedMove->execute();
	}
	void ExecuteMove(BoardMove* m) {
		m->execute(gameboard);
		PostMoveUpdates();
		activePlayer = OtherPlayer(activePlayer);
		CalculateAllPosibleMoves(activePlayer);
		CheckGameEndConditions();
	}

	void CalculateAllPosibleMoves(Player* toMove) {
		rememberedMovesMap.clear();

		rememberedMovesMap = gameboard->readAllPlayerMovs(toMove);
		PostCalculationUpdates();
		rememberedMovesMap = filterEmptyMoves();
	}


	std::map<Piece*, std::vector<BoardMove*>> filterEmptyMoves() {
		std::map<Piece*, std::vector<BoardMove*>> allPosibleMoves_filtered;
		auto pred = [](std::pair<Piece*, std::vector<BoardMove*>> p) {return !p.second.empty(); };
		std::copy_if(rememberedMovesMap.begin(), rememberedMovesMap.end(),
			std::inserter(allPosibleMoves_filtered, allPosibleMoves_filtered.begin()), pred);

		return allPosibleMoves_filtered;
	}

};

#endif