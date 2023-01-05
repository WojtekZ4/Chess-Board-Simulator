//
// Created by wojte on 28-Dec-22.
//
//
// Created by wojte on 24-Dec-22.
//
#ifndef GAMEDRAWER_CPP
#define GAMEDRAWER_CPP

#include <map>
#include <iostream>
#include "BoardMove.cpp"
#include "Piece.cpp"
#include <algorithm>

class GameDrawer {
public:
    void DrawBoard(std::map<int, Piece*> bo) {
        std::string s = "";
        s.append("   abcdefgh\n");
        s.append("\n");
        for (int i = 8; i > 0; i--) {
            s += std::to_string(i) + "  ";
            for (int j = 1; j < 9; j++) {
                s += bo[j * 10 + i]->symbol;
            }
            s += '\n';
        }
        s.append("\n");
        std::cout << s;
    }

    BoardMove* DetermineMove(std::map<int, Piece*> bo, Player* toMove, std::map<Piece*, std::set<BoardMove*>> allMoves) {

        BoardMove* selectedMove;
        do {
            system("cls");
            DrawBoard(bo);
            std::cout << "Player's " << toMove->name << " move." << std::endl;
            Piece* selectedPiece = ChosePiece(allMoves);

            system("cls");
            DrawBoard(bo);
            std::cout << "Player's " << toMove->name << " move." << std::endl;
            std::set<BoardMove*> posibleMoves = allMoves[selectedPiece];
            selectedMove = ChoseMove(selectedPiece, posibleMoves);
        } while (selectedMove->name == "Go Back");


        return selectedMove;
    }

    Piece* ChosePiece(std::map<Piece*, std::set<BoardMove*>> allMoves) {
        std::map<std::string, Piece*> orderdUsablePieces = DrawUsablePieces(allMoves);
        std::string in = "";
        do {
            std::cout << "Select piece: ";
            std::cin >> in;

        } while (orderdUsablePieces.find(in) == orderdUsablePieces.end());

        Piece* selectedPiece = orderdUsablePieces.at(in);
        return selectedPiece;
    }

    BoardMove* ChoseMove(Piece* piece, std::set<BoardMove*> posibleMoves) {
        std::map<std::string, BoardMove*> orderdPosibleMoves = DrawPossibleMoves(piece, posibleMoves);

        std::string in = "";

        while (orderdPosibleMoves.find(in) == orderdPosibleMoves.end()) {
            std::cout << "Select move: ";
            std::cin >> in;
        }
        BoardMove* selectedMove = orderdPosibleMoves.at(in);
        return selectedMove;
    }

    std::map<std::string, Piece*> DrawUsablePieces(std::map<Piece*, std::set<BoardMove*>> allPieces) {

        std::map<std::string, Piece*> mapedUsablePieces;
        int i = 1001;
        std::transform(allPieces.begin(), allPieces.end(),
            std::inserter(mapedUsablePieces, mapedUsablePieces.begin()),
            [&](std::pair<Piece*, std::set<BoardMove*>> obj) {
                std::string s = std::to_string(i++);
        return std::make_pair(s.substr(1, s.length()), obj.first);
            });
        std::string s = "";
        for (auto a : mapedUsablePieces) {
            s.append(a.first + ". " + a.second->toString() + "\n");
        }
        std::cout << "Selectable pieces: " << std::endl;
        std::cout << s;

        return mapedUsablePieces;
    }

    std::map<std::string, BoardMove*> DrawPossibleMoves(Piece* piece, std::set<BoardMove*> possibleMoves) {
        std::map<std::string, BoardMove*> mapedPossibleMoves;
        int i = 1001;
        std::transform(possibleMoves.begin(), possibleMoves.end(),
            std::inserter(mapedPossibleMoves, mapedPossibleMoves.begin()), [&](BoardMove* obj) {
                std::string s = std::to_string(i++);
        return std::make_pair(s.substr(1, s.length()), obj);
            });
        mapedPossibleMoves.insert(std::pair("b", new BoardMove("Go Back", "Go Back")));
        std::string s = "";
        for (auto a : mapedPossibleMoves) {
            s.append(a.first + ". " + a.second->toString() + "\n");
        }

        std::cout << "Selectable moves for " + piece->toString() + ": " << std::endl;
        std::cout << s;
        return mapedPossibleMoves;
    }


};

#endif