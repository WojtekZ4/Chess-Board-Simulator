#pragma once

#include "Piece.cpp"
#include "BoardMove.cpp"
#include "Game.cpp"
#include "Coordinates.cpp"
#include "SpecialButton.h"

#include <stdlib.h>
#include <string.h>
#include <msclr\marshal.h>

namespace ChessBoardSimulator {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace msclr::interop;

	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		Game* g;

		MainForm(Game* ggg)
		{
			InitializeComponent();

			this->g = ggg;
			//pictureBox14->Load("../Resources/Chess Black Knight Transparent.jpg");
			RefreshBoardState();

		}

		void RefreshBoardState() {
			for (auto cc : g->gameboard->bo) {
				Coordinates c = Coordinates(cc.first);

				auto o = (PictureBox^)DBoard->GetControlFromPosition(c.x() - 1, 7 - (c.y() - 1));
				String^ message = gcnew String(cc.second->icon.c_str());
				o->Load(message);
			}
			const char* message = g->activePlayer->name.c_str();
			String^ result = marshal_as<String^>(message);
			ActivePlayerName->Text = result;
			DisplayPieces();
		}
		void UpdateMoves() {
			g->CalculateAllPosibleMoves(g->activePlayer);
		}


		void DisplayPieces() {
			interactionPanel->Controls->Clear();
			label82->Text = "Select piece:";
			auto ff = g->rememberedMovesMap;
			for (auto rr : ff) {
				SpecialButton^ b = gcnew SpecialButton;
				String^ message = gcnew String(rr.first->toString().c_str());
				b->Text = message;
				b->p = rr.first;
				b->Click += gcnew System::EventHandler(this, &MainForm::pieceButton_Click);
				interactionPanel->Controls->Add(b);
			}
		}

		void DisplayMoves(Piece* toMove, std::set< BoardMove*> rrr) {
			interactionPanel->Controls->Clear();
			String^ message = gcnew String(toMove->toString().c_str());
			label82->Text = "Select moves for " + message + ":";
			backButton->Visible = true;
			for (auto rr : rrr) {
				SpecialButton^ b = (gcnew SpecialButton());
				String^ message = gcnew String(rr->toString().c_str());
				b->Text = message;
				b->m = rr;
				b->Click += gcnew System::EventHandler(this, &MainForm::moveButton_Click);
				interactionPanel->Controls->Add(b);
			}
		}
		void ProcesSelectedMove(BoardMove* f) {

			//g->MakeMove(m);
		}


	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Void pieceButton_Click(System::Object^ sender, System::EventArgs^ e) {
		SpecialButton^ btn = (SpecialButton^)sender;
		auto ff = g->rememberedMovesMap;
		Piece* pp = btn->p;
		DisplayMoves(pp, ff[pp]);
	}
	private: System::Void moveButton_Click(System::Object^ sender, System::EventArgs^ e) {
		SpecialButton^ btn = (SpecialButton^)sender;
		BoardMove* mm = btn->m;
		g->ExecuteMove(mm);
		backButton->Visible = false;
		RefreshBoardState();

	}
	private: System::Void backButton_Click(System::Object^ sender, System::EventArgs^ e) {
		Button^ btn = (Button^)sender;
		DisplayPieces();
		btn->Visible = false;
	}
	private: System::Windows::Forms::FlowLayoutPanel^ interactionPanel;
	protected:

	private: System::Windows::Forms::Label^ label65;

	private: System::Windows::Forms::TableLayoutPanel^ DBoard;

































































	private: System::Windows::Forms::Label^ ActivePlayerName;

	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Button^ button5;
	private: System::Windows::Forms::Button^ button6;
	private: System::Windows::Forms::Button^ backButton;
	private: System::Windows::Forms::Label^ label66;

	private: System::Windows::Forms::Label^ label68;
	private: System::Windows::Forms::Label^ label69;
	private: System::Windows::Forms::Label^ label70;
	private: System::Windows::Forms::Label^ label71;
	private: System::Windows::Forms::Label^ label67;
	private: System::Windows::Forms::Label^ label72;
	private: System::Windows::Forms::Label^ label73;
	private: System::Windows::Forms::Label^ label74;
	private: System::Windows::Forms::Label^ label75;
	private: System::Windows::Forms::Label^ label76;
	private: System::Windows::Forms::Label^ label77;
	private: System::Windows::Forms::Label^ label78;
	private: System::Windows::Forms::Label^ label79;
	private: System::Windows::Forms::Label^ label80;
	private: System::Windows::Forms::Label^ label81;
	private: System::Windows::Forms::Label^ label82;
	private: System::Windows::Forms::Button^ button7;
	private: System::Windows::Forms::Button^ button8;
	private: System::Windows::Forms::Button^ button9;
	private: System::Windows::Forms::Button^ button10;
	private: System::Windows::Forms::Button^ button11;
	private: System::Windows::Forms::Button^ button12;
	private: System::Windows::Forms::Button^ button13;




	private: System::Windows::Forms::Button^ button14;
	private: System::Windows::Forms::Button^ button15;
	private: System::Windows::Forms::Button^ button16;
	private: System::Windows::Forms::Button^ button17;
	private: System::Windows::Forms::Button^ button18;



















