#pragma once
#include "Dealer.h"
//need to add efecto de cartas.

typedef System::Windows::Forms::MessageBox MSHOW;

class CJuego {
private:
	//0 es derecha - 1 es izquierda
	bool direccion, changeC, changed;
	CDealer * dealer;
	UNOCard * topCard;
	CJugadores * winner;
	vector <CJugadores*>* crrPlayers;

	//THIS NEEDS TO WORK ALWAYS YOU <3
	bool canPlay(UNOCard * topCard, UNOCard* playingCard) {
		if (topCard->getColor() == playingCard->getColor() || (topCard->getEfecto() == playingCard->getEfecto() &&
			topCard->getValue() == playingCard->getValue() && topCard->getValue() != 50))
			return true;
		else if (topCard->getValue() == 50)
			return static_cast<CCartaEspecialWild*>(topCard)->cambiaColor() == playingCard->getColor();
		else if (playingCard->getValue() == 50)
			return true;

		return false;
	};
	
	
	
public:
	bool playableCard(CJugadores * player) {
		for (short i = 0; i < player->myCards->size(); i++) {
			if (canPlay(topCard, player->myCards->at(i)))
				return true;
		};
		return false;
	};

	CJuego(vector<CJugadores*> _crrPlayers) {
		dealer = new CDealer();
		direccion = changed = changeC =  false;
		topCard = NULL;
		winner = NULL;

		this->crrPlayers = new vector <CJugadores*>;
		for (short i = 0; i < _crrPlayers.size(); i++)
			crrPlayers->push_back(_crrPlayers.at(i));
	};

	//numero del jugador en turno para mostrarlo en pantalla
	short crrPlayer() {
		for (short i = 0; i < crrPlayers->size(); i++)
			if (crrPlayers->at(i)->esMiTurno()) return (i + 1);
		return 0;
	};
	bool getChangeColor() {
		return this->changeC;
	}
	void setChangeColor(bool _changeC) {
		changeC = _changeC;
	}


	CJugadores* getDealer() {
		return this->dealer->getDealer();
	};

	void IniciarMatch(BufferedGraphics ^ buffer, Bitmap ^ cardBmp, Rectangulo size, Point mousePoint) {
		dealer->turnos(*crrPlayers);
		dealer->sieteCIniciales(*crrPlayers);
		centerCards(buffer, cardBmp, size);
		this->MostrarCartas(buffer, cardBmp, mousePoint);
		idenDealer(buffer);
		if (topCard->getValue() == 50) {
			System::Random r;
			static_cast<CCartaEspecialWild*>(topCard)->setNewColor(static_cast<CColor>(r.Next(0, 5)));
		};

		if (topCard->getEfecto() != NORMAL) {
			checkEspecialCard(topCard->getEfecto(), this->crrPlayers->at(this->crrPlayer() - 1));
		};
		return;
	};

	bool crrMatch(BufferedGraphics ^ buffer, Bitmap ^ cardBmp, Rectangulo size, 
		Point mousePoint, bool click) {
		if (this->dealer->emptyDeck()) 		//tell the user ¿?
			this->dealer->suffleMazo();

		if (endGame())
			return false;

		if (click) {
			this->playersTurn(mousePoint);
		}
		else
			PCTurn();

		centerCards(buffer, cardBmp, size);
		mostarCrrTurno(buffer);
		this->MostrarCartas(buffer, cardBmp, mousePoint);
		idenDealer(buffer);
		
		changed = false;
		return true;
	};

	//modificar !i por true para mostrar todas las cartas
	void mostarCrrTurno(BufferedGraphics ^ buffer) {
		short side = this->crrPlayers->at(crrPlayer() - 1)->side;

		Point pnt = Point(this->crrPlayers->at(crrPlayer()-1)->middle.X + ((side == 1 || side == 2) ? (CWIDTH*0.4)+10: -26),
			this->crrPlayers->at(crrPlayer() - 1)->middle.Y + (CHEIGHT*0.4 * ((side == 0 || side == 3) ? -1 : 1)));

		buffer->Graphics->DrawRectangle(gcnew System::Drawing::Pen(Color::Black),
			Rectangulo(pnt, System::Drawing::Size(25, 25)));
		buffer->Graphics->DrawString("T", gcnew System::Drawing::Font("Arial Black", 16),
			gcnew System::Drawing::SolidBrush(Color::Black), pnt);
	}

