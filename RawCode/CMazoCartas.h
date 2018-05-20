//to see someting
#include <vector> 
#include <algorithm> //suffle
#include <random> //default_random_engine
#include <chrono> // time()
#include "CCartaEspecial.h"

//Se inicializa en cada juego o cuando se a acabado el deck actual

static class CMazoCartas {
private:
	std::vector <CCarta*> *deck; //Vector que almacena todas las cartas en el deck de la partida actual

public:
	CMazoCartas() {
		deck = new std::vector <CCarta*>;
		//agrego todas las cartas a mi vector
		for (short i = Rojo; i < Negro; i++) {
			deck->push_back(new CCarta(0, static_cast<Color>(i)));
			for (short j = 1; j < 10; j++) {
				deck->push_back(new CCarta(j, static_cast<Color>(i)));
				deck->push_back(new CCarta(j, static_cast<Color>(i)));
			}
			for (short j = TOMA2; j <= PASA; j++) {
				deck->push_back(new CCartaEspecial(20, static_cast<Color>(i), static_cast<Efecto>(j)));
				deck->push_back(new CCartaEspecial(20, static_cast<Color>(i), static_cast<Efecto>(j)));
			}
		}
		for (short i = 0; i < 4; i++) {
			deck->push_back(new CCartaEspecial(50, static_cast<Color>(Negro), TOMA4));
			deck->push_back(new CCartaEspecial(50, static_cast<Color>(Negro), CAMBIA));
		}
	};

	~CMazoCartas() {
		for (short i = 0; i < deck->size(); i++)
			delete deck->at(i);
		delete deck;
	}

	void suffleMazo();
	CCarta * cartaOnTop();
	virtual void mostrarMazo();
};

void CMazoCartas::suffleMazo() {
	//Orden de manera aleatoria mi deck 
	unsigned seed = time(NULL);
	std::shuffle(deck->begin(), deck->end(), std::default_random_engine (seed));
	/*System::Random rand;
	for (short i = 0; i < deck->size() - 1; i++) {
		short n = rand.Next(i + 1);
		std::swap(deck[i], deck[n]);
	}*/
}

void CMazoCartas::mostrarMazo() {
	//test to see the cards
	std::cout << "Mazo actual - " << deck->size() << std::endl;
	for (short i = 0; i < deck->size(); i++)
		deck->at(i)->mostrarCarta();
	return;
}

//Envia la ultima carta que cree y la saca del mazo.
CCarta * CMazoCartas::cartaOnTop() {
	CCarta * onTop = this->deck->back();
	this->deck->pop_back();
	return onTop;
}