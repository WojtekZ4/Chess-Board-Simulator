#pragma once
#include "Piece.cpp"
#include "BoardMove.cpp"

public ref class SpecialButton : public System::Windows::Forms::Button {
public:
	BoardMove* m;
	Piece* p;
	SpecialButton():Button(){
		this->Size = System::Drawing::Size(260, 50);
		this->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 12);
	}
};