#include "CCarta.h"
enum Efecto { TOMA2, RETORNO, PASA, CAMBIA, TOMA4 };
const char * Efectos[] = { "TOMA2", "RETORNO", "PASA", "CAMBIA", "TOMA4"};

class CCartaEspecial : public CCarta {
private:
	Efecto efecto;

public:
	CCartaEspecial(short _value, Color _color, Efecto _efecto) :CCarta(_value, _color) {
		this->efecto = _efecto;
	};

	virtual void mostrarCarta() {
		std::cout << "Valor:" << this->value << "	Color: " << Colores[this->color] << "	Efecto: " << Efectos[this->efecto] << std::endl;
	}
};