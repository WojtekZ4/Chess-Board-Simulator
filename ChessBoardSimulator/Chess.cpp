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
	Chess() : Game() {
		name = "Chess";
	}
	virtual void setupBord() {
		gameboard = new Board(this);
		gameStatus = std::pair(false, "");
		activePlayer = players.first;
		players.first->dummyPiece = new ChessDummyPiece(gameboard, players.first);
		players.second->dummyPiece = new ChessDummyPiece(gameboard, players.second);

		gameboard->PlacePiece(new Rook(gameboard, players.first), Coordinates("a1"));
		gameboard->PlacePiece(new Knight(gameboard, players.first), Coordinates("b1"));
		gameboard->PlacePiece(new Bishop(gameboard, players.first), Coordinates("c1"));
		gameboard->PlacePiece(new Queen(gameboard, players.first), Coordinates("d1"));
		gameboard->PlacePiece(new ChessKing(gameboard, players.first), Coordinates("e1"));
		gameboard->PlacePiece(new Bishop(gameboard, players.first), Coordinates("f1"));
		gameboard->PlacePiece(new Knight(gameboard, players.first), Coordinates("g1"));
		gameboard->PlacePiece(new Rook(gameboard, players.first), Coordinates("h1"));

		gameboard->PlacePiece(new Pawn(gameboard, players.first), Coordinates("a2"));
		gameboard->PlacePiece(new Pawn(gameboard, players.first), Coordinates("b2"));
		gameboard->PlacePiece(new Pawn(gameboard, players.first), Coordinates("c2"));
		gameboard->PlacePiece(new Pawn(gameboard, players.first), Coordinates("d2"));
		gameboard->PlacePiece(new Pawn(gameboard, players.first), Coordinates("e2"));
		gameboard->PlacePiece(new Pawn(gameboard, players.first), Coordinates("f2"));
		gameboard->PlacePiece(new Pawn(gameboard, players.first), Coordinates("g2"));
		gameboard->PlacePiece(new Pawn(gameboard, players.first), Coordinates("h2"));

		gameboard->PlacePiece(new Rook(gameboard, players.second), Coordinates("a8"));
		gameboard->PlacePiece(new Knight(gameboard, players.second), Coordinates("b8"));
		gameboard->PlacePiece(new Bishop(gameboard, players.second), Coordinates("c8"));
		gameboard->PlacePiece(new Queen(gameboard, players.second), Coordinates("d8"));
		gameboard->PlacePiece(new ChessKing(gameboard, players.second), Coordinates("e8"));
		gameboard->PlacePiece(new Bishop(gameboard, players.second), Coordinates("f8"));
		gameboard->PlacePiece(new Knight(gameboard, players.second), Coordinates("g8"));
		gameboard->PlacePiece(new Rook(gameboard, players.second), Coordinates("h8"));

		gameboard->PlacePiece(new Pawn(gameboard, players.second), Coordinates("a7"));
		gameboard->PlacePiece(new Pawn(gameboard, players.second), Coordinates("b7"));
		gameboard->PlacePiece(new Pawn(gameboard, players.second), Coordinates("c7"));
		gameboard->PlacePiece(new Pawn(gameboard, players.second), Coordinates("d7"));
		gameboard->PlacePiece(new Pawn(gameboard, players.second), Coordinates("e7"));
		gameboard->PlacePiece(new Pawn(gameboard, players.second), Coordinates("f7"));
		gameboard->PlacePiece(new Pawn(gameboard, players.second), Coordinates("g7"));
		gameboard->PlacePiece(new Pawn(gameboard, players.second), Coordinates("h7"));

		//gameboard->PlacePiece(new Rook(gameboard, players.first), Coordinates("a4"));
		//gameboard->PlacePiece(new Rook(gameboard, players.first), Coordinates("a3"));
		//gameboard->PlacePiece(new Rook(gameboard, players.first), Coordinates("a2"));
		//gameboard->PlacePiece(new ChessKing(gameboard, players.first), Coordinates("e1"));

		//gameboard->PlacePiece(new Rook(gameboard, players.second), Coordinates("a7"));
		//gameboard->PlacePiece(new ChessKing(gameboard, players.second), Coordinates("e8"));

		CalculateAllPosibleMoves(activePlayer);
	}

	//void CalculateAllPosibleMoves(Player* toMove) {
	//    std::map<Piece*, std::set<BoardMove*>> allPosibleMoves;
	//    for (Piece* p : gameboard->PlayersPieces(toMove)) {
	//        allPosibleMoves.insert(std::pair<Piece*, std::set<BoardMove*>>(p, p->getMoves()));
	//    }
	//    rememberedMovesMap = allPosibleMoves;
	//}

	void PostMoveUpdates() {
		for (auto p : gameboard->PlayersPieces(OtherPlayer(activePlayer))) {
			p->removeTag("En Pessant possible");
			p->removeTag("checking");
		}
	}

	//bool pred2e(BoardMove* b) {
	//	Board* testBoard = new Board(*gameboard);
	//	b->execute(testBoard);
	//	std::map<Piece*, std::vector<BoardMove*>> predictedMoves = testBoard->readAllPlayerMovs(OtherPlayer(activePlayer));
	//	if (std::any_of(predictedMoves.begin(), predictedMoves.end(),
	//		[](std::pair<Piece*, std::vector<BoardMove*>> pp) {return pp.first->hasTag("checking"); }))
	//		return false;
	//	else
	//		return true;
	//}
	
	void PostCalculationUpdates() {
		std::map<Piece*, std::vector<BoardMove*>> allPosibleMoves_filtered;

		std::transform(rememberedMovesMap.begin(), rememberedMovesMap.end(),
			std::inserter(allPosibleMoves_filtered, allPosibleMoves_filtered.begin()),
			[this](std::pair<Piece*, std::vector<BoardMove*>> p) {
				std::vector<BoardMove*> newMoves;
		std::copy_if(p.second.begin(), p.second.end(), std::inserter(newMoves, newMoves.begin()), [this](BoardMove * b) {
			Board* testBoard = new Board(*gameboard);
			b->execute(testBoard);
			std::map<Piece*, std::vector<BoardMove*>> predictedMoves = testBoard->readAllPlayerMovs(OtherPlayer(activePlayer));
			if (std::any_of(predictedMoves.begin(), predictedMoves.end(),
				[](std::pair<Piece*, std::vector<BoardMove*>> pp) {return pp.first->hasTag("checking"); }))
				return false;
			else
				return true;
		});
		return std::pair(p.first, newMoves);
			});

		rememberedMovesMap = allPosibleMoves_filtered;


		//std::transform(rememberedMovesMap.begin(), rememberedMovesMap.end(),
		//	std::inserter(allPosibleMoves_filtered, allPosibleMoves_filtered.begin()),
		//	[this](std::pair<Piece*, std::set<BoardMove*>> p) {
		//		std::set<BoardMove*> newMoves;
		//		std::copy_if(p.second.begin(), p.second.end(), std::inserter(newMoves, newMoves.begin()),
		//	[this](BoardMove* b) {
		//		Board *testBoard =new Board(*gameboard);
		//		b->execute(testBoard);
		//		std::map<Piece*, std::set<BoardMove*>> predictedMoves =testBoard->readAllPlayerMovs(OtherPlayer(activePlayer));
		//		if (std::any_of(predictedMoves.begin(), predictedMoves.end(),
		//			[](std::pair<Piece*, std::set<BoardMove*>> pp) {return pp.first->hasTag("checking"); }))
		//			return false;
		//		else
		//			return true;
		//	});
		//	return std::pair(p.first, newMoves);
		//	});

		//rememberedMovesMap = allPosibleMoves_filtered;

	}
	

	//bool checkIfPlayerInCheck(Player* toCheck) {
	//	Player* otherPlayer = this->OtherPlayer(toCheck);
	//	CalculateAllPosibleMoves(otherPlayer);
	//	std::set<Piece*> otherPlayerPieces = gameboard->PlayersPieces(this->OtherPlayer(otherPlayer));
	//	return any_of(otherPlayerPieces.begin(), otherPlayerPieces.end(),
	//		[](Piece* p) { return p->hasTag("checking"); });
	//}
	void CheckGameEndConditions() {
		
		if (rememberedMovesMap.empty()) {
			gameStatus.first = true;
			gameboard->readAllPlayerMovs(OtherPlayer(activePlayer));
			std::set<Piece*> enemyPieces = gameboard->PlayersPieces(OtherPlayer(activePlayer));
			if (std::any_of(enemyPieces.begin(), enemyPieces.end(), [this](Piece* p) {return p->hasTag("checking"); })) {
				gameStatus.second = "Player " + OtherPlayer(activePlayer)->name + " wins the game as player " + activePlayer->name + " has been checkmated.";
			}
			else {
				gameStatus.second = "Game ends in a draw as " +activePlayer->name + " has no posible moves.";
			}
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
	//void CheckGameEndConditions() {
		//CalculateAllPosibleMoves(OtherPlayer(activePlayer));
		//std::map<Piece*, std::set<BoardMove*>> allPosibleMoves = rememberedMovesMap;
		//bool playerHasAnyMoves = any_of(allPosibleMoves.begin(), allPosibleMoves.end(),
		//	[](std::pair<Piece*, std::set<BoardMove*>> p) { return !p.second.empty(); });

		//std::set<Piece*> playerPieces = gameboard->PlayersPieces(OtherPlayer(activePlayer));

		//bool playerHasKing = any_of(playerPieces.begin(), playerPieces.end(),
		//	[](Piece* p) { return p->name == "King"; });

		//bool playerSurrendered = activePlayer->dummyPiece->hasTag("surrender");
		//if (playerSurrendered) {
		//	gameEnded = true;
		//	std::cout << "Game ends in a a player " + OtherPlayer(activePlayer)->name + " wictory as player " +
		//		activePlayer->name + " has surrendered\n";
		//}
		//else if (!playerHasKing) {
		//	gameEnded = true;
		//	std::cout << "Game ends in a a player " + activePlayer->name + " wictory as player " +
		//		OtherPlayer(activePlayer)->name + " lost their king\n";
		//}
		//else if (!playerHasAnyMoves) {
		//	gameEnded = true;
		//	std::cout << "Game ends in a draw as player " + OtherPlayer(activePlayer)->name +
		//		"can not make a move on their turn\n";
		//}
	/*}*/


};

#endif