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
	Checkers() : Game() {
		name = "Checkers";
	}
	virtual void setupBord() {
		gameboard = new Board(this);
		gameStatus = std::pair(false, "");
		activePlayer = players.first;
		players.first->dummyPiece = new CheckersDummyPiece(gameboard, players.first);
		players.second->dummyPiece = new CheckersDummyPiece(gameboard, players.second);

		//gameboard->PlacePiece(new CheckersKing(gameboard, players.first), Coordinates("g1"));

		gameboard->PlacePiece(new Soldier(gameboard, players.first), Coordinates("a1"));
		gameboard->PlacePiece(new Soldier(gameboard, players.first), Coordinates("c1"));
		gameboard->PlacePiece(new Soldier(gameboard, players.first), Coordinates("e1"));
		gameboard->PlacePiece(new Soldier(gameboard, players.first), Coordinates("g1"));

		gameboard->PlacePiece(new Soldier(gameboard, players.first), Coordinates("b2"));
		gameboard->PlacePiece(new Soldier(gameboard, players.first), Coordinates("d2"));
		gameboard->PlacePiece(new Soldier(gameboard, players.first), Coordinates("f2"));
		gameboard->PlacePiece(new Soldier(gameboard, players.first), Coordinates("h2"));

		gameboard->PlacePiece(new Soldier(gameboard, players.first), Coordinates("a3"));
		gameboard->PlacePiece(new Soldier(gameboard, players.first), Coordinates("c3"));
		gameboard->PlacePiece(new Soldier(gameboard, players.first), Coordinates("e3"));
		gameboard->PlacePiece(new Soldier(gameboard, players.first), Coordinates("g3"));

		gameboard->PlacePiece(new Soldier(gameboard, players.second), Coordinates("b8"));
		gameboard->PlacePiece(new Soldier(gameboard, players.second), Coordinates("d8"));
		gameboard->PlacePiece(new Soldier(gameboard, players.second), Coordinates("f8"));
		gameboard->PlacePiece(new Soldier(gameboard, players.second), Coordinates("h8"));

		gameboard->PlacePiece(new Soldier(gameboard, players.second), Coordinates("a7"));
		gameboard->PlacePiece(new Soldier(gameboard, players.second), Coordinates("c7"));
		gameboard->PlacePiece(new Soldier(gameboard, players.second), Coordinates("e7"));
		gameboard->PlacePiece(new Soldier(gameboard, players.second), Coordinates("g7"));

		gameboard->PlacePiece(new Soldier(gameboard, players.second), Coordinates("b6"));
		gameboard->PlacePiece(new Soldier(gameboard, players.second), Coordinates("d6"));
		gameboard->PlacePiece(new Soldier(gameboard, players.second), Coordinates("f6"));
		gameboard->PlacePiece(new Soldier(gameboard, players.second), Coordinates("h6"));

		CalculateAllPosibleMoves(activePlayer);
	}


	//virtual void CalculateAllPosibleMoves(Player* toMove) {
	//    std::map<Piece*, std::vector<BoardMove*>> allPosibleMoves;
	//    for (Piece* p : gameboard->PlayersPieces(toMove)) {
	//        allPosibleMoves.insert(std::pair<Piece*, std::vector<BoardMove*>>(p, p->getMoves()));
	//    }
	//    rememberedMovesMap = allPosibleMoves;
	//}

	void CheckGameEndConditions() {
		if (gameboard->PlayersPieces(activePlayer).empty()) {
			gameStatus.first = true;
			gameStatus.second = "Player " + OtherPlayer(activePlayer)->name + " wins the game as player " + activePlayer->name + " lost all pieces.";
		}
		else if (rememberedMovesMap.empty()) {
			gameStatus.first = true;
			gameStatus.second = "Player " + OtherPlayer(activePlayer)->name + " wins the game as player " + activePlayer->name + " has no posible moves.";
		}
		else if (plyerSurrenderd(OtherPlayer(activePlayer))) {
			gameStatus.first = true;
			gameStatus.second = "Player " + OtherPlayer(activePlayer)->name + " wins the game as player " + activePlayer->name + " has surrendered.";
		}
	}

	bool plyerSurrenderd(Player* toChech) {
		auto pp = gameboard->PlayersPieces(toChech);
		return std::any_of(pp.begin(), pp.end(), [](Piece* p) {return p->hasTag("surrendered"); });
	}
	virtual void PostCalculationUpdates() {

		if (std::find_if(rememberedMovesMap.begin(), rememberedMovesMap.end(),
			[](std::pair<Piece*, std::vector<BoardMove*>> p) {return p.first->hasTag("can attack"); })
			!= rememberedMovesMap.end()) {

			std::map<Piece*, std::vector<BoardMove*>> allPosibleMoves_filtered;
			std::transform(rememberedMovesMap.begin(), rememberedMovesMap.end(),
				std::inserter(allPosibleMoves_filtered, allPosibleMoves_filtered.begin()),
				[](std::pair<Piece*, std::vector<BoardMove*>> p) {
					std::vector<BoardMove*> newMoves;
			std::copy_if(p.second.begin(), p.second.end(), std::inserter(newMoves, newMoves.begin()),
				[](BoardMove* b) {return b->name == "jump"; });
			return std::pair(p.first, newMoves);
				});

			//for (auto a : rememberedMovesMap) {
			//    std::vector<BoardMove*> newMoves;
			//    std::copy_if(a.second.begin(), a.second.end(), std::inserter(newMoves, newMoves.begin()),
			//        [](BoardMove* b) {return b->name=="jump"; });
			//    rememberedMovesMap
			//}

			rememberedMovesMap = allPosibleMoves_filtered;
		}
	};

	void PostMoveUpdates() {
		for (auto p : gameboard->PlayersPieces(OtherPlayer(activePlayer))) {
			p->removeTag("can attack");
		}
	}

};

#endif