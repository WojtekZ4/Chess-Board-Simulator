#pragma once
#include "Piece.cpp"
#include "BoardMove.cpp"

public ref class SpecialButton : public System::Windows::Forms::Button {
public:
	BoardMove* m;
	Piece* p;
};