#include "CSesion.h"
#include <Windows.h>
#include <MMSystem.h>

namespace UNO2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//
		}

	protected:
		bool newGame, crrPlaying;
		BufferedGraphics ^ buffer;


	private: System::Windows::Forms::Timer^  tiempo;
	protected:
		Bitmap ^ cardBmp;
		Bitmap^escenario;

	private: System::Windows::Forms::PictureBox^  unoLogo;
	private: System::Windows::Forms::Button^  buttonNewG;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Label^  labelPlayers;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown1;
	private: System::Windows::Forms::Label^  labelName;
	private: System::Windows::Forms::Button^  playButton;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  nameBox1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  puntaje;
	private: System::Windows::Forms::Button^  unoButton;
	private: System::Windows::Forms::Button^  pasarButton;
	private: System::Windows::Forms::Button^  colorGreenBoton;
	private: System::Windows::Forms::Button^  colorRedBoton;
	private: System::Windows::Forms::Button^  colorAzulBoton;
	private: System::Windows::Forms::Button^  colorAmarilloBoton;




	protected:
		CSesion * sesionJuego;
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		};
	private: System::ComponentModel::IContainer^  components;
	protected:

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->tiempo = (gcnew System::Windows::Forms::Timer(this->components));
			this->unoLogo = (gcnew System::Windows::Forms::PictureBox());
			this->buttonNewG = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->labelPlayers = (gcnew System::Windows::Forms::Label());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->labelName = (gcnew System::Windows::Forms::Label());
			this->playButton = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->nameBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->puntaje = (gcnew System::Windows::Forms::Label());
			this->unoButton = (gcnew System::Windows::Forms::Button());
			this->pasarButton = (gcnew System::Windows::Forms::Button());
			this->colorGreenBoton = (gcnew System::Windows::Forms::Button());
			this->colorRedBoton = (gcnew System::Windows::Forms::Button());
			this->colorAzulBoton = (gcnew System::Windows::Forms::Button());
			this->colorAmarilloBoton = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->unoLogo))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
			this->SuspendLayout();
			// 
			// tiempo
			// 
			this->tiempo->Enabled = true;
			this->tiempo->Interval = 200;
			this->tiempo->Tick += gcnew System::EventHandler(this, &MyForm::tiempo_Tick);
			// 
			// unoLogo
			// 
			this->unoLogo->BackColor = System::Drawing::Color::Transparent;
			resources->ApplyResources(this->unoLogo, L"unoLogo");
			this->unoLogo->Name = L"unoLogo";
			this->unoLogo->TabStop = false;
			this->unoLogo->UseWaitCursor = true;
			// 
			// buttonNewG
			// 
			this->buttonNewG->AutoEllipsis = true;
			this->buttonNewG->BackColor = System::Drawing::Color::White;
			resources->ApplyResources(this->buttonNewG, L"buttonNewG");
			this->buttonNewG->CausesValidation = false;
			this->buttonNewG->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->buttonNewG->Name = L"buttonNewG";
			this->buttonNewG->TabStop = false;
			this->buttonNewG->UseVisualStyleBackColor = false;
			this->buttonNewG->Click += gcnew System::EventHandler(this, &MyForm::buttonNewG_Click);
			// 
			// button1
			// 
			this->button1->AutoEllipsis = true;
			this->button1->BackColor = System::Drawing::Color::White;
			resources->ApplyResources(this->button1, L"button1");
			this->button1->CausesValidation = false;
			this->button1->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->button1->Name = L"button1";
			this->button1->TabStop = false;
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->AutoEllipsis = true;
			resources->ApplyResources(this->button2, L"button2");
			this->button2->BackColor = System::Drawing::Color::White;
			this->button2->CausesValidation = false;
			this->button2->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->button2->Name = L"button2";
			this->button2->TabStop = false;
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// labelPlayers
			// 
			resources->ApplyResources(this->labelPlayers, L"labelPlayers");
			this->labelPlayers->BackColor = System::Drawing::Color::Transparent;
			this->labelPlayers->Name = L"labelPlayers";
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->numericUpDown1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			resources->ApplyResources(this->numericUpDown1, L"numericUpDown1");
			this->numericUpDown1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
			this->numericUpDown1->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->ReadOnly = true;
			this->numericUpDown1->TabStop = false;
			this->numericUpDown1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			// 
			// labelName
			// 
			resources->ApplyResources(this->labelName, L"labelName");
			this->labelName->BackColor = System::Drawing::Color::Transparent;
			this->labelName->Name = L"labelName";
			this->labelName->Click += gcnew System::EventHandler(this, &MyForm::labelName_Click);
			// 
			// playButton
			// 
			this->playButton->AutoEllipsis = true;
			this->playButton->BackColor = System::Drawing::Color::White;
			resources->ApplyResources(this->playButton, L"playButton");
			this->playButton->CausesValidation = false;
			this->playButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->playButton->Name = L"playButton";
			this->playButton->TabStop = false;
			this->playButton->UseVisualStyleBackColor = false;
			this->playButton->Click += gcnew System::EventHandler(this, &MyForm::playButton_Click);
			// 
			// label1
			// 
			resources->ApplyResources(this->label1, L"label1");
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Name = L"label1";
			// 
			// nameBox1
			// 
			resources->ApplyResources(this->nameBox1, L"nameBox1");
			this->nameBox1->Name = L"nameBox1";
			// 
			// label2
			// 
			resources->ApplyResources(this->label2, L"label2");
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Name = L"label2";
			// 
			// puntaje
			// 
			resources->ApplyResources(this->puntaje, L"puntaje");
			this->puntaje->BackColor = System::Drawing::Color::Transparent;
			this->puntaje->Name = L"puntaje";
			// 
			// unoButton
			// 
			this->unoButton->AutoEllipsis = true;
			this->unoButton->BackColor = System::Drawing::Color::White;
			resources->ApplyResources(this->unoButton, L"unoButton");
			this->unoButton->CausesValidation = false;
			this->unoButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->unoButton->Name = L"unoButton";
			this->unoButton->TabStop = false;
			this->unoButton->UseVisualStyleBackColor = false;
			this->unoButton->Click += gcnew System::EventHandler(this, &MyForm::unoButton_Click);
			// 
			// pasarButton
			// 
			this->pasarButton->AutoEllipsis = true;
			this->pasarButton->BackColor = System::Drawing::Color::White;
			resources->ApplyResources(this->pasarButton, L"pasarButton");
			this->pasarButton->CausesValidation = false;
			this->pasarButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->pasarButton->Name = L"pasarButton";
			this->pasarButton->TabStop = false;
			this->pasarButton->UseVisualStyleBackColor = false;
			this->pasarButton->Click += gcnew System::EventHandler(this, &MyForm::pasarButton_Click);
			// 
			// colorGreenBoton
			// 
			this->colorGreenBoton->AutoEllipsis = true;
			this->colorGreenBoton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			resources->ApplyResources(this->colorGreenBoton, L"colorGreenBoton");
			this->colorGreenBoton->CausesValidation = false;
			this->colorGreenBoton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->colorGreenBoton->Name = L"colorGreenBoton";
			this->colorGreenBoton->TabStop = false;
			this->colorGreenBoton->UseVisualStyleBackColor = false;
			this->colorGreenBoton->Click += gcnew System::EventHandler(this, &MyForm::colorGreenBoton_Click);
			// 
			// colorRedBoton
			// 
			this->colorRedBoton->AutoEllipsis = true;
			this->colorRedBoton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			resources->ApplyResources(this->colorRedBoton, L"colorRedBoton");
			this->colorRedBoton->CausesValidation = false;
			this->colorRedBoton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->colorRedBoton->Name = L"colorRedBoton";
			this->colorRedBoton->TabStop = false;
			this->colorRedBoton->UseVisualStyleBackColor = false;
			this->colorRedBoton->Click += gcnew System::EventHandler(this, &MyForm::colorRedBoton_Click);
			// 
			// colorAzulBoton
			// 
			this->colorAzulBoton->AutoEllipsis = true;
			this->colorAzulBoton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			resources->ApplyResources(this->colorAzulBoton, L"colorAzulBoton");
			this->colorAzulBoton->CausesValidation = false;
			this->colorAzulBoton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->colorAzulBoton->Name = L"colorAzulBoton";
			this->colorAzulBoton->TabStop = false;
			this->colorAzulBoton->UseVisualStyleBackColor = false;
			this->colorAzulBoton->Click += gcnew System::EventHandler(this, &MyForm::colorAzulBoton_Click);
			// 
			// colorAmarilloBoton
			// 
			this->colorAmarilloBoton->AutoEllipsis = true;
			this->colorAmarilloBoton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			resources->ApplyResources(this->colorAmarilloBoton, L"colorAmarilloBoton");
			this->colorAmarilloBoton->CausesValidation = false;
			this->colorAmarilloBoton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->colorAmarilloBoton->Name = L"colorAmarilloBoton";
			this->colorAmarilloBoton->TabStop = false;
			this->colorAmarilloBoton->UseVisualStyleBackColor = false;
			this->colorAmarilloBoton->Click += gcnew System::EventHandler(this, &MyForm::colorAmarilloBoton_Click);
			// 
			// MyForm
			// 
			resources->ApplyResources(this, L"$this");
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->colorAmarilloBoton);
			this->Controls->Add(this->colorAzulBoton);
			this->Controls->Add(this->colorRedBoton);
			this->Controls->Add(this->colorGreenBoton);
			this->Controls->Add(this->pasarButton);
			this->Controls->Add(this->unoButton);
			this->Controls->Add(this->puntaje);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->nameBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->playButton);
			this->Controls->Add(this->labelName);
			this->Controls->Add(this->numericUpDown1);
			this->Controls->Add(this->labelPlayers);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->buttonNewG);
			this->Controls->Add(this->unoLogo);
			this->ForeColor = System::Drawing::Color::DarkRed;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->KeyPreview = true;
			this->MaximizeBox = false;
			this->Name = L"MyForm";
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Show;
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->Click += gcnew System::EventHandler(this, &MyForm::MyForm_MouseDown);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->unoLogo))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_keyPressed);

		}
