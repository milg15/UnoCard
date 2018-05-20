#include <vector>
#include <string>
#include "CMazoCartas.h"

using namespace std;
class CJugador{
private:
	friend class Juego; //Temporal¿?
	string nombre;
	short score;
	vector <CCarta*> * mazo;


	void mostrarMano() {
		cout << "Cartas de " << this->nombre << endl;
		for (size_t i = 0; i < this->mazo->size(); i++)
			this->mazo->at(short(i))->mostrarCarta();
		/*for (auto t = mazo->begin(); t != mazo->end(); ++t) {
		(*t)->mostrarCarta();
		}*/
	}
public:
	CJugador(string _nombre) {
		this->nombre = _nombre;
		this->mazo = new vector <CCarta*>;
	}

	string getNombre() {
		return this->nombre;
	}

	void agregarCarta(CCarta * carta) {
		this->mazo->push_back(carta);
	}

	CCarta* jugar() {
		//mostrar opciones de cartas.. seleccionar una valida
		//verificar estado de juego... funcion validar()
		return this->mazo->back();
	}
};

