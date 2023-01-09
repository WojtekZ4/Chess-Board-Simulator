
#include <iostream>
#include "Checkers.cpp"
#include "Chess.cpp"
#include "BoardMove.cpp"

#include "MainForm.h"
using namespace System;
using namespace System::Windows::Forms;
[STAThread]

int main() {
	std::list<Game*> allGames = {new Chess(),new Checkers()};
	//g->RunGame();
	System::Windows::Forms::Application::EnableVisualStyles();
	System::Windows::Forms::Application::SetCompatibleTextRenderingDefault(false);
	ChessBoardSimulator::MainForm form(allGames);
	System::Windows::Forms::Application::Run(% form);
	System::Windows::Forms::Application::Exit();
	return 0;
}
