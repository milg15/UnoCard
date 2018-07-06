#include "CJugadores.h"

using namespace std;

class CardDeck{
private:
	vector <UNOCard *> Mazo;

public:
	CardDeck() {
		//incicializa cartas
		for (short c = Rojo; c < Negro; c++) {
			for (short i = 0; i < 10; i++) {
				Mazo.push_back(new CCarta(i, CColor(c)));

				//añade solo una carta valor 0 por color
				if (i)
					Mazo.push_back(new CCarta(i, CColor(c)));
			}
				//agrega 2 cartas de efecto por color
			for (short e= PASA; e < CAMBIA; e++) {
				Mazo.push_back(new CCartaEspecial(20, CColor(c), CEfecto(e)));
				Mazo.push_back(new CCartaEspecial(20, CColor(c), CEfecto(e)));
			}
		}
		for (short i = 0; i < 4; i++) {
			Mazo.push_back(new CCartaEspecialWild(50, CAMBIA));
			Mazo.push_back(new CCartaEspecialWild(50, TOMA4));
		}
	}

	~CardDeck() {
		short size = Mazo.size();
		for (short i = 0; i <size; i++) {
			if (Mazo.at(i)->getValue() < 0) continue;
			delete Mazo.at(i);
		}
	}

	vector<UNOCard*> getMazo() {
		return this->Mazo;
	}
};


//card listener for the mouse
//shuffle