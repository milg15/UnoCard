#pragma once
#include "CJuego.h"

class CSesion {
private:
	std::vector <CJugadores *> Jugadores;
	CJuego * partida;
	short cntPartidas = 0;

public:
	CSesion(short n) {
		for (short i = 0; i < n; i++) {
			Jugadores.push_back(new CJugadores());
		};
	};

	CSesion(std::string nombre, short n) {
		//posición inicial de cada carta
		partida = NULL;
		Jugadores.push_back(new CJugadores(nombre.size()>0?nombre:"P1"));
		for (short i = 1; i < n; i++)
			Jugadores.push_back(new CPC("Bot " + std::to_string(i)));
	};

	void crearNJuego(BufferedGraphics ^ buffer, Bitmap ^ cardBmp, Rectangulo windowSize, Point mousePoint) {
		for (short i = 1; i < Jugadores.size(); i++) {
			Jugadores.at(i)->setdijoUnoF();
			Jugadores.at(i)->setTurnoF();
		}

		partida = new CJuego(Jugadores);
		partida->posJugadores(windowSize);
		partida->IniciarMatch(buffer, cardBmp, windowSize, mousePoint);
	};

	CJugadores* dealer() {
		return this->partida->getDealer();
	};

	CJugadores* crrPlayer() {
		return this->Jugadores.at(this->partida->crrPlayer()-1);
	};

	CJuego*getPartida() {
		return this->partida;
	};

	bool getChangeC() {
		return this->partida->getChangeColor();
	}

	bool areWePlayin() {
		return (partida != NULL);
	}

	std::vector <CJugadores *>  getJugadores() {
		return this->Jugadores;
	};

	short getCntPartidas(){
		return this->cntPartidas+1;
	}

	//enviar los puntajes
	System::String ^ mensaje(){
		System::String ^ helper;
		helper = gcnew System::String("Ptns: ");
		for (short i = 0; i < Jugadores.size(); i++) {
			helper += gcnew System::String(Jugadores.at(i)->getNombre().c_str());
			helper += gcnew System::String( "(" + Jugadores.at(i)->getScore() + ") ");
		}
		return helper;
		
	};


	bool Jugar(BufferedGraphics ^ buffer, Bitmap ^ cardBmp, Rectangulo windowSize, 
		Point mousePoint, bool click) {
		//Inicia varias partidas hasta que alguno de los jugadores alcance 500pnt
		//partida->crrMatch(buffer, cardBmp, windowSize, mousePoint, click);
		//delete this->partida;
		if (!partida->crrMatch(buffer, cardBmp, windowSize, mousePoint, click)) {
			if (finPartida()) {
				//hey we have a winner
				return false;
			};
			//avisar al jugador que inicia un nuevo Juego
			crearNJuego(buffer, cardBmp, windowSize, mousePoint);

		};
		return true;
	};



	bool finPartida() {
		cntPartidas++;
		delete partida;
		partida = NULL;
		for (short i = 0; i < Jugadores.size(); i++) {
			if (Jugadores.at(i)->getScore() >= 500)
				return true;
		};
		return false;
	};

	~CSesion(){

	}
};