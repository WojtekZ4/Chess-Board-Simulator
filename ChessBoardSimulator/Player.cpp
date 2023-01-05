//
// Created by wojte on 24-Dec-22.
//

#ifndef PLAYER_CPP
#define PLAYER_CPP

#include <set>
#include <string>

//#include "Piece.cpp"
class Piece;

class Player {
private:
    //    std::set<Piece*> myPieces;
public:
    std::string name;
    Piece* dummyPiece;
    bool lowerBoardSide;

    Player(std::string name, bool lowerBoardSide) {
        this->name = name;
        dummyPiece = nullptr;
        this->lowerBoardSide = lowerBoardSide;
    }



    //    Player(std::string name,Piece* dummyPiece ) {
    //        this->name = name;
    //        this->dummyPiece = dummyPiece;
    //    }
    //    std::set<Move *>  getDummyMoves(){
    //        if(dummyPiece!= nullptr){
    //            return dummyPiece->getMoves()
    //        }
    //    }
    //    Player() {}
    //    void MakeMove(){}


};

#endif