	void idenDealer(BufferedGraphics ^ buffer) {
		short side = this->dealer->getDealer()->side;

		Point pnt = Point(this->dealer->getDealer()->middle.X + ((side == 1 || side == 2) ? CWIDTH + 26 : -26),
			this->dealer->getDealer()->middle.Y + ((26*((side == 0 || side == 3) ? -1 : 1))));

		buffer->Graphics->DrawEllipse(gcnew System::Drawing::Pen(Color::Black),
									Rectangulo(pnt, System::Drawing::Size(25, 25)));
		buffer->Graphics->FillEllipse(gcnew System::Drawing::SolidBrush(Color::Blue), 
									Rectangulo (pnt, System::Drawing::Size(25,25)));
		buffer->Graphics->DrawString("D", gcnew System::Drawing::Font("Arial Black", 16),
									gcnew System::Drawing::SolidBrush(Color::Black), pnt);
	
	}
	void MostrarCartas(BufferedGraphics ^ buffer, Bitmap ^ cardBmp, Point mousePoint) {
		//modificar para que tome cualquier cantidad de cartas

		//FIX UBICACION JUGADOR
		for (short i = 0; i < crrPlayers->size(); i++) {
			short side = crrPlayers->at(i)->side;
			short x = crrPlayers->at(i)->middle.X;
			short y = crrPlayers->at(i)->middle.Y;

			//dealer
			if (side == 0 || side == 2) {
				if (this->crrPlayers->at(i)->myCards->size() < 10)
					x -= (CWIDTH / ((side == 0 && crrPlayers->size() == 5 || crrPlayers->size() != 5) ? 5 : 3))
					*(crrPlayers->at(i)->getTotalCards() / 2) + (side == 0 ? 15 : 5);
				else
					x -= (CWIDTH / ((side == 0 && crrPlayers->size() == 5 || crrPlayers->size() != 5) ? 5 : 3))
					*(crrPlayers->at(i)->getTotalCards() / 2) + (side == 0 ? 20 : 10);
			}
			else
				y -= (CHEIGHT / 5)*(crrPlayers->at(i)->getTotalCards() / 2) - 8;

			for (short j = 0; j < crrPlayers->at(i)->getTotalCards(); j++) {
				UNOCard * card = crrPlayers->at(i)->myCards->at(j);
				card->setXY(Point(x, y));

				if (side == 0 && card->getAreaDibujo().Contains(mousePoint))
					card->hoverUP();

				card->dibujar(buffer, cardBmp, !i);
				if (side == 0 || side == 2 && side != 1) {
					if(this->crrPlayers->at(i)->myCards->size()<10)
						x += CWIDTH / (crrPlayers->size() == 5 ? (side == 0 ? 2.5 : 4) : (side == 0 ? 2.5 : 3));
					else
						x += CWIDTH / (crrPlayers->size() == 5 ? (side == 0 ? 2.5 : 5) : (side == 0 ? 2.5 : 4));
				}
				else
					if (this->crrPlayers->at(i)->myCards->size()<10)
						y += CHEIGHT / 4.5;
					else
						y += CHEIGHT / 5;

			};
		};
	};

	void posJugadores(Rectangulo size) {
		crrPlayers->at(0)->side = 0; crrPlayers->at(0)->middle = Point((size.Width / 2) - (CWIDTH / 2), size.Height - 130);
		if (crrPlayers->size() == 5) {
			crrPlayers->at(1)->middle = Point(50, size.Height / 2); crrPlayers->at(1)->side = 1;
			crrPlayers->at(2)->middle = Point((size.Width / 4), 30); crrPlayers->at(2)->side = 2;
			crrPlayers->at(3)->middle = Point((size.Width / 4 * 3), 30); crrPlayers->at(3)->side = 2;
			crrPlayers->at(4)->middle = Point(size.Width - 50 - (CWIDTH / 2), size.Height / 2); crrPlayers->at(4)->side = 3;
		}
		else if (crrPlayers->size() == 4) {
			crrPlayers->at(1)->middle = Point(50, size.Height / 2); crrPlayers->at(1)->side = 1;
			crrPlayers->at(2)->middle = Point((size.Width / 2) - (CWIDTH / 2) - 15, 30); crrPlayers->at(2)->side = 2;
			crrPlayers->at(3)->middle = Point(size.Width - 50 - (CWIDTH / 2) - 15, size.Height / 2); crrPlayers->at(3)->side = 3;
		}
		else if (crrPlayers->size() == 3) {
			crrPlayers->at(1)->middle = Point(50, size.Height / 2); crrPlayers->at(1)->side = 1; crrPlayers->at(1)->side = 1;
			crrPlayers->at(2)->middle = Point(size.Width - 50 - (CWIDTH / 2), size.Height / 2); crrPlayers->at(2)->side = 3;
		}
		else if (crrPlayers->size() == 2) {
			crrPlayers->at(1)->middle = Point((size.Width / 2) - (CWIDTH / 2), 30); crrPlayers->at(1)->side = 2;
		}
	};

