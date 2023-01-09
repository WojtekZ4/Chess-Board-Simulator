//
// Created by wojte on 24-Dec-22.
//

#ifndef BOARD_CPP
#define BOARD_CPP

#include "Piece.cpp"
#include "Coordinates.cpp"
#include "EmptySpace.cpp"
#include <set>
#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

class Game;

class Board {
public:
	std::map<Coordinates, Piece*> bo;
	Game* g;

	Board(Game* g) {
		this->g = g;
		for (int i = 1; i < 9; i++) {
			for (int j = 1; j < 9; j++) {
				PlacePiece(new EmptySpace(this), Coordinates(i, j));
			}
		}
	}

	Board(Board& other) {
		this->g = other.g;
		for (int i = 1; i < 9; i++) {
			for (int j = 1; j < 9; j++) {
				PlacePiece(other.getPiece(Coordinates(i, j))->clone(), Coordinates(i, j));
			}
		}
	}

	Piece* getPiece(Coordinates location) {
		return bo.at(location.value());
	}
	bool containsPiece(Coordinates location) {
		return bo.find(location.value()) != bo.end();
	}

	//    std::string DrawBoard() {
	//        std::string s = "";
	//        s.append(" abcdefgh\n");
	//        for (int i = 1; i < 9; i++) {
	//            s += std::to_string(i);
	//            for (int j = 1; j < 9; j++) {
	//                s += bo[j * 10 + i]->symbol;
	//            }
	//            s += '\n';
	//        }
	//        return s;
	//        return " abcdefgh\n"
	//               "8rnbqkbnr\n"
	//               "7pppppppp\n"
	//               "6........\n"
	//               "5........\n"
	//               "4........\n"
	//               "3........\n"
	//               "2PPPPPPPP\n"
	//               "1RNBQKBNR";
	//    }

	void MovePiece(Coordinates  start, Coordinates  end) {
		Piece* toMove = getPiece(start);
		RemovePiece(start);
		PlacePiece(toMove, end);
	}

	void RemovePiece(Coordinates location) {
		PlacePiece(new EmptySpace(this), location);
	}

	//    template<Field* location>
	//    void RemovePiece_t() {
	//        location->setContent(nullptr);
	//    }

	//    void ReplacePiece(Field *location, Piece *newPiece) {
	//        location->setContent(newPiece);
	//        newPiece->location=location->location;
	//    }

	void PlacePiece(Piece* newPiece, Coordinates location) {
		bo[location.value()] = newPiece;
		newPiece->location = location;
		newPiece->b = this;
	}

	//    void cos2() {
	//        int (Board::*fun_ptr2)(int);
	//        fun_ptr2=&Board::foo;
	//        int (Board::*fun_ptr3)();
	//        fun_ptr3=&Board::foo;
	//        std::vector<void (Board::*)(Field *,Piece *)> dupa;
	//
	//        void (Board::*fun_ptr)(Field *,Piece *);
	//        fun_ptr = &Board::PlacePiece;
	//        dupa.push_back(fun_ptr);
	//    }

	std::set<Piece*> PlayersPieces(Player* piecesOwner) {
		std::map<Coordinates, Piece*> out1;

		std::copy_if(bo.begin(), bo.end(), std::inserter(out1, out1.begin()),
			[&piecesOwner](const std::pair<Coordinates, Piece*>& p) { return p.second->loyalty == piecesOwner; });

		std::set<Piece*> out2;

		if (piecesOwner->dummyPiece != nullptr) out2.insert(piecesOwner->dummyPiece);

		transform(out1.cbegin(), out1.cend(),
			std::inserter(out2, out2.begin()),
			[](const std::pair<Coordinates, Piece*>& key_value) { return key_value.second; });

		return out2;
	}

	std::map<Piece*, std::vector<BoardMove*>> readAllPlayerMovs(Player* toMove) {
		std::map<Piece*, std::vector<BoardMove*>> allPosibleMoves;
		for (Piece* p : PlayersPieces(toMove)) {
			allPosibleMoves.insert(std::pair<Piece*, std::vector<BoardMove*>>(p, p->getMoves()));
		}
		return allPosibleMoves;
	}
	//    Board() {}
	//    Field* Movees(Piece* toMove){}


};
// copy only positive numbers:

#endif
