#pragma once
#include "CCartas.h"
#include <vector>
#include <string>

class CViewPlayer {
protected:
	short side;
	Point middle;
};

class CJugadores: public CViewPlayer {
protected:
	friend class CJuego;
	std::string nombre;
	short score, cartasJugadas;
	bool dijoUNO, turn;
	std::vector <UNOCard*> * myCards;

public:
	CJugadores( ) {
		this->nombre = "Generico";
		this->myCards = new std::vector <UNOCard*>;
	}

	CJugadores(std::string _nombre) {
		this->turn = false;
		this->dijoUNO = false;
		cartasJugadas = score = 0;
		this->nombre = _nombre;
		this->myCards = new std::vector <UNOCard*>;
	}

	void addScore(short _point) {
		score += _point;
	}

	void setNombre(std::string _nombre) {
		this->nombre = _nombre;
	}

	std::string getNombre() {
		return this->nombre;
	}

	void agregarCarta(UNOCard * carta) {
		myCards->push_back(carta);
	}

	std::vector <UNOCard*> * getAllCards() {
		return this->myCards;
	}

	short getTotalCards() {
		return this->myCards->size();
	}

	short getScore() {
		return this->score;
	}

	void removeCard(UNOCard * carta) {
		std::vector<UNOCard*>::iterator cardPos = std::find(this->myCards->begin(), this->myCards->end(), carta);
		this->myCards->erase(cardPos);
		this->cartasJugadas++;
	}

	bool tieneCarta(UNOCard * carta) {
		std::vector<UNOCard*>::iterator cardPos = std::find(this->myCards->begin(), this->myCards->end(), carta);
		return (cardPos != this->myCards->end());
	}

	short getTotalCJugadas() {
		return this->cartasJugadas;
	}

	void setTurno() {
		this->turn = !this->turn;
	}

	void setTurnoF() {
		this->turn = false;
	}

	bool esMiTurno() {
		return this->turn;
	}

	bool tieneCartas() {
		return (!this->myCards->empty());
	}

	bool getDijoUNO() {
		return this->dijoUNO;
	}

	void diceUno() {
		this->dijoUNO = true;
	}

	void setdijoUnoF() {
		dijoUNO = false;
	}

	UNOCard *  getCardToPlay(Point mouseXY) {
		for (std::vector <UNOCard*>::iterator it = myCards->begin(); it != myCards->end(); ++it) {
			if ((*it)->getAreaDibujo().Contains(mouseXY)) return (*it);
		}
		return NULL;
	}
	
	//desctructur
	~CJugadores(){
		delete this->myCards;
	}

};

class CPC : public CJugadores {
public:
	CPC(std::string name) :CJugadores(name) {
	};
	UNOCard* playCard(UNOCard * crrCard) {
		bool wild = false; UNOCard * card = NULL;

		for (std::vector<UNOCard*>::iterator it = this->myCards->begin(); it != myCards->end(); ++it) {
			if ((*it)->getColor() == crrCard->getColor() || ((*it)->getValue() == crrCard->getValue()
				&& (*it)->getEfecto() == crrCard->getEfecto() && (*it)->getValue() != 50) ||
				(crrCard)->getValue()==50 && (static_cast<CCartaEspecialWild*>(crrCard))->cambiaColor()==(*it)->getColor()) {
				card = *it;
				wild = false;
				this->removeCard(*it);
				break;
			}

			if ((*it)->getValue() == 50) {
				wild = true;
				card = *it;
			}
		};

		if (wild) 
			this->removeCard(card);

		if (getTotalCards() <= 1 ){
			diceUno();
		}
		else {
			setdijoUnoF();
		}

		return card;
	}
};