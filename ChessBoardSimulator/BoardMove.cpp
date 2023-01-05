//
// Created by wojte on 28-Dec-22.
//

#ifndef BOARDMOVE_CPP
#define BOARDMOVE_CPP

#include <vector>
#include <functional>
#include <string>

class BoardMove {
public:
    std::vector<std::function<void()>> moves;
    std::string name;
    std::string description;
    BoardMove(std::string name, std::string description) {
        this->name = name;
        this->description = description;
    }

    BoardMove(BoardMove& other) {
        this->name = other.name;
        this->description = other.description;
        this->moves = std::vector<std::function<void()>>(other.moves);
    }

    void addDescription(std::string moreDescription) {
        description += moreDescription;
    }

    void push_back(std::function<void()> toInsert) {
        moves.push_back(toInsert);
    }

    void execute() {
        for (auto m : moves) {
            m();
        }
    }

    std::string toString() {
        return description;
    }
};

#endif