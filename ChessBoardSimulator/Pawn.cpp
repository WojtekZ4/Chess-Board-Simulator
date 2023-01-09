//
// Created by wojte on 28-Dec-22.
//
#ifndef PAWN_CPP
#define PAWN_CPP

#include <optional>
#include "Piece.cpp"
#include "Game.cpp"
#include "Rook.cpp"
#include "Bishop.cpp"
#include "Knight.cpp"
#include "Queen.cpp"
#include "ChessKing.cpp"

class Pawn : public Piece {
public:
	bool orientatedUp;
	Coordinates forward;

	Pawn(Board* b, Player* loyalty)
		: Piece(b, loyalty, 'p', "Pawn",
			loyalty->lowerBoardSide ? "../Resources/source_1/White/Pawn.jpg" : "../Resources/source_1/Black/Pawn.jpg") {
		this->orientatedUp = loyalty->lowerBoardSide;
		if (orientatedUp)
			forward = Coordinates().up();
		else
			forward = Coordinates().down();
	}

	Pawn* clone() const override {
		return new Pawn(*this);
	};

	std::vector<BoardMove*> getMoves() {
		std::vector<BoardMove*> out;
		checkForMove(&out);
		checkForCapture(&out);
		return out;
	}

	void checkPositionForMoveForward(std::vector<BoardMove*>* out, Coordinates checkedLocation) {
		if (b->containsPiece(checkedLocation) &&
			b->getPiece(checkedLocation)->name == "empty") {
			BoardMove* m = new BoardMove("move", "Move to " + checkedLocation.toString());
			m->push_back(
				[location = new Coordinates(location), checkedLocation = new Coordinates(
					checkedLocation)](Board* b) {
						b->MovePiece(*location, *checkedLocation);
				});
			if (!checkPositionForPromotion(out, m, checkedLocation))
				out->push_back(m);

			checkedLocation += forward;

			if ((location.y == 2 && orientatedUp) || (location.y == 7 && !orientatedUp) &&
				b->containsPiece(checkedLocation) &&
				b->getPiece(checkedLocation)->name == "empty") {

				BoardMove* m = new BoardMove("move", "Move to " + checkedLocation.toString());
				m->push_back(
					[location = new Coordinates(location), checkedLocation = new Coordinates(
						checkedLocation)](Board* b) {
							b->getPiece(*location)->addTag("En Pessant possible");
							b->MovePiece(*location, *checkedLocation);
					});
				if (!checkPositionForPromotion(out, m, checkedLocation))
					out->push_back(m);

			}
		}
	}

	void checkForMove(std::vector<BoardMove*>* out) {
		Coordinates checkedLocation = location;

		checkedLocation += forward;
		checkPositionForMoveForward(out, checkedLocation);
	}

	void checkPositionForEnPessantAttack(std::vector<BoardMove*>* out, Coordinates enemyPosition, Coordinates emptyPosition) {
		if (b->containsPiece(enemyPosition) &&
			b->getPiece(enemyPosition)->name != "empty" &&
			b->getPiece(enemyPosition)->loyalty != loyalty &&
			b->getPiece(enemyPosition)->hasTag("En Pessant possible") &&
			b->containsPiece(emptyPosition) &&
			b->getPiece(emptyPosition)->name == "empty"
			) {
			checkChecking(enemyPosition);
			BoardMove* m = new BoardMove("attack", "Attack " + b->getPiece(enemyPosition)->toString());
			m->push_back([location = new Coordinates(location), enemyPosition = new Coordinates(
				enemyPosition), emptyPosition = new Coordinates(emptyPosition)](Board* b) {
					b->RemovePiece(*enemyPosition);
					b->MovePiece(*location, *emptyPosition);
				});
			if (!checkPositionForPromotion(out, m, emptyPosition)) {
				out->push_back(m);
			}
		}
	}

	bool checkPositionForPromotion(std::vector<BoardMove*>* out, BoardMove* oldMove, Coordinates checkedLocation) {
		if ((checkedLocation.y == 8 && orientatedUp) || (checkedLocation.y == 1 && !orientatedUp)) {
			BoardMove* m;

			m = new BoardMove(*oldMove);
			m->addDescription(" and promote to Queen");
			m->push_back([location = new Coordinates(location), checkedLocation = new Coordinates(
				checkedLocation)](Board* b) {
					Piece* oldPiece = b->getPiece(*checkedLocation);
					b->RemovePiece(*checkedLocation);
					b->PlacePiece(new Queen(b, oldPiece->loyalty), *checkedLocation);
				});
			out->push_back(m);

			m = new BoardMove(*oldMove);
			m->addDescription(" and promote to Rook");
			m->push_back([location = new Coordinates(location), checkedLocation = new Coordinates(
				checkedLocation)](Board* b) {
					Piece* oldPiece = b->getPiece(*checkedLocation);
					b->RemovePiece(*checkedLocation);
					b->PlacePiece(new Rook(b, oldPiece->loyalty), *checkedLocation);
				});
			out->push_back(m);

			m = new BoardMove(*oldMove);
			m->addDescription(" and promote to Bishop");
			m->push_back([location = new Coordinates(location), checkedLocation = new Coordinates(
				checkedLocation)](Board* b) {
					Piece* oldPiece = b->getPiece(*checkedLocation);
					b->RemovePiece(*checkedLocation);
					b->PlacePiece(new Bishop(b, oldPiece->loyalty), *checkedLocation);
				});
			out->push_back(m);

			m = new BoardMove(*oldMove);
			m->addDescription(" and promote to Knight");
			m->push_back([location = new Coordinates(location), checkedLocation = new Coordinates(
				checkedLocation)](Board* b) {
					Piece* oldPiece = b->getPiece(*checkedLocation);
					b->RemovePiece(*checkedLocation);
					b->PlacePiece(new Knight(b, oldPiece->loyalty), *checkedLocation);
				});
			out->push_back(m);
			return true;
		}
		else {
			return false;
		}
	}

	void checkPositionForCapture(std::vector<BoardMove*>* out, Coordinates checkedLocation) {
		if (b->containsPiece(checkedLocation) &&
			b->getPiece(checkedLocation)->name != "empty" &&
			b->getPiece(checkedLocation)->loyalty != loyalty) {
			checkChecking(checkedLocation);
			BoardMove* m = new BoardMove("attack", "Attack " + b->getPiece(checkedLocation)->toString());
			m->push_back(
				[location = new Coordinates(location), checkedLocation = new Coordinates(checkedLocation)](Board* b) {
					b->RemovePiece(*checkedLocation);
					b->MovePiece(*location, *checkedLocation);
				});
			if (!checkPositionForPromotion(out, m, checkedLocation))
				out->push_back(m);
		}
	}

	void checkForCapture(std::vector<BoardMove*>* out) {
		Coordinates checkedLocation = location;

		checkPositionForEnPessantAttack(out, checkedLocation.right(), checkedLocation.right() + forward);
		checkPositionForEnPessantAttack(out, checkedLocation.left(), checkedLocation.left() + forward);

		checkedLocation += forward;
		checkPositionForCapture(out, checkedLocation.right());
		checkPositionForCapture(out, checkedLocation.left());

	}
	void checkChecking(Coordinates checkedLocation) {
		if (b->containsPiece(checkedLocation) &&
			b->getPiece(checkedLocation)->loyalty != this->loyalty &&
			b->getPiece(checkedLocation)->name == "King") {
			addTag("checking");
		}
	}
};

#endif