	private: System::Windows::Forms::PictureBox^ pictureBox78;
	private: System::Windows::Forms::PictureBox^ pictureBox77;
	private: System::Windows::Forms::PictureBox^ pictureBox76;
	private: System::Windows::Forms::PictureBox^ pictureBox75;
	private: System::Windows::Forms::PictureBox^ pictureBox74;
	private: System::Windows::Forms::PictureBox^ pictureBox73;
	private: System::Windows::Forms::PictureBox^ pictureBox72;
	private: System::Windows::Forms::PictureBox^ pictureBox71;
	private: System::Windows::Forms::PictureBox^ pictureBox70;
	private: System::Windows::Forms::PictureBox^ pictureBox69;
	private: System::Windows::Forms::PictureBox^ pictureBox68;
	private: System::Windows::Forms::PictureBox^ pictureBox67;
	private: System::Windows::Forms::PictureBox^ pictureBox66;
	private: System::Windows::Forms::PictureBox^ pictureBox65;
	private: System::Windows::Forms::PictureBox^ pictureBox64;
	private: System::Windows::Forms::PictureBox^ pictureBox63;
	private: System::Windows::Forms::PictureBox^ pictureBox62;
	private: System::Windows::Forms::PictureBox^ pictureBox61;
	private: System::Windows::Forms::PictureBox^ pictureBox60;
	private: System::Windows::Forms::PictureBox^ pictureBox59;
	private: System::Windows::Forms::PictureBox^ pictureBox58;
	private: System::Windows::Forms::PictureBox^ pictureBox57;
	private: System::Windows::Forms::PictureBox^ pictureBox56;
	private: System::Windows::Forms::PictureBox^ pictureBox55;
	private: System::Windows::Forms::PictureBox^ pictureBox54;
	private: System::Windows::Forms::PictureBox^ pictureBox53;
	private: System::Windows::Forms::PictureBox^ pictureBox52;
	private: System::Windows::Forms::PictureBox^ pictureBox51;
	private: System::Windows::Forms::PictureBox^ pictureBox50;
	private: System::Windows::Forms::PictureBox^ pictureBox49;
	private: System::Windows::Forms::PictureBox^ pictureBox48;
	private: System::Windows::Forms::PictureBox^ pictureBox47;
	private: System::Windows::Forms::PictureBox^ pictureBox46;
	private: System::Windows::Forms::PictureBox^ pictureBox45;
	private: System::Windows::Forms::PictureBox^ pictureBox44;
	private: System::Windows::Forms::PictureBox^ pictureBox43;
	private: System::Windows::Forms::PictureBox^ pictureBox42;
	private: System::Windows::Forms::PictureBox^ pictureBox41;
	private: System::Windows::Forms::PictureBox^ pictureBox40;
	private: System::Windows::Forms::PictureBox^ pictureBox39;
	private: System::Windows::Forms::PictureBox^ pictureBox38;
	private: System::Windows::Forms::PictureBox^ pictureBox37;
	private: System::Windows::Forms::PictureBox^ pictureBox36;
	private: System::Windows::Forms::PictureBox^ pictureBox35;
	private: System::Windows::Forms::PictureBox^ pictureBox34;
	private: System::Windows::Forms::PictureBox^ pictureBox33;
	private: System::Windows::Forms::PictureBox^ pictureBox32;
	private: System::Windows::Forms::PictureBox^ pictureBox31;
	private: System::Windows::Forms::PictureBox^ pictureBox30;
	private: System::Windows::Forms::PictureBox^ pictureBox29;
	private: System::Windows::Forms::PictureBox^ pictureBox28;
	private: System::Windows::Forms::PictureBox^ pictureBox27;
	private: System::Windows::Forms::PictureBox^ pictureBox26;
	private: System::Windows::Forms::PictureBox^ pictureBox25;
	private: System::Windows::Forms::PictureBox^ pictureBox24;
	private: System::Windows::Forms::PictureBox^ pictureBox23;
	private: System::Windows::Forms::PictureBox^ pictureBox22;
	private: System::Windows::Forms::PictureBox^ pictureBox21;
	private: System::Windows::Forms::PictureBox^ pictureBox20;
	private: System::Windows::Forms::PictureBox^ pictureBox19;
	private: System::Windows::Forms::PictureBox^ pictureBox18;
	private: System::Windows::Forms::PictureBox^ pictureBox17;
	private: System::Windows::Forms::PictureBox^ pictureBox16;
	private: System::Windows::Forms::PictureBox^ pictureBox15;








































































	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->interactionPanel = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->button11 = (gcnew System::Windows::Forms::Button());
			this->button12 = (gcnew System::Windows::Forms::Button());
			this->button13 = (gcnew System::Windows::Forms::Button());
			this->button14 = (gcnew System::Windows::Forms::Button());
			this->button15 = (gcnew System::Windows::Forms::Button());
			this->button16 = (gcnew System::Windows::Forms::Button());
			this->button17 = (gcnew System::Windows::Forms::Button());
			this->button18 = (gcnew System::Windows::Forms::Button());
			this->label65 = (gcnew System::Windows::Forms::Label());
			this->DBoard = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->pictureBox78 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox77 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox76 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox75 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox74 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox73 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox72 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox71 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox70 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox69 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox68 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox67 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox66 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox65 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox64 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox63 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox62 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox61 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox60 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox59 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox58 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox57 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox56 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox55 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox54 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox53 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox52 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox51 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox50 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox49 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox48 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox47 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox46 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox45 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox44 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox43 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox42 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox41 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox40 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox39 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox38 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox37 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox36 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox35 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox34 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox33 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox32 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox31 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox30 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox29 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox28 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox27 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox26 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox25 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox24 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox23 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox22 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox21 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox20 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox19 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox18 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox17 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox16 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox15 = (gcnew System::Windows::Forms::PictureBox());
			this->ActivePlayerName = (gcnew System::Windows::Forms::Label());
			this->backButton = (gcnew System::Windows::Forms::Button());
			this->label66 = (gcnew System::Windows::Forms::Label());
			this->label68 = (gcnew System::Windows::Forms::Label());
			this->label69 = (gcnew System::Windows::Forms::Label());
			this->label70 = (gcnew System::Windows::Forms::Label());
			this->label71 = (gcnew System::Windows::Forms::Label());
			this->label67 = (gcnew System::Windows::Forms::Label());
			this->label72 = (gcnew System::Windows::Forms::Label());
			this->label73 = (gcnew System::Windows::Forms::Label());
			this->label74 = (gcnew System::Windows::Forms::Label());
			this->label75 = (gcnew System::Windows::Forms::Label());
			this->label76 = (gcnew System::Windows::Forms::Label());
			this->label77 = (gcnew System::Windows::Forms::Label());
			this->label78 = (gcnew System::Windows::Forms::Label());
			this->label79 = (gcnew System::Windows::Forms::Label());
			this->label80 = (gcnew System::Windows::Forms::Label());
			this->label81 = (gcnew System::Windows::Forms::Label());
			this->label82 = (gcnew System::Windows::Forms::Label());
			this->interactionPanel->SuspendLayout();
			this->DBoard->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox78))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox77))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox76))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox75))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox74))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox73))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox72))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox71))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox70))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox69))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox68))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox67))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox66))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox65))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox64))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox63))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox62))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox61))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox60))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox59))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox58))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox57))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox56))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox55))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox54))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox53))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox52))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox51))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox50))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox49))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox48))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox47))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox46))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox45))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox44))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox43))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox42))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox41))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox40))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox39))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox38))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox37))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox36))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox35))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox34))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox33))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox32))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox31))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox30))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox29))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox28))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox27))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox26))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox25))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox24))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox23))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox22))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox21))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox20))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox19))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox18))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox17))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox16))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox15))->BeginInit();
			this->SuspendLayout();
			// 
			// interactionPanel
			// 
			this->interactionPanel->AutoScroll = true;
			this->interactionPanel->Controls->Add(this->button1);
			this->interactionPanel->Controls->Add(this->button2);
			this->interactionPanel->Controls->Add(this->button3);
			this->interactionPanel->Controls->Add(this->button4);
			this->interactionPanel->Controls->Add(this->button5);
			this->interactionPanel->Controls->Add(this->button6);
			this->interactionPanel->Controls->Add(this->button7);
			this->interactionPanel->Controls->Add(this->button8);
			this->interactionPanel->Controls->Add(this->button9);
			this->interactionPanel->Controls->Add(this->button10);
			this->interactionPanel->Controls->Add(this->button11);
			this->interactionPanel->Controls->Add(this->button12);
			this->interactionPanel->Controls->Add(this->button13);
			this->interactionPanel->Controls->Add(this->button14);
			this->interactionPanel->Controls->Add(this->button15);
			this->interactionPanel->Controls->Add(this->button16);
			this->interactionPanel->Controls->Add(this->button17);
			this->interactionPanel->Controls->Add(this->button18);
			this->interactionPanel->Location = System::Drawing::Point(601, 91);
			this->interactionPanel->Name = L"interactionPanel";
			this->interactionPanel->Size = System::Drawing::Size(151, 435);
			this->interactionPanel->TabIndex = 3;
			this->interactionPanel->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainForm::flowLayoutPanel1_Paint);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(3, 3);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = true;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(3, 32);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 1;
			this->button2->Text = L"button2";
			this->button2->UseVisualStyleBackColor = true;
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(3, 61);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 23);
			this->button3->TabIndex = 2;
			this->button3->Text = L"button3";
			this->button3->UseVisualStyleBackColor = true;
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(3, 90);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(75, 23);
			this->button4->TabIndex = 3;
			this->button4->Text = L"button4";
			this->button4->UseVisualStyleBackColor = true;
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(3, 119);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(75, 23);
			this->button5->TabIndex = 4;
			this->button5->Text = L"button5";
			this->button5->UseVisualStyleBackColor = true;
			// 
			// button6
			// 
			this->button6->Location = System::Drawing::Point(3, 148);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(75, 23);
			this->button6->TabIndex = 5;
			this->button6->Text = L"button6";
			this->button6->UseVisualStyleBackColor = true;
			// 
			// button7
			// 
			this->button7->Location = System::Drawing::Point(3, 177);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(75, 23);
			this->button7->TabIndex = 6;
			this->button7->Text = L"button7";
			this->button7->UseVisualStyleBackColor = true;
			// 
			// button8
			// 
			this->button8->Location = System::Drawing::Point(3, 206);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(75, 23);
			this->button8->TabIndex = 7;
			this->button8->Text = L"button8";
			this->button8->UseVisualStyleBackColor = true;
			// 
			// button9
			// 
			this->button9->Location = System::Drawing::Point(3, 235);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(75, 23);
			this->button9->TabIndex = 8;
			this->button9->Text = L"button9";
			this->button9->UseVisualStyleBackColor = true;
			// 
			// button10
			// 
			this->button10->Location = System::Drawing::Point(3, 264);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(75, 23);
			this->button10->TabIndex = 9;
			this->button10->Text = L"button10";
			this->button10->UseVisualStyleBackColor = true;
			// 
			// button11
			// 
			this->button11->Location = System::Drawing::Point(3, 293);
			this->button11->Name = L"button11";
			this->button11->Size = System::Drawing::Size(75, 23);
			this->button11->TabIndex = 10;
			this->button11->Text = L"button11";
			this->button11->UseVisualStyleBackColor = true;
			// 
			// button12
			// 
			this->button12->Location = System::Drawing::Point(3, 322);
			this->button12->Name = L"button12";
			this->button12->Size = System::Drawing::Size(75, 23);
			this->button12->TabIndex = 11;
			this->button12->Text = L"button12";
			this->button12->UseVisualStyleBackColor = true;
			// 
			// button13
			// 
			this->button13->Location = System::Drawing::Point(3, 351);
			this->button13->Name = L"button13";
			this->button13->Size = System::Drawing::Size(75, 23);
			this->button13->TabIndex = 12;
			this->button13->Text = L"button13";
			this->button13->UseVisualStyleBackColor = true;
			// 
			// button14
			// 
			this->button14->Location = System::Drawing::Point(3, 380);
			this->button14->Name = L"button14";
			this->button14->Size = System::Drawing::Size(75, 23);
			this->button14->TabIndex = 13;
			this->button14->Text = L"button14";
			this->button14->UseVisualStyleBackColor = true;
			// 
			// button15
			// 
			this->button15->Location = System::Drawing::Point(3, 409);
			this->button15->Name = L"button15";
			this->button15->Size = System::Drawing::Size(75, 23);
			this->button15->TabIndex = 14;
			this->button15->Text = L"button15";
			this->button15->UseVisualStyleBackColor = true;
			// 
			// button16
			// 
			this->button16->Location = System::Drawing::Point(3, 438);
			this->button16->Name = L"button16";
			this->button16->Size = System::Drawing::Size(75, 23);
			this->button16->TabIndex = 15;
			this->button16->Text = L"button16";
			this->button16->UseVisualStyleBackColor = true;
			// 
			// button17
			// 
			this->button17->Location = System::Drawing::Point(3, 467);
			this->button17->Name = L"button17";
			this->button17->Size = System::Drawing::Size(75, 23);
			this->button17->TabIndex = 16;
			this->button17->Text = L"button17";
			this->button17->UseVisualStyleBackColor = true;
			// 
			// button18
			// 
			this->button18->Location = System::Drawing::Point(3, 496);
			this->button18->Name = L"button18";
			this->button18->Size = System::Drawing::Size(75, 23);
			this->button18->TabIndex = 17;
			this->button18->Text = L"button18";
			this->button18->UseVisualStyleBackColor = true;
			// 
			// label65
			// 
			this->label65->AutoSize = true;
			this->label65->Location = System::Drawing::Point(598, 9);
			this->label65->Name = L"label65";
			this->label65->Size = System::Drawing::Size(81, 16);
			this->label65->TabIndex = 66;
			this->label65->Text = L"Active Plyer:";
			this->label65->Click += gcnew System::EventHandler(this, &MainForm::label65_Click);
			// 
			// DBoard
			// 
			this->DBoard->ColumnCount = 8;
			this->DBoard->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 12.5F)));
			this->DBoard->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 12.5F)));
			this->DBoard->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 12.5F)));
			this->DBoard->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 12.5F)));
			this->DBoard->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 12.5F)));
			this->DBoard->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 12.5F)));
			this->DBoard->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 12.5F)));
			this->DBoard->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 12.5F)));
			this->DBoard->Controls->Add(this->pictureBox78, 7, 7);
			this->DBoard->Controls->Add(this->pictureBox77, 6, 7);
			this->DBoard->Controls->Add(this->pictureBox76, 5, 7);
			this->DBoard->Controls->Add(this->pictureBox75, 4, 7);
			this->DBoard->Controls->Add(this->pictureBox74, 3, 7);
			this->DBoard->Controls->Add(this->pictureBox73, 2, 7);
			this->DBoard->Controls->Add(this->pictureBox72, 1, 7);
			this->DBoard->Controls->Add(this->pictureBox71, 0, 7);
			this->DBoard->Controls->Add(this->pictureBox70, 7, 6);
			this->DBoard->Controls->Add(this->pictureBox69, 6, 6);
			this->DBoard->Controls->Add(this->pictureBox68, 5, 6);
			this->DBoard->Controls->Add(this->pictureBox67, 4, 6);
			this->DBoard->Controls->Add(this->pictureBox66, 3, 6);
			this->DBoard->Controls->Add(this->pictureBox65, 2, 6);
			this->DBoard->Controls->Add(this->pictureBox64, 1, 6);
			this->DBoard->Controls->Add(this->pictureBox63, 0, 6);
			this->DBoard->Controls->Add(this->pictureBox62, 7, 5);
			this->DBoard->Controls->Add(this->pictureBox61, 6, 5);
			this->DBoard->Controls->Add(this->pictureBox60, 5, 5);
			this->DBoard->Controls->Add(this->pictureBox59, 4, 5);
			this->DBoard->Controls->Add(this->pictureBox58, 3, 5);
			this->DBoard->Controls->Add(this->pictureBox57, 2, 5);
			this->DBoard->Controls->Add(this->pictureBox56, 1, 5);
			this->DBoard->Controls->Add(this->pictureBox55, 0, 5);
			this->DBoard->Controls->Add(this->pictureBox54, 7, 4);
			this->DBoard->Controls->Add(this->pictureBox53, 6, 4);
			this->DBoard->Controls->Add(this->pictureBox52, 5, 4);
			this->DBoard->Controls->Add(this->pictureBox51, 4, 4);
			this->DBoard->Controls->Add(this->pictureBox50, 3, 4);
			this->DBoard->Controls->Add(this->pictureBox49, 2, 4);
			this->DBoard->Controls->Add(this->pictureBox48, 1, 4);
			this->DBoard->Controls->Add(this->pictureBox47, 0, 4);
			this->DBoard->Controls->Add(this->pictureBox46, 7, 3);
			this->DBoard->Controls->Add(this->pictureBox45, 6, 3);
			this->DBoard->Controls->Add(this->pictureBox44, 5, 3);
			this->DBoard->Controls->Add(this->pictureBox43, 4, 3);
			this->DBoard->Controls->Add(this->pictureBox42, 3, 3);
			this->DBoard->Controls->Add(this->pictureBox41, 2, 3);
			this->DBoard->Controls->Add(this->pictureBox40, 1, 3);
			this->DBoard->Controls->Add(this->pictureBox39, 0, 3);
			this->DBoard->Controls->Add(this->pictureBox38, 7, 2);
			this->DBoard->Controls->Add(this->pictureBox37, 6, 2);
			this->DBoard->Controls->Add(this->pictureBox36, 5, 2);
			this->DBoard->Controls->Add(this->pictureBox35, 4, 2);
			this->DBoard->Controls->Add(this->pictureBox34, 3, 2);
			this->DBoard->Controls->Add(this->pictureBox33, 2, 2);
			this->DBoard->Controls->Add(this->pictureBox32, 1, 2);
			this->DBoard->Controls->Add(this->pictureBox31, 0, 2);
			this->DBoard->Controls->Add(this->pictureBox30, 7, 1);
			this->DBoard->Controls->Add(this->pictureBox29, 6, 1);
			this->DBoard->Controls->Add(this->pictureBox28, 5, 1);
			this->DBoard->Controls->Add(this->pictureBox27, 4, 1);
			this->DBoard->Controls->Add(this->pictureBox26, 3, 1);
			this->DBoard->Controls->Add(this->pictureBox25, 2, 1);
			this->DBoard->Controls->Add(this->pictureBox24, 1, 1);
			this->DBoard->Controls->Add(this->pictureBox23, 0, 1);
			this->DBoard->Controls->Add(this->pictureBox22, 7, 0);
			this->DBoard->Controls->Add(this->pictureBox21, 6, 0);
			this->DBoard->Controls->Add(this->pictureBox20, 5, 0);
			this->DBoard->Controls->Add(this->pictureBox19, 4, 0);
			this->DBoard->Controls->Add(this->pictureBox18, 3, 0);
			this->DBoard->Controls->Add(this->pictureBox17, 2, 0);
			this->DBoard->Controls->Add(this->pictureBox16, 1, 0);
			this->DBoard->Controls->Add(this->pictureBox15, 0, 0);
			this->DBoard->Location = System::Drawing::Point(58, 43);
			this->DBoard->Name = L"DBoard";
			this->DBoard->RowCount = 8;
			this->DBoard->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 12.5F)));
			this->DBoard->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 12.5F)));
			this->DBoard->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 12.5F)));
			this->DBoard->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 12.5F)));
			this->DBoard->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 12.5F)));
			this->DBoard->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 12.5F)));
			this->DBoard->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 12.5F)));
			this->DBoard->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 12.5F)));
			this->DBoard->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->DBoard->Size = System::Drawing::Size(512, 512);
			this->DBoard->TabIndex = 68;
			// 
			// pictureBox78
			// 
			this->pictureBox78->BackColor = System::Drawing::Color::MistyRose;
			this->pictureBox78->Location = System::Drawing::Point(448, 448);
			this->pictureBox78->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox78->Name = L"pictureBox78";
			this->pictureBox78->Size = System::Drawing::Size(64, 64);
			this->pictureBox78->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox78->TabIndex = 63;
			this->pictureBox78->TabStop = false;
			// 
			// pictureBox77
			// 
			this->pictureBox77->BackColor = System::Drawing::Color::Brown;
			this->pictureBox77->Location = System::Drawing::Point(384, 448);
			this->pictureBox77->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox77->Name = L"pictureBox77";
			this->pictureBox77->Size = System::Drawing::Size(64, 64);
			this->pictureBox77->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox77->TabIndex = 62;
			this->pictureBox77->TabStop = false;
			// 
			// pictureBox76
			// 
			this->pictureBox76->BackColor = System::Drawing::Color::MistyRose;
			this->pictureBox76->Location = System::Drawing::Point(320, 448);
			this->pictureBox76->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox76->Name = L"pictureBox76";
			this->pictureBox76->Size = System::Drawing::Size(64, 64);
			this->pictureBox76->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox76->TabIndex = 61;
			this->pictureBox76->TabStop = false;
			// 
			// pictureBox75
			// 
			this->pictureBox75->BackColor = System::Drawing::Color::Brown;
			this->pictureBox75->Location = System::Drawing::Point(256, 448);
			this->pictureBox75->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox75->Name = L"pictureBox75";
			this->pictureBox75->Size = System::Drawing::Size(64, 64);
			this->pictureBox75->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox75->TabIndex = 60;
			this->pictureBox75->TabStop = false;
			// 
			// pictureBox74
			// 
			this->pictureBox74->BackColor = System::Drawing::Color::MistyRose;
			this->pictureBox74->Location = System::Drawing::Point(192, 448);
			this->pictureBox74->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox74->Name = L"pictureBox74";
			this->pictureBox74->Size = System::Drawing::Size(64, 64);
			this->pictureBox74->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox74->TabIndex = 59;
			this->pictureBox74->TabStop = false;
			// 
			// pictureBox73
			// 
			this->pictureBox73->BackColor = System::Drawing::Color::Brown;
			this->pictureBox73->Location = System::Drawing::Point(128, 448);
			this->pictureBox73->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox73->Name = L"pictureBox73";
			this->pictureBox73->Size = System::Drawing::Size(64, 64);
			this->pictureBox73->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox73->TabIndex = 58;
			this->pictureBox73->TabStop = false;
			// 
			// pictureBox72
			// 
			this->pictureBox72->BackColor = System::Drawing::Color::MistyRose;
			this->pictureBox72->Location = System::Drawing::Point(64, 448);
			this->pictureBox72->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox72->Name = L"pictureBox72";
			this->pictureBox72->Size = System::Drawing::Size(64, 64);
			this->pictureBox72->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox72->TabIndex = 57;
			this->pictureBox72->TabStop = false;
			// 
			// pictureBox71
			// 
			this->pictureBox71->BackColor = System::Drawing::Color::Brown;
			this->pictureBox71->Location = System::Drawing::Point(0, 448);
			this->pictureBox71->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox71->Name = L"pictureBox71";
			this->pictureBox71->Size = System::Drawing::Size(64, 64);
			this->pictureBox71->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox71->TabIndex = 56;
			this->pictureBox71->TabStop = false;
			// 
			// pictureBox70
			// 
			this->pictureBox70->BackColor = System::Drawing::Color::Brown;
			this->pictureBox70->Location = System::Drawing::Point(448, 384);
			this->pictureBox70->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox70->Name = L"pictureBox70";
			this->pictureBox70->Size = System::Drawing::Size(64, 64);
			this->pictureBox70->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox70->TabIndex = 55;
			this->pictureBox70->TabStop = false;
			// 
			// pictureBox69
			// 
			this->pictureBox69->BackColor = System::Drawing::Color::MistyRose;
			this->pictureBox69->Location = System::Drawing::Point(384, 384);
			this->pictureBox69->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox69->Name = L"pictureBox69";
			this->pictureBox69->Size = System::Drawing::Size(64, 64);
			this->pictureBox69->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox69->TabIndex = 54;
			this->pictureBox69->TabStop = false;
			// 
			// pictureBox68
			// 
			this->pictureBox68->BackColor = System::Drawing::Color::Brown;
			this->pictureBox68->Location = System::Drawing::Point(320, 384);
			this->pictureBox68->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox68->Name = L"pictureBox68";
			this->pictureBox68->Size = System::Drawing::Size(64, 64);
			this->pictureBox68->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox68->TabIndex = 53;
			this->pictureBox68->TabStop = false;
			// 
			// pictureBox67
			// 
			this->pictureBox67->BackColor = System::Drawing::Color::MistyRose;
			this->pictureBox67->Location = System::Drawing::Point(256, 384);
			this->pictureBox67->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox67->Name = L"pictureBox67";
			this->pictureBox67->Size = System::Drawing::Size(64, 64);
			this->pictureBox67->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox67->TabIndex = 52;
			this->pictureBox67->TabStop = false;
			// 
			// pictureBox66
			// 
			this->pictureBox66->BackColor = System::Drawing::Color::Brown;
			this->pictureBox66->Location = System::Drawing::Point(192, 384);
			this->pictureBox66->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox66->Name = L"pictureBox66";
			this->pictureBox66->Size = System::Drawing::Size(64, 64);
			this->pictureBox66->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox66->TabIndex = 51;
			this->pictureBox66->TabStop = false;
			// 
			// pictureBox65
			// 
			this->pictureBox65->BackColor = System::Drawing::Color::MistyRose;
			this->pictureBox65->Location = System::Drawing::Point(128, 384);
			this->pictureBox65->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox65->Name = L"pictureBox65";
			this->pictureBox65->Size = System::Drawing::Size(64, 64);
			this->pictureBox65->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox65->TabIndex = 50;
			this->pictureBox65->TabStop = false;
			// 
			// pictureBox64
			// 
			this->pictureBox64->BackColor = System::Drawing::Color::Brown;
			this->pictureBox64->Location = System::Drawing::Point(64, 384);
			this->pictureBox64->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox64->Name = L"pictureBox64";
			this->pictureBox64->Size = System::Drawing::Size(64, 64);
			this->pictureBox64->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox64->TabIndex = 49;
			this->pictureBox64->TabStop = false;
			// 
			// pictureBox63
			// 
			this->pictureBox63->BackColor = System::Drawing::Color::MistyRose;
			this->pictureBox63->Location = System::Drawing::Point(0, 384);
			this->pictureBox63->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox63->Name = L"pictureBox63";
			this->pictureBox63->Size = System::Drawing::Size(64, 64);
			this->pictureBox63->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox63->TabIndex = 48;
			this->pictureBox63->TabStop = false;
			// 
			// pictureBox62
			// 
			this->pictureBox62->BackColor = System::Drawing::Color::MistyRose;
			this->pictureBox62->Location = System::Drawing::Point(448, 320);
			this->pictureBox62->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox62->Name = L"pictureBox62";
			this->pictureBox62->Size = System::Drawing::Size(64, 64);
			this->pictureBox62->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox62->TabIndex = 47;
			this->pictureBox62->TabStop = false;
			// 
			// pictureBox61
			// 
			this->pictureBox61->BackColor = System::Drawing::Color::Brown;
			this->pictureBox61->Location = System::Drawing::Point(384, 320);
			this->pictureBox61->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox61->Name = L"pictureBox61";
			this->pictureBox61->Size = System::Drawing::Size(64, 64);
			this->pictureBox61->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox61->TabIndex = 46;
			this->pictureBox61->TabStop = false;
			// 
			// pictureBox60
			// 
			this->pictureBox60->BackColor = System::Drawing::Color::MistyRose;
			this->pictureBox60->Location = System::Drawing::Point(320, 320);
			this->pictureBox60->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox60->Name = L"pictureBox60";
			this->pictureBox60->Size = System::Drawing::Size(64, 64);
			this->pictureBox60->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox60->TabIndex = 45;
			this->pictureBox60->TabStop = false;
			// 
			// pictureBox59
			// 
			this->pictureBox59->BackColor = System::Drawing::Color::Brown;
			this->pictureBox59->Location = System::Drawing::Point(256, 320);
			this->pictureBox59->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox59->Name = L"pictureBox59";
			this->pictureBox59->Size = System::Drawing::Size(64, 64);
			this->pictureBox59->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox59->TabIndex = 44;
			this->pictureBox59->TabStop = false;
			// 
			// pictureBox58
			// 
			this->pictureBox58->BackColor = System::Drawing::Color::MistyRose;
			this->pictureBox58->Location = System::Drawing::Point(192, 320);
			this->pictureBox58->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox58->Name = L"pictureBox58";
			this->pictureBox58->Size = System::Drawing::Size(64, 64);
			this->pictureBox58->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox58->TabIndex = 43;
			this->pictureBox58->TabStop = false;
			// 
			// pictureBox57
			// 
			this->pictureBox57->BackColor = System::Drawing::Color::Brown;
			this->pictureBox57->Location = System::Drawing::Point(128, 320);
			this->pictureBox57->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox57->Name = L"pictureBox57";
			this->pictureBox57->Size = System::Drawing::Size(64, 64);
			this->pictureBox57->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox57->TabIndex = 42;
			this->pictureBox57->TabStop = false;
			// 
			// pictureBox56
			// 
			this->pictureBox56->BackColor = System::Drawing::Color::MistyRose;
			this->pictureBox56->Location = System::Drawing::Point(64, 320);
			this->pictureBox56->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox56->Name = L"pictureBox56";
			this->pictureBox56->Size = System::Drawing::Size(64, 64);
			this->pictureBox56->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox56->TabIndex = 41;
			this->pictureBox56->TabStop = false;
			// 
			// pictureBox55
			// 
			this->pictureBox55->BackColor = System::Drawing::Color::Brown;
			this->pictureBox55->Location = System::Drawing::Point(0, 320);
			this->pictureBox55->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox55->Name = L"pictureBox55";
			this->pictureBox55->Size = System::Drawing::Size(64, 64);
			this->pictureBox55->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox55->TabIndex = 40;
			this->pictureBox55->TabStop = false;
			// 
			// pictureBox54
			// 
			this->pictureBox54->BackColor = System::Drawing::Color::Brown;
			this->pictureBox54->Location = System::Drawing::Point(448, 256);
			this->pictureBox54->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox54->Name = L"pictureBox54";
			this->pictureBox54->Size = System::Drawing::Size(64, 64);
			this->pictureBox54->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox54->TabIndex = 39;
			this->pictureBox54->TabStop = false;
			// 
			// pictureBox53
			// 
			this->pictureBox53->BackColor = System::Drawing::Color::MistyRose;
			this->pictureBox53->Location = System::Drawing::Point(384, 256);
			this->pictureBox53->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox53->Name = L"pictureBox53";
			this->pictureBox53->Size = System::Drawing::Size(64, 64);
			this->pictureBox53->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox53->TabIndex = 38;
			this->pictureBox53->TabStop = false;
			// 
			// pictureBox52
			// 
			this->pictureBox52->BackColor = System::Drawing::Color::Brown;
			this->pictureBox52->Location = System::Drawing::Point(320, 256);
			this->pictureBox52->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox52->Name = L"pictureBox52";
			this->pictureBox52->Size = System::Drawing::Size(64, 64);
			this->pictureBox52->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox52->TabIndex = 37;
			this->pictureBox52->TabStop = false;
			// 
			// pictureBox51
			// 
			this->pictureBox51->BackColor = System::Drawing::Color::MistyRose;
			this->pictureBox51->Location = System::Drawing::Point(256, 256);
			this->pictureBox51->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox51->Name = L"pictureBox51";
			this->pictureBox51->Size = System::Drawing::Size(64, 64);
			this->pictureBox51->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox51->TabIndex = 36;
			this->pictureBox51->TabStop = false;
			// 
			// pictureBox50
			// 
			this->pictureBox50->BackColor = System::Drawing::Color::Brown;
			this->pictureBox50->Location = System::Drawing::Point(192, 256);
			this->pictureBox50->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox50->Name = L"pictureBox50";
			this->pictureBox50->Size = System::Drawing::Size(64, 64);
			this->pictureBox50->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox50->TabIndex = 35;
			this->pictureBox50->TabStop = false;
			// 
			// pictureBox49
			// 
			this->pictureBox49->BackColor = System::Drawing::Color::MistyRose;
			this->pictureBox49->Location = System::Drawing::Point(128, 256);
			this->pictureBox49->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox49->Name = L"pictureBox49";
			this->pictureBox49->Size = System::Drawing::Size(64, 64);
			this->pictureBox49->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox49->TabIndex = 34;
			this->pictureBox49->TabStop = false;
			// 
			// pictureBox48
			// 
			this->pictureBox48->BackColor = System::Drawing::Color::Brown;
			this->pictureBox48->Location = System::Drawing::Point(64, 256);
			this->pictureBox48->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox48->Name = L"pictureBox48";
			this->pictureBox48->Size = System::Drawing::Size(64, 64);
			this->pictureBox48->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox48->TabIndex = 33;
			this->pictureBox48->TabStop = false;
			// 
			// pictureBox47
			// 
			this->pictureBox47->BackColor = System::Drawing::Color::MistyRose;
			this->pictureBox47->Location = System::Drawing::Point(0, 256);
			this->pictureBox47->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox47->Name = L"pictureBox47";
			this->pictureBox47->Size = System::Drawing::Size(64, 64);
			this->pictureBox47->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox47->TabIndex = 32;
			this->pictureBox47->TabStop = false;
			// 
			// pictureBox46
			// 
			this->pictureBox46->BackColor = System::Drawing::Color::MistyRose;
			this->pictureBox46->Location = System::Drawing::Point(448, 192);
			this->pictureBox46->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox46->Name = L"pictureBox46";
			this->pictureBox46->Size = System::Drawing::Size(64, 64);
			this->pictureBox46->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox46->TabIndex = 31;
			this->pictureBox46->TabStop = false;
			// 
			// pictureBox45
			// 
			this->pictureBox45->BackColor = System::Drawing::Color::Brown;
			this->pictureBox45->Location = System::Drawing::Point(384, 192);
			this->pictureBox45->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox45->Name = L"pictureBox45";
			this->pictureBox45->Size = System::Drawing::Size(64, 64);
			this->pictureBox45->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox45->TabIndex = 30;
			this->pictureBox45->TabStop = false;
			// 
			// pictureBox44
			// 
			this->pictureBox44->BackColor = System::Drawing::Color::MistyRose;
			this->pictureBox44->Location = System::Drawing::Point(320, 192);
			this->pictureBox44->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox44->Name = L"pictureBox44";
			this->pictureBox44->Size = System::Drawing::Size(64, 64);
			this->pictureBox44->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox44->TabIndex = 29;
			this->pictureBox44->TabStop = false;
			// 
			// pictureBox43
			// 
			this->pictureBox43->BackColor = System::Drawing::Color::Brown;
			this->pictureBox43->Location = System::Drawing::Point(256, 192);
			this->pictureBox43->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox43->Name = L"pictureBox43";
			this->pictureBox43->Size = System::Drawing::Size(64, 64);
			this->pictureBox43->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox43->TabIndex = 28;
			this->pictureBox43->TabStop = false;
			// 
			// pictureBox42
			// 
			this->pictureBox42->BackColor = System::Drawing::Color::MistyRose;
			this->pictureBox42->Location = System::Drawing::Point(192, 192);
			this->pictureBox42->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox42->Name = L"pictureBox42";
			this->pictureBox42->Size = System::Drawing::Size(64, 64);
			this->pictureBox42->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox42->TabIndex = 27;
			this->pictureBox42->TabStop = false;
			// 
			// pictureBox41
			// 
			this->pictureBox41->BackColor = System::Drawing::Color::Brown;
			this->pictureBox41->Location = System::Drawing::Point(128, 192);
			this->pictureBox41->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox41->Name = L"pictureBox41";
			this->pictureBox41->Size = System::Drawing::Size(64, 64);
			this->pictureBox41->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox41->TabIndex = 26;
			this->pictureBox41->TabStop = false;
			// 
			// pictureBox40
			// 
			this->pictureBox40->BackColor = System::Drawing::Color::MistyRose;
			this->pictureBox40->Location = System::Drawing::Point(64, 192);
			this->pictureBox40->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox40->Name = L"pictureBox40";
			this->pictureBox40->Size = System::Drawing::Size(64, 64);
			this->pictureBox40->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox40->TabIndex = 25;
			this->pictureBox40->TabStop = false;
			// 
			// pictureBox39
			// 
			this->pictureBox39->BackColor = System::Drawing::Color::Brown;
			this->pictureBox39->Location = System::Drawing::Point(0, 192);
			this->pictureBox39->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox39->Name = L"pictureBox39";
			this->pictureBox39->Size = System::Drawing::Size(64, 64);
			this->pictureBox39->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox39->TabIndex = 24;
			this->pictureBox39->TabStop = false;
			// 
			// pictureBox38
			// 
			this->pictureBox38->BackColor = System::Drawing::Color::Brown;
			this->pictureBox38->Location = System::Drawing::Point(448, 128);
			this->pictureBox38->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox38->Name = L"pictureBox38";
			this->pictureBox38->Size = System::Drawing::Size(64, 64);
			this->pictureBox38->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox38->TabIndex = 23;
			this->pictureBox38->TabStop = false;
			// 
			// pictureBox37
			// 
			this->pictureBox37->BackColor = System::Drawing::Color::MistyRose;
			this->pictureBox37->Location = System::Drawing::Point(384, 128);
			this->pictureBox37->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox37->Name = L"pictureBox37";
			this->pictureBox37->Size = System::Drawing::Size(64, 64);
			this->pictureBox37->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox37->TabIndex = 22;
			this->pictureBox37->TabStop = false;
			// 
			// pictureBox36
			// 
			this->pictureBox36->BackColor = System::Drawing::Color::Brown;
			this->pictureBox36->Location = System::Drawing::Point(320, 128);
			this->pictureBox36->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox36->Name = L"pictureBox36";
			this->pictureBox36->Size = System::Drawing::Size(64, 64);
			this->pictureBox36->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox36->TabIndex = 21;
			this->pictureBox36->TabStop = false;
			// 
			// pictureBox35
			// 
			this->pictureBox35->BackColor = System::Drawing::Color::MistyRose;
			this->pictureBox35->Location = System::Drawing::Point(256, 128);
			this->pictureBox35->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox35->Name = L"pictureBox35";
			this->pictureBox35->Size = System::Drawing::Size(64, 64);
			this->pictureBox35->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox35->TabIndex = 20;
			this->pictureBox35->TabStop = false;
			// 
			// pictureBox34
			// 
			this->pictureBox34->BackColor = System::Drawing::Color::Brown;
			this->pictureBox34->Location = System::Drawing::Point(192, 128);
			this->pictureBox34->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox34->Name = L"pictureBox34";
			this->pictureBox34->Size = System::Drawing::Size(64, 64);
			this->pictureBox34->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox34->TabIndex = 19;
			this->pictureBox34->TabStop = false;
			// 
			// pictureBox33
			// 
			this->pictureBox33->BackColor = System::Drawing::Color::MistyRose;
			this->pictureBox33->Location = System::Drawing::Point(128, 128);
			this->pictureBox33->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox33->Name = L"pictureBox33";
			this->pictureBox33->Size = System::Drawing::Size(64, 64);
			this->pictureBox33->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox33->TabIndex = 18;
			this->pictureBox33->TabStop = false;
			// 
			// pictureBox32
			// 
			this->pictureBox32->BackColor = System::Drawing::Color::Brown;
			this->pictureBox32->Location = System::Drawing::Point(64, 128);
			this->pictureBox32->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox32->Name = L"pictureBox32";
			this->pictureBox32->Size = System::Drawing::Size(64, 64);
			this->pictureBox32->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox32->TabIndex = 17;
			this->pictureBox32->TabStop = false;
			// 
			// pictureBox31
			// 
			this->pictureBox31->BackColor = System::Drawing::Color::MistyRose;
			this->pictureBox31->Location = System::Drawing::Point(0, 128);
			this->pictureBox31->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox31->Name = L"pictureBox31";
			this->pictureBox31->Size = System::Drawing::Size(64, 64);
			this->pictureBox31->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox31->TabIndex = 16;
			this->pictureBox31->TabStop = false;
			// 
			// pictureBox30
			// 
			this->pictureBox30->BackColor = System::Drawing::Color::MistyRose;
			this->pictureBox30->Location = System::Drawing::Point(448, 64);
			this->pictureBox30->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox30->Name = L"pictureBox30";
			this->pictureBox30->Size = System::Drawing::Size(64, 64);
			this->pictureBox30->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox30->TabIndex = 15;
			this->pictureBox30->TabStop = false;
			// 
			// pictureBox29
			// 
			this->pictureBox29->BackColor = System::Drawing::Color::Brown;
			this->pictureBox29->Location = System::Drawing::Point(384, 64);
			this->pictureBox29->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox29->Name = L"pictureBox29";
			this->pictureBox29->Size = System::Drawing::Size(64, 64);
			this->pictureBox29->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox29->TabIndex = 14;
			this->pictureBox29->TabStop = false;
			// 
			// pictureBox28
			// 
			this->pictureBox28->BackColor = System::Drawing::Color::MistyRose;
			this->pictureBox28->Location = System::Drawing::Point(320, 64);
			this->pictureBox28->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox28->Name = L"pictureBox28";
			this->pictureBox28->Size = System::Drawing::Size(64, 64);
			this->pictureBox28->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox28->TabIndex = 13;
			this->pictureBox28->TabStop = false;
			// 
			// pictureBox27
			// 
			this->pictureBox27->BackColor = System::Drawing::Color::Brown;
			this->pictureBox27->Location = System::Drawing::Point(256, 64);
			this->pictureBox27->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox27->Name = L"pictureBox27";
			this->pictureBox27->Size = System::Drawing::Size(64, 64);
			this->pictureBox27->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox27->TabIndex = 12;
			this->pictureBox27->TabStop = false;
			// 
			// pictureBox26
			// 
			this->pictureBox26->BackColor = System::Drawing::Color::MistyRose;
			this->pictureBox26->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox26.Image")));
			this->pictureBox26->Location = System::Drawing::Point(192, 64);
			this->pictureBox26->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox26->Name = L"pictureBox26";
			this->pictureBox26->Size = System::Drawing::Size(64, 64);
			this->pictureBox26->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox26->TabIndex = 11;
			this->pictureBox26->TabStop = false;
			// 
			// pictureBox25
			// 
			this->pictureBox25->BackColor = System::Drawing::Color::Brown;
			this->pictureBox25->Location = System::Drawing::Point(128, 64);
			this->pictureBox25->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox25->Name = L"pictureBox25";
			this->pictureBox25->Size = System::Drawing::Size(64, 64);
			this->pictureBox25->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox25->TabIndex = 10;
			this->pictureBox25->TabStop = false;
			// 
			// pictureBox24
			// 
			this->pictureBox24->BackColor = System::Drawing::Color::MistyRose;
			this->pictureBox24->Location = System::Drawing::Point(64, 64);
			this->pictureBox24->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox24->Name = L"pictureBox24";
			this->pictureBox24->Size = System::Drawing::Size(64, 64);
			this->pictureBox24->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox24->TabIndex = 9;
			this->pictureBox24->TabStop = false;
			// 
			// pictureBox23
			// 
			this->pictureBox23->BackColor = System::Drawing::Color::Brown;
			this->pictureBox23->Location = System::Drawing::Point(0, 64);
			this->pictureBox23->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox23->Name = L"pictureBox23";
			this->pictureBox23->Size = System::Drawing::Size(64, 64);
			this->pictureBox23->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox23->TabIndex = 8;
			this->pictureBox23->TabStop = false;
			// 
			// pictureBox22
			// 
			this->pictureBox22->BackColor = System::Drawing::Color::Brown;
			this->pictureBox22->Location = System::Drawing::Point(448, 0);
			this->pictureBox22->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox22->Name = L"pictureBox22";
			this->pictureBox22->Size = System::Drawing::Size(64, 64);
			this->pictureBox22->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox22->TabIndex = 7;
			this->pictureBox22->TabStop = false;
			// 
			// pictureBox21
			// 
			this->pictureBox21->BackColor = System::Drawing::Color::MistyRose;
			this->pictureBox21->Location = System::Drawing::Point(384, 0);
			this->pictureBox21->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox21->Name = L"pictureBox21";
			this->pictureBox21->Size = System::Drawing::Size(64, 64);
			this->pictureBox21->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox21->TabIndex = 6;
			this->pictureBox21->TabStop = false;
			// 
			// pictureBox20
			// 
			this->pictureBox20->BackColor = System::Drawing::Color::Brown;
			this->pictureBox20->Location = System::Drawing::Point(320, 0);
			this->pictureBox20->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox20->Name = L"pictureBox20";
			this->pictureBox20->Size = System::Drawing::Size(64, 64);
			this->pictureBox20->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox20->TabIndex = 5;
			this->pictureBox20->TabStop = false;
			this->pictureBox20->Click += gcnew System::EventHandler(this, &MainForm::pictureBox20_Click);
			// 
			// pictureBox19
			// 
			this->pictureBox19->BackColor = System::Drawing::Color::MistyRose;
			this->pictureBox19->Location = System::Drawing::Point(256, 0);
			this->pictureBox19->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox19->Name = L"pictureBox19";
			this->pictureBox19->Size = System::Drawing::Size(64, 64);
			this->pictureBox19->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox19->TabIndex = 4;
			this->pictureBox19->TabStop = false;
			// 
			// pictureBox18
			// 
			this->pictureBox18->BackColor = System::Drawing::Color::Brown;
			this->pictureBox18->Location = System::Drawing::Point(192, 0);
			this->pictureBox18->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox18->Name = L"pictureBox18";
			this->pictureBox18->Size = System::Drawing::Size(64, 64);
			this->pictureBox18->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox18->TabIndex = 3;
			this->pictureBox18->TabStop = false;
			// 
			// pictureBox17
			// 
			this->pictureBox17->BackColor = System::Drawing::Color::MistyRose;
			this->pictureBox17->Location = System::Drawing::Point(128, 0);
			this->pictureBox17->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox17->Name = L"pictureBox17";
			this->pictureBox17->Size = System::Drawing::Size(64, 64);
			this->pictureBox17->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox17->TabIndex = 2;
			this->pictureBox17->TabStop = false;
			// 
			// pictureBox16
			// 
			this->pictureBox16->BackColor = System::Drawing::Color::Brown;
			this->pictureBox16->Location = System::Drawing::Point(64, 0);
			this->pictureBox16->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox16->Name = L"pictureBox16";
			this->pictureBox16->Size = System::Drawing::Size(64, 64);
			this->pictureBox16->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox16->TabIndex = 1;
			this->pictureBox16->TabStop = false;
			// 
			// pictureBox15
			// 
			this->pictureBox15->BackColor = System::Drawing::Color::MistyRose;
			this->pictureBox15->Location = System::Drawing::Point(0, 0);
			this->pictureBox15->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox15->Name = L"pictureBox15";
			this->pictureBox15->Size = System::Drawing::Size(64, 64);
			this->pictureBox15->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox15->TabIndex = 0;
			this->pictureBox15->TabStop = false;
			// 
			// ActivePlayerName
			// 
			this->ActivePlayerName->AutoSize = true;
			this->ActivePlayerName->Location = System::Drawing::Point(709, 9);
			this->ActivePlayerName->Name = L"ActivePlayerName";
			this->ActivePlayerName->Size = System::Drawing::Size(11, 16);
			this->ActivePlayerName->TabIndex = 69;
			this->ActivePlayerName->Text = L"-";
			this->ActivePlayerName->Click += gcnew System::EventHandler(this, &MainForm::label66_Click);
			// 
			// backButton
			// 
			this->backButton->Location = System::Drawing::Point(677, 532);
			this->backButton->Name = L"backButton";
			this->backButton->Size = System::Drawing::Size(75, 23);
			this->backButton->TabIndex = 6;
			this->backButton->Text = L"Back";
			this->backButton->UseVisualStyleBackColor = true;
			this->backButton->Visible = false;
			this->backButton->Click += gcnew System::EventHandler(this, &MainForm::backButton_Click);
			// 
			// label66
			// 
			this->label66->AutoSize = true;
			this->label66->Location = System::Drawing::Point(81, 9);
			this->label66->Name = L"label66";
			this->label66->Size = System::Drawing::Size(15, 16);
			this->label66->TabIndex = 70;
			this->label66->Text = L"a";
			this->label66->Click += gcnew System::EventHandler(this, &MainForm::label66_Click_1);
			// 
			// label68
			// 
			this->label68->AutoSize = true;
			this->label68->Location = System::Drawing::Point(142, 9);
			this->label68->Name = L"label68";
			this->label68->Size = System::Drawing::Size(15, 16);
			this->label68->TabIndex = 72;
			this->label68->Text = L"b";
			this->label68->Click += gcnew System::EventHandler(this, &MainForm::label68_Click);
			// 
			// label69
			// 
			this->label69->AutoSize = true;
			this->label69->Location = System::Drawing::Point(205, 9);
			this->label69->Name = L"label69";
			this->label69->Size = System::Drawing::Size(14, 16);
			this->label69->TabIndex = 73;
			this->label69->Text = L"c";
			this->label69->Click += gcnew System::EventHandler(this, &MainForm::label69_Click);
			// 
			// label70
			// 
			this->label70->AutoSize = true;
			this->label70->Location = System::Drawing::Point(274, 9);
			this->label70->Name = L"label70";
			this->label70->Size = System::Drawing::Size(15, 16);
			this->label70->TabIndex = 74;
			this->label70->Text = L"d";
			// 
			// label71
			// 
			this->label71->AutoSize = true;
			this->label71->Location = System::Drawing::Point(337, 9);
			this->label71->Name = L"label71";
			this->label71->Size = System::Drawing::Size(15, 16);
			this->label71->TabIndex = 75;
			this->label71->Text = L"e";
			this->label71->Click += gcnew System::EventHandler(this, &MainForm::label71_Click);
			// 
			// label67
			// 
			this->label67->AutoSize = true;
			this->label67->Location = System::Drawing::Point(402, 9);
			this->label67->Name = L"label67";
			this->label67->Size = System::Drawing::Size(10, 16);
			this->label67->TabIndex = 76;
			this->label67->Text = L"f";
			// 
			// label72
			// 
			this->label72->AutoSize = true;
			this->label72->Location = System::Drawing::Point(466, 9);
			this->label72->Name = L"label72";
			this->label72->Size = System::Drawing::Size(15, 16);
			this->label72->TabIndex = 77;
			this->label72->Text = L"g";
			// 
			// label73
			// 
			this->label73->AutoSize = true;
			this->label73->Location = System::Drawing::Point(529, 9);
			this->label73->Name = L"label73";
			this->label73->Size = System::Drawing::Size(14, 16);
			this->label73->TabIndex = 78;
			this->label73->Text = L"h";
			// 
			// label74
			// 
			this->label74->AutoSize = true;
			this->label74->Location = System::Drawing::Point(22, 66);
			this->label74->Name = L"label74";
			this->label74->Size = System::Drawing::Size(14, 16);
			this->label74->TabIndex = 79;
			this->label74->Text = L"8";
			this->label74->Click += gcnew System::EventHandler(this, &MainForm::label74_Click);
			// 
			// label75
			// 
			this->label75->AutoSize = true;
			this->label75->Location = System::Drawing::Point(22, 130);
			this->label75->Name = L"label75";
			this->label75->Size = System::Drawing::Size(14, 16);
			this->label75->TabIndex = 80;
			this->label75->Text = L"7";
			// 
			// label76
			// 
			this->label76->AutoSize = true;
			this->label76->Location = System::Drawing::Point(22, 188);
			this->label76->Name = L"label76";
			this->label76->Size = System::Drawing::Size(14, 16);
			this->label76->TabIndex = 81;
			this->label76->Text = L"6";
			// 
			// label77
			// 
			this->label77->AutoSize = true;
			this->label77->Location = System::Drawing::Point(22, 257);
			this->label77->Name = L"label77";
			this->label77->Size = System::Drawing::Size(14, 16);
			this->label77->TabIndex = 82;
			this->label77->Text = L"5";
			this->label77->Click += gcnew System::EventHandler(this, &MainForm::label77_Click);
			// 
			// label78
			// 
			this->label78->AutoSize = true;
			this->label78->Location = System::Drawing::Point(22, 316);
			this->label78->Name = L"label78";
			this->label78->Size = System::Drawing::Size(14, 16);
			this->label78->TabIndex = 83;
			this->label78->Text = L"4";
			this->label78->Click += gcnew System::EventHandler(this, &MainForm::label78_Click);
			// 
			// label79
			// 
			this->label79->AutoSize = true;
			this->label79->Location = System::Drawing::Point(22, 384);
			this->label79->Name = L"label79";
			this->label79->Size = System::Drawing::Size(14, 16);
			this->label79->TabIndex = 84;
			this->label79->Text = L"3";
			this->label79->Click += gcnew System::EventHandler(this, &MainForm::label79_Click);
			// 
			// label80
			// 
			this->label80->AutoSize = true;
			this->label80->Location = System::Drawing::Point(22, 449);
			this->label80->Name = L"label80";
			this->label80->Size = System::Drawing::Size(14, 16);
			this->label80->TabIndex = 85;
			this->label80->Text = L"2";
			// 
			// label81
			// 
			this->label81->AutoSize = true;
			this->label81->Location = System::Drawing::Point(22, 510);
			this->label81->Name = L"label81";
			this->label81->Size = System::Drawing::Size(14, 16);
			this->label81->TabIndex = 86;
			this->label81->Text = L"1";
			// 
			// label82
			// 
			this->label82->AutoSize = true;
			this->label82->Location = System::Drawing::Point(598, 55);
			this->label82->Name = L"label82";
			this->label82->Size = System::Drawing::Size(85, 16);
			this->label82->TabIndex = 87;
			this->label82->Text = L"Select piece:";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(816, 592);
			this->Controls->Add(this->label82);
			this->Controls->Add(this->label81);
			this->Controls->Add(this->label80);
			this->Controls->Add(this->label79);
			this->Controls->Add(this->label78);
			this->Controls->Add(this->label77);
			this->Controls->Add(this->label76);
			this->Controls->Add(this->label75);
			this->Controls->Add(this->label74);
			this->Controls->Add(this->label73);
			this->Controls->Add(this->label72);
			this->Controls->Add(this->label67);
			this->Controls->Add(this->label71);
			this->Controls->Add(this->label70);
			this->Controls->Add(this->label69);
			this->Controls->Add(this->label68);
			this->Controls->Add(this->label66);
			this->Controls->Add(this->ActivePlayerName);
			this->Controls->Add(this->DBoard);
			this->Controls->Add(this->label65);
			this->Controls->Add(this->interactionPanel);
			this->Controls->Add(this->backButton);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"MainForm";
			this->Text = L"Board Simulator";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->interactionPanel->ResumeLayout(false);
			this->DBoard->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox78))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox77))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox76))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox75))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox74))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox73))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox72))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox71))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox70))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox69))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox68))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox67))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox66))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox65))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox64))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox63))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox62))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox61))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox60))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox59))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox58))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox57))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox56))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox55))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox54))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox53))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox52))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox51))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox50))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox49))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox48))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox47))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox46))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox45))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox44))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox43))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox42))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox41))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox40))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox39))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox38))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox37))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox36))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox35))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox34))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox33))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox32))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox31))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox30))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox29))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox28))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox27))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox26))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox25))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox24))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox23))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox22))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox21))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox20))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox19))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox18))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox17))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox16))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox15))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void backgroundWorker1_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {
	}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label65_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void panel1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void label1_Click_1(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void tableLayoutPanel1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	}

	private: System::Void panel2_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void label1_Click_2(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label66_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void flowLayoutPanel1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label66_Click_1(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label68_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label74_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label69_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void pictureBox3_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void pictureBox9_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void pictureBox20_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label71_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label79_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label78_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label77_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	};




	/// <summary>
	/// Summary for MainForm
	/// </summary>


}


