#pragma once

#include "Game.cpp"
public ref class GameButton : public System::Windows::Forms::Button {
public:
	Game* g;
	GameButton() : Button() {
		this->Size = System::Drawing::Size(260, 50);
		this->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 12);
	}
};