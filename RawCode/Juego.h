#include "CJugador.h"
/*
	-How to handle multiple games..
	---This works for hito 1--
	---Change the constructor? Probably---
	ps: this class is only saving one game... I need a new class ::thinking::

*/


class Juego{
private:
	friend class CPartida;
	short crrDealer;
	vector <CJugador*> jugadores;
	CMazoCartas * Mazo;

public:
	Juego() {
		short n = 0;
		while (true) {
			string name;
			cout << "Indique el nombre de su jugador: ";
			cin >> name;
			jugadores.push_back(new CJugador(name));
			n++;

			//agregamos 4 jugadores
			if (n == 4)
				break;
		}
		Mazo = new CMazoCartas();
		Mazo->suffleMazo();
		Mazo->mostrarMazo();

		//Quien Reparte¿?
		dealer();

		//Agregar Cartas
		for (short j = 0; j < 7; j++) {
			short cnt = 0, i = (crrDealer + 1 >= jugadores.size()) ? 0 : crrDealer + 1;
			do {
				jugadores.at(i++)->agregarCarta(Mazo->cartaOnTop());
				if (i >= jugadores.size()) i=0;
				cnt++;
			} while (cnt!=jugadores.size());
		};

		//test crr cards ¿?
		for (short i = 0; i < jugadores.size(); i++) {
			jugadores.at(i)->mostrarMano();
			cout << endl;
		};

		cout << endl;
	};

	~Juego() {
		delete Mazo;
		for (short i=0; i< jugadores.size(); i++)
			delete jugadores.at(i);
	}

	void dealer();
};


//All of this will have to change 
void Juego::dealer() {
	short *turns = new short[jugadores.size()];
	string * names = new string[jugadores.size()];

	for (short i = 0; i < jugadores.size(); i++) {
		CCarta * card = Mazo->cartaOnTop();
		while (card->getValue() > 10) {
			delete card;
			card = Mazo->cartaOnTop();
		}
		names[i] = jugadores[i]->nombre;
		turns[i] = card->getValue();
		delete card;
	}

	for (short i = 0; i < jugadores.size() - 1; i++) {
		for (short j = i + 1; j<jugadores.size(); j++)
			if (turns[i]<turns[j]) {
				short aux = turns[i];
				string auxN = names[i];

				turns[i] = turns[j];
				names[i] = names[j];

				turns[j] = aux;
				names[j] = auxN;
			}
	}

	for (short i = 0; i < jugadores.size(); i++) {
		if (jugadores[i]->nombre == names[0])
			crrDealer = i;
	}

	delete[] turns;
	delete[] names;
}