#pragma endregion

	System::Void MyForm_keyPressed(Object^ sender, KeyEventArgs^ e){
	
	}
	private: System::Void Home_Page() {
		puntaje->Visible = false;
		label2->Visible = false;

		unoLogo->Visible = true;
		buttonNewG->Visible = true;
		button1->Visible = true;
		button2->Visible = true;
		label1->Visible = true;

		button1->Enabled = true;
		button2->Enabled = true;
		playButton->Enabled = true;
		buttonNewG->Enabled = true;

		unoButton->Visible = false;
		pasarButton->Visible = false;

		colorRedBoton->		 Visible = false;
		colorGreenBoton->	 Visible = false;
		colorAmarilloBoton-> Visible = false;
		colorAzulBoton->	 Visible = false;
	}

	private: System::Void Game_visual() {
		if (this->crrPlaying) {
			labelPlayers->Visible = false;
			labelName->Visible = false;
			numericUpDown1->Visible = false;
			playButton->Visible = false;
			nameBox1->Visible = false;

			unoLogo->Visible = false;
			buttonNewG->Visible = false;
			button1->Visible = false;
			button2->Visible = false;
			label1->Visible = false;

			button1->Enabled = false;
			button2->Enabled = false;
			playButton->Enabled = false;
			buttonNewG->Enabled = false;

			unoButton->Visible = true;
			pasarButton->Visible = true;
		}
		else if (this->newGame) {
			labelPlayers->Visible = true;
			labelName->Visible = true;
			numericUpDown1->Visible = true;
			playButton->Visible = true;
			nameBox1->Visible = true;
		}

	}

	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
		cardBmp = gcnew Bitmap("Imagenes/spritesheet_uno.png");
		escenario = gcnew Bitmap("Imagenes/top.jpg");
		this->newGame = this->crrPlaying = false;
		tiempo->Enabled = true;
		this->puntaje->Visible = false;
		buffer = BufferedGraphicsManager::Current->Allocate(this->CreateGraphics(), this->ClientRectangle);

		Home_Page();
	}

			 Point mousePos;
			 //CLICKK MF.
	private: System::Void MyForm_MouseDown(System::Object^  sender, System::EventArgs^  e) {
		buffer->Graphics->DrawImage(escenario, this->ClientRectangle);
		if (this->crrPlaying) {
			if (!sesionJuego->Jugar(buffer, cardBmp, this->ClientRectangle, mousePos, true)) {
				crrPlaying = false;
				Home_Page();
				String ^ JWinner;
				for (short i = 0; i < this->sesionJuego->getJugadores().size(); i++) {
					if (this->sesionJuego->getJugadores().at(i)->getScore() >= 10)
						JWinner = gcnew String(this->sesionJuego->getJugadores().at(i)->getNombre().c_str());
				};
				MessageBox::Show(JWinner + " ha \n ganado.", "GANADOR",
					MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			};
		}
	}
	
	String^ message;
	bool jugadorP = false;
	private: System::Void tiempo_Tick(System::Object^  sender, System::EventArgs^  e){
		buffer->Graphics->DrawImage(escenario, this->ClientRectangle);
		Game_visual();

		if (this->crrPlaying) {
			mousePos = this->PointToClient(System::Windows::Forms::Cursor::Position);
			System::Windows::Forms::Cursor::Position
			if (this->newGame) {
				
				sesionJuego->crearNJuego(buffer, cardBmp, this->ClientRectangle, mousePos);
				String^ dealerName = gcnew String(this->sesionJuego->dealer()->getNombre().c_str());
				String^ playerNombre = gcnew String(this->sesionJuego->crrPlayer()->getNombre().c_str());
				if (this->sesionJuego->crrPlayer() == this->sesionJuego->getJugadores().at(0)) {
					tiempo->Interval = 200; jugadorP = true;
				}
				else {
					tiempo->Interval = 1200;  jugadorP = false;
				}

				puntaje->Visible = true;
				label2->Visible = true;

				this->newGame = false;
				message = "El dealer es " + dealerName +
					"\n el primer jugador es " + playerNombre;
				
				MessageBox::Show(message);
			}

			//m{s lento cuando juegue la computadora ... kind of

			if (this->sesionJuego->crrPlayer() == this->sesionJuego->getJugadores().at(0)
				&& !jugadorP) {
				tiempo->Interval = 200; jugadorP = true;
			}
			else if (this->sesionJuego->crrPlayer() != this->sesionJuego->getJugadores().at(0)
				&& jugadorP) {
				tiempo->Interval = 1200;  jugadorP = false;
			}

			message = gcnew String("Ptns: ");
			for (short i = 0; i < this->sesionJuego->getJugadores().size(); i++) {
				message += gcnew String(this->sesionJuego->getJugadores().at(i)->getNombre().c_str());
				message += gcnew String(" (" + this->sesionJuego->getJugadores().at(i)->getScore() + ") ");
			}

			puntaje->Text = message;
			label2->Text = "MATCH - " + this->sesionJuego->getCntPartidas();

			if (!sesionJuego->Jugar(buffer, cardBmp, this->ClientRectangle, mousePos, false)) {
				crrPlaying = false;
				delete sesionJuego;
				Home_Page();
				//fin de la sesion should be end of the game
				//need to show puntaje

				String ^winner;
				for (short i = 0; i < this->sesionJuego->getJugadores().size(); i++) {
					if (this->sesionJuego->getJugadores().at(i)->getScore() >= 500)
						winner = gcnew String(this->sesionJuego->getJugadores().at(i)->getNombre().c_str());
				};

				MessageBox::Show(winner + " ha \n ganado.", "GANADOR",
					MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			}
			visualChangeColor();
		}

		buffer->Render(this->CreateGraphics());
	}

private: void visualChangeColor() {
	if (sesionJuego->getChangeC()) {
		seeColorButtons(true);
	}else
		seeColorButtons(false);

	}
			 void seeColorButtons(bool see) {
				 colorRedBoton->Visible = see;
				 colorGreenBoton->Visible = see;
				 colorAmarilloBoton->Visible = see;
				 colorAzulBoton->Visible = see;
			 }
	private: System::Void buttonNewG_Click(System::Object^  sender, System::EventArgs^  e) {
		newGame = true;
	}
private: System::Void labelName_Click(System::Object^  sender, System::EventArgs^  e) {
};
private: System::Void nameBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	//
};
private: System::Void playButton_Click(System::Object^  sender, System::EventArgs^  e) {
	crrPlaying = true;
	//
	using namespace Runtime::InteropServices;
	const wchar_t * chars = (const wchar_t *)(Marshal::StringToHGlobalUni(this->nameBox1->Text).ToPointer());
	wstring ws(chars);
	//make String into string para mostrar el nombre del jugador

	string playerName(ws.begin(), ws.end());
	Marshal::FreeHGlobal(IntPtr((void*)chars));

	this->sesionJuego = new CSesion(playerName, short(Decimal::ToInt16(numericUpDown1->Value)));
}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		Application::Exit();
}
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	//instrucciones

}
private: System::Void unoButton_Click(System::Object^  sender, System::EventArgs^  e) {
	if (sesionJuego->crrPlayer() == sesionJuego->getJugadores().at(0) &&
		sesionJuego->crrPlayer()->getAllCards()->size()==2 &&
		sesionJuego->getPartida()->playableCard(sesionJuego->crrPlayer())) {
		MessageBox::Show("UNO!!");
		sesionJuego->crrPlayer()->diceUno();
	}
}
private: System::Void pasarButton_Click(System::Object^  sender, System::EventArgs^  e) {
	if (sesionJuego->crrPlayer() == sesionJuego->getJugadores().at(0)) {
		if (!sesionJuego->getPartida()->getDrewCardP()) {
			sesionJuego->getPartida()->setDrewCard();
			sesionJuego->getPartida()->drawCard();
		}
		else
			sesionJuego->getPartida()->nextTurn();
	}
	}
private: System::Void colorGreenBoton_Click(System::Object^  sender, System::EventArgs^  e) {
	this->sesionJuego->getPartida()->changeColor(2);
	this->sesionJuego->getPartida()->setChangeColor(false);

}
private: System::Void colorRedBoton_Click(System::Object^  sender, System::EventArgs^  e) {
	this->sesionJuego->getPartida()->changeColor(0);
	this->sesionJuego->getPartida()->setChangeColor(false);

}
private: System::Void colorAzulBoton_Click(System::Object^  sender, System::EventArgs^  e) {
	this->sesionJuego->getPartida()->changeColor(3);
	this->sesionJuego->getPartida()->setChangeColor(false);

}
	private: System::Void colorAmarilloBoton_Click(System::Object^  sender, System::EventArgs^  e) {
		this->sesionJuego->getPartida()->changeColor(1);
		this->sesionJuego->getPartida()->setChangeColor(false);
	}

};
};


