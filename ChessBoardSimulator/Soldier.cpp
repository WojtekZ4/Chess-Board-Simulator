//
// Created by wojte on 28-Dec-22.
//
#ifndef SOLDIER_CPP
#define SOLDIER_CPP

#include <optional>
#include "Game.cpp"
#include "Piece.cpp"
#include "CheckersKing.cpp"

class Soldier : public Piece {
public:
	bool orientatedUp;
	Coordinates forward;
	Soldier(Board* b, Player* loyalty) : Piece(b, loyalty, 'o', "Soldier",
		loyalty->lowerBoardSide ? "../Resources/source_1/White/Pawn.jpg" : "../Resources/source_1/Black/Pawn.jpg") {
		this->orientatedUp = loyalty->lowerBoardSide;
		if (orientatedUp)
			forward = Coordinates().up();
		else
			forward = Coordinates().down();
	}
	Soldier* clone() const override {
		return new Soldier(*this);
	};

	std::vector<BoardMove*> getMoves() {
		std::vector<BoardMove*> out;


		checkPositionAndMove(&out, location.right() + forward);
		checkPositionAndMove(&out, location.left() + forward);

		checkPositionAndJump15(&out, location, Coordinates().right());
		checkPositionAndJump15(&out, location, Coordinates().left());
		return out;
	}

	void checkPositionAndMove(std::vector<BoardMove*>* out, Coordinates position) {
		if (b->containsPiece(position) && b->getPiece(position)->name == "empty") {
			BoardMove* m = new BoardMove("move", "Move to " + position.toString());

			m->push_back([location = new Coordinates(location), position = new Coordinates(position)](Board* b) {
				b->MovePiece(*location, *position);
				});

			checkForPromotion(m, position);
			out->push_back(m);
		}

	}

	void checkForPromotion(BoardMove* oldMove, Coordinates position) {
		if ((position.y == 8 && orientatedUp) || (position.y == 1 && !orientatedUp)) {
			oldMove->description = oldMove->description + " and promote to King";
			oldMove->push_back([position = new Coordinates(position)](Board* b) {
				Piece* oldPiece(b->getPiece(*position));
				b->RemovePiece(*position);
				b->PlacePiece(new CheckersKing(b, oldPiece->loyalty), *position);
				});
		}
	}
	void checkPositionAndJump15(std::vector<BoardMove*>* out, Coordinates currentPosition, Coordinates direction) {
		Coordinates enemyPosition = currentPosition + forward + direction;
		Coordinates emptyPosition = enemyPosition + forward + direction;
		if (b->containsPiece(enemyPosition) &&
			b->getPiece(enemyPosition)->name != "empty" &&
			b->getPiece(enemyPosition)->loyalty != this->loyalty &&
			b->containsPiece(emptyPosition) &&
			b->getPiece(emptyPosition)->name == "empty") {

			addTag("can attack");

			BoardMove* m = new BoardMove("jump", "Jump to " + emptyPosition.toString());
			m->push_back([enemyPosition = new Coordinates(enemyPosition), currentPosition = new Coordinates(
				currentPosition), emptyPosition = new Coordinates(emptyPosition)](Board* b) {
					b->RemovePiece(*enemyPosition);
					b->MovePiece(*currentPosition, *emptyPosition);
				});

			checkForPromotion(m, emptyPosition);
			out->push_back(m);

			checkPositionAndJump2(m, out, emptyPosition, Coordinates().right());
			checkPositionAndJump2(m, out, emptyPosition, Coordinates().left());
		}
	}
	void checkPositionAndJump2(BoardMove* oldMove, std::vector<BoardMove*>* out, Coordinates currentPosition, Coordinates direction) {
		Coordinates enemyPosition = currentPosition + forward + direction;
		Coordinates emptyPosition = enemyPosition + forward + direction;
		if (b->containsPiece(enemyPosition) &&
			b->getPiece(enemyPosition)->name != "empty" &&
			b->getPiece(enemyPosition)->loyalty != this->loyalty &&
			b->containsPiece(emptyPosition) &&
			b->getPiece(emptyPosition)->name == "empty") {

			addTag("can attack");

			BoardMove* m = new BoardMove(*oldMove);
			m->description = m->description + " then jump to " + emptyPosition.toString();

			m->push_back([enemyPosition = new Coordinates(enemyPosition), currentPosition = new Coordinates(
				currentPosition), emptyPosition = new Coordinates(emptyPosition)](Board* b) {
					b->RemovePiece(*enemyPosition);
					b->MovePiece(*currentPosition, *emptyPosition);
				});

			checkForPromotion(m, emptyPosition);
			out->push_back(m);

			checkPositionAndJump2(m, out, emptyPosition, Coordinates().right());
			checkPositionAndJump2(m, out, emptyPosition, Coordinates().left());
		}
	}
	//void checkPositionAndJump(BoardMove* oldMove, std::vector<BoardMove*>* out, Coordinates currentPosition, Coordinates enemyPosition,
	//        Coordinates emptyPosition) {
	//    if (g->gameboard->containsPiece(enemyPosition) &&
	//        g->gameboard->getPiece(enemyPosition)->loyalty != this->loyalty &&
	//        g->gameboard->containsPiece(emptyPosition) && g->gameboard->getPiece(emptyPosition)->name == "empty") {
	//        BoardMove* m = new BoardMove(*oldMove);

	//        m->push_back([this, enemyPosition = new Coordinates(enemyPosition), currentPosition = new Coordinates(
	//            currentPosition), emptyPosition = new Coordinates(emptyPosition)] {
	//                g->gameboard->RemovePiece(*enemyPosition);
	//        g->gameboard->MovePiece(*currentPosition, *emptyPosition);
	//            });
	//        out->push_back(m);
	//        if (orientatedUp) {
	//            m->description = m->description + "then jump to " + emptyPosition.up().right().up().right().toString();
	//            checkPositionAndJump(m, out, emptyPosition, emptyPosition.up().right(),
	//                emptyPosition.up().right().up().right());
	//            m->description = m->description + "then jump to " + emptyPosition.up().left().up().left().toString();
	//            checkPositionAndJump(m, out, emptyPosition, emptyPosition.up().left(),
	//                emptyPosition.up().left().up().left());
	//        }
	//        else {
	//            m->description =
	//                m->description + "then jump to " + emptyPosition.down().right().down().right().toString();
	//            checkPositionAndJump(m, out, emptyPosition, emptyPosition.down().right(),
	//                emptyPosition.down().right().down().right());
	//            m->description =
	//                m->description + "then jump to " + emptyPosition.down().left().down().left().toString();
	//            checkPositionAndJump(m, out, emptyPosition, emptyPosition.down().left(),
	//                emptyPosition.down().left().down().left());
	//        }

	//    }
	//}
};

#endif