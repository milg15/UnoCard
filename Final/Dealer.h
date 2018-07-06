#pragma once
#include "CardDeck.h"
#include <algorithm> //suffle
#include <random> //default_random_engine
#include <chrono> // time()
#include <stack>

class CDealer {
private:
	CardDeck * cardDeck;
	stack <UNOCard*> * pile, *mazo;
	CJugadores * dealer;

public:
	CDealer() {
		this->cardDeck = new CardDeck();
		this->mazo = new stack<UNOCard*>;
		this->pile = new stack <UNOCard*>;

		for (short i =0; i<this->cardDeck->getMazo().size(); i++)
			this->pile->push(this->cardDeck->getMazo().at(i));

		this->suffleMazo();
	}

	CJugadores* getDealer() {
		return this->dealer;
	}

	//Elge quien es el primer jugador - A la derecha del dealer
	void turnos(vector <CJugadores*> players) {
		short high = 0, j = -1;
		for (short i = 0; i < players.size(); i++) {
			UNOCard * temp = getCard();
			while (temp->getEfecto()!=NORMAL) {
				this->returnCard(temp);
				temp = getCard();
			}
			//solo numeros?
			if (high < temp->getValue()) {
				high = temp->getValue();
				j = i;
			}
		}

		players.at(j - 1 == -1 ? players.size() - 1 : j - 1)->setTurno();
		this->dealer = players.at(j);
		return;
	}

	void suffleMazo() {
		unsigned seed = time(NULL);
		std::vector <UNOCard*> temp;
		short size = this->pile->size();
		for (short i = 0; i < size; i++) {
			temp.push_back(this->pile->top());
			this->pile->pop();
		}

		std::shuffle(temp.begin(), temp.end(), std::default_random_engine(seed));

		for (std::vector<UNOCard*>::iterator it = temp.begin(); it != temp.end(); it++)
			this->mazo->push(*it);

		return;
	}

	bool emptyDeck() {
		return mazo->empty();
	}

	//primera mano
	void sieteCIniciales(vector <CJugadores*> players) {
		for (short j = 0; j < 7; j++) {
			//short cnt = 0, i = (crrDealer + 1 >= jugadores.size()) ? 0 : crrDealer + 1;
			short i = 0, cnt = 0;
			do {
				players.at(i++)->agregarCarta(this->mazo->top());
				this->mazo->pop();
				cnt++;
			} while (cnt != players.size());
		}
	}

	std::stack <UNOCard*> * getPile() {
		return this->pile;
	}

	std::stack <UNOCard*> * getMazo() {
		return this->mazo;
	}

	UNOCard * getCard() {
		if (mazo->empty())
			suffleMazo();

		UNOCard * card = mazo->top();
		mazo->pop();
		return card;
	}

	void returnCard(UNOCard * card) {
		pile->push(card);
	}

	~CDealer() {
		short size = this->pile->size();
		for (short i = 0; i < size; i++) 
			this->pile->pop();

		size = this->mazo->size();
		for (short i = 0; i < size; i++) 
			this->mazo->pop();

		delete this->pile;
		delete this->mazo;
		delete this->cardDeck;
	}

};