	//funcionalidad especial... CAmbia cartas
	void cambiaCartas(CJugadores * crr, CJugadores * playSwitch) {
		vector <UNOCard*> temp;

		while(!crr->myCards->empty()){
			temp.push_back(crr->myCards->back());
			crr->myCards->pop_back();
		}
		
		while (!playSwitch->myCards->empty()) {
			crr->myCards->push_back(playSwitch->myCards->back());
			playSwitch->myCards->pop_back();
		}

		while (!temp.empty()) {
			playSwitch->myCards->push_back(temp.back());
			temp.pop_back();
		}
	}

	//coloca la cartas centrales y le doy al juego la carta onTop
	void centerCards(BufferedGraphics ^ buffer, Bitmap ^ cardBmp, Rectangulo size) {
		short x = size.Width / 2, y = size.Height / 2;
		if (topCard == NULL) {
			topCard = dealer->getCard();
			while (topCard->getValue()==50 && topCard->getEfecto==CAMBIA) {
				dealer->returnCard(topCard);
				topCard = dealer->getCard();
			}
		}
		topCard->setXY(Point(x, y - CHEIGHT / 3));
		topCard->dibujar(buffer, cardBmp, true);

		if (dealer->getMazo()->empty()) dealer->suffleMazo();
		UNOCard * card = dealer->getMazo()->top();
		card->setXY(Point(x - CWIDTH / 2, y - CHEIGHT / 3));
		card->dibujar(buffer, cardBmp, false);
	};

	bool endGame() {
		for (short i = 0; i < crrPlayers->size(); i++) {
			//&&
			/*crrPlayers->at(i)->getDijoUNO()*/
			if (crrPlayers->at(i)->myCards->empty()) {
				winner = crrPlayers->at(i);
				return true;
			};
		};
		return false;
	};;

	void drawNCards(CJugadores * player, short n) {
		for (short i = 0; i < n; i++)
			player->agregarCarta(dealer->getCard());
		nextTurn();
	};

	/*Un jugador en su turno podrá decidir no jugar una de las cartas de su mano, aunque
	esta coincida en número, color o símbolo con la última de la pila de descarte. 
	En este caso, debe robar una carta del montón, pudiéndola jugar inmediatamente. 
	Después de robar, sólo puede jugar la carta que ha robado, le está prohibido 
	descartarse de unas de las cartas que ya tenía en la mano
	*/
	
	bool getDrewCardP() {
		return this->drewCard;
	}
	//validar que no termine con carta especial¿?
	bool drewCard = false;
	void playersTurn(Point mousePoint) {
		if (dealer->getMazo()->empty()) dealer->suffleMazo();
		if (this->crrPlayers->at(0)->esMiTurno()) {
			//solo puede tomar una 
			if (dealer->getMazo()->top()->getAreaDibujo().Contains(mousePoint)
				&& !drewCard) {
				drawCard();
				drewCard = true;
				return;
			};

			//set UNO a falso
			if (this->crrPlayers->at(0)->getDijoUNO() &&
				this->crrPlayers->at(0)->myCards->size() > 2)
				this->crrPlayers->at(0)->setdijoUnoF();


			UNOCard * card = crrPlayers->at(0)->getCardToPlay(mousePoint);
			if (card != NULL && canPlay(topCard, card)) {
				dealer->returnCard(topCard);
				topCard = card;
				crrPlayers->at(0)->removeCard(card);

				if (card->getValue() == 50)
					changeC = true;

				nextTurn();
				//help
				checkEspecialCard(topCard->getEfecto(), crrPlayers->at(crrPlayer() - 1));
			};
		};
	};
	
	//carga más cartas de las que deberia.
	void PCTurn() {
		for (short i = 1; i < crrPlayers->size(); i++) {
			if (crrPlayers->at(i)->esMiTurno() && !changeC) {
				//verifica que el jugador allá dicho uno
				short j = direccion ?
					(i - 1 == -1 ? crrPlayers->size() - 1 : i - 1) :
					(i == crrPlayers->size() - 1 ? 0 : i + 1);

				if (!j && crrPlayers->at(j)->myCards->size() <= 1 && !crrPlayers->at(j)->getDijoUNO()) {
					MSHOW::Show("El BOT " + i + "ha dicho UNO \n en lugar del jugador\n cargue dos.");
					this->drawNCards(crrPlayers->at(j), 2);
				}

				drewCard = false;
				UNOCard *card = (static_cast<CPC*>(crrPlayers->at(i)))->playCard(topCard);
				if (card == NULL) {
					drawCard();
					card = (static_cast<CPC*>(crrPlayers->at(i)))->playCard(topCard);
					if (card == NULL)
						break;
				}

				dealer->returnCard(topCard);
				topCard = card;
				nextTurn();

				//check error!!!
				checkEspecialCard(topCard->getEfecto(), crrPlayers->at(crrPlayer() - 1));
			};
		};
	};

	void nextTurn() {
		for (short i = 0; i < crrPlayers->size();i++) {
			if (crrPlayers->at(i)->esMiTurno()) {
				crrPlayers->at(i)->setTurno();

				crrPlayers->at(!direccion?
					(i-1 == -1 ? crrPlayers->size() - 1 : i - 1):
					(i == crrPlayers->size() - 1 ? 0 : i + 1))->setTurno();
				break;
			};
		};
	};

	void setDrewCard() {
		this->drewCard = true;
	}

	void drawCard() {
		bool canPlay = false; 
		for (std::vector<CJugadores*>::iterator it = crrPlayers->begin(); it != crrPlayers->end();++it) {
			if ((*it)->esMiTurno()) {
				UNOCard * card = dealer->getCard();
				(*it)->agregarCarta(card);

				canPlay = this->canPlay(topCard, card);
				break;
			};
		};
		if (!canPlay || (drewCard && crrPlayer()-1 == 0))
			nextTurn();
	};

	void changeColor(short n) {
		//Selecciona nuevo color cause wild card
		System::Random r;
		if (changeC && n != -1)
			return;

		else {
			if(changeC)
				static_cast<CCartaEspecialWild*>(topCard)->setNewColor(static_cast<CColor>(n));
			else
				static_cast<CCartaEspecialWild*>(topCard)->setNewColor(static_cast<CColor>(r.Next(0, 4)));

			System::String^crrColor;
			if (static_cast<CCartaEspecialWild*>(topCard)->cambiaColor() == Rojo)
				crrColor = gcnew System::String("Rojo");
			else if (static_cast<CCartaEspecialWild*>(topCard)->cambiaColor() == Verde)
				crrColor = gcnew System::String("Verde");
			else if (static_cast<CCartaEspecialWild*>(topCard)->cambiaColor() == Azul)
				crrColor = gcnew System::String("Azul");
			else
				crrColor = gcnew System::String("Amarillo");

			MSHOW::Show("El nuevo color es\n" + crrColor);
		}

	};

	//Comportamineto si la carta on TOP es especialed ( funciona for the most part)
	void checkEspecialCard(CEfecto efecto, CJugadores * jugador) {
		switch (efecto) {
		case(TOMA2): {
			drawNCards(jugador, 2);
			break;
		};
		case(TOMA4): {
			changeColor(-1);
			drawNCards(jugador, 4);
			break;
		};
		case(RETORNO): {
			direccion = !direccion;
			MSHOW::Show("Cambio de sentido " + (direccion ? "<-" : "->"));
			nextTurn();
			if (crrPlayers->size() != 2)
				nextTurn();
			break;
		};
		case(PASA): {
			nextTurn();
			break;
		};
		case (CAMBIA): {
			changeColor(-1);
			break;
		};
		default:
			break;
		};
		
	};

	UNOCard * getTopCard() {
		return this->topCard;
	};

	void placeCard(UNOCard * card) {
		topCard = card;
	};

	void calculaPuntaje() {
		//quitar carta de los jugadores y calcular puntaje del ganador
		for (short i = 0; i < crrPlayers->size(); i++) {
			short cardSize = crrPlayers->at(i)->myCards->size();
			for (short j = cardSize-1; j >=0; j--) {
				winner->addScore(crrPlayers->at(i)->myCards->at(j)->getValue());

				crrPlayers->at(i)->setdijoUnoF();
				crrPlayers->at(i)->setTurnoF();
				UNOCard * card = crrPlayers->at(i)->myCards->at(j);
				crrPlayers->at(i)->removeCard(card);
				dealer->returnCard(card);
			}
		};
	};

	~CJuego(){
		//calcular los puntos ¿'?
		calculaPuntaje();

		delete dealer;
		delete crrPlayers;
	};
};;