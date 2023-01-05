//
// Created by wojte on 24-Dec-22.
//
#ifndef PIECE_CPP
#define PIECE_CPP

#include <map>
#include <string>
#include "Player.cpp"
#include "BoardMove.cpp"
#include <cctype>
#include "Coordinates.cpp"

class Game;

class Player;

class Piece {
public:
    Coordinates location;
    std::string name;
    std::set<std::string> tags;
    Player* loyalty;
    char symbol;
    Game* g;
    std::string icon;

    Piece(Game* g, Player* loyalty, char symbol, std::string name, Coordinates location, std::string icon) {
        this->g = g;
        this->loyalty = loyalty;
        if (loyalty != nullptr && loyalty->lowerBoardSide)
            this->symbol = (char)toupper(symbol);
        else
            this->symbol = (char)tolower(symbol);

        this->name = name;
        this->location = Coordinates(location);
        this->icon = icon;
    }

    void addTag(std::string tag) {
        tags.insert(tag);
    }

    void removeTag(std::string tag) {
        tags.erase(tag);
    }

    bool hasTag(std::string tag) {
        return std::find(tags.begin(), tags.end(), tag) != tags.end();
    }

    virtual std::set<BoardMove*> getMoves() = 0;

    virtual std::string toString() {
        return name + " at " + location.toString();
    }

};

#endif