//
// Created by wojte on 28-Dec-22.
//
#ifndef EMPTYSPACE_CPP
#define EMPTYSPACE_CPP

#include "Piece.cpp"

class EmptySpace : public Piece {
public:
    EmptySpace(Game* g, Coordinates location) : Piece(g, nullptr, '.', "empty", location, "../Resources/Empty Space.jpg") {}

    std::set<BoardMove*> getMoves() {
        std::set<BoardMove*> out;
        return out;
    }
};

#endif