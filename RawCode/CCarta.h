//inlcude for somthing
#include <iostream>

enum Color { Rojo, Azul, Verde, Amarillo, Negro };
const char * Colores[5] = {"Rojo\0", "Azul\0", "Verde\0", "Amarillo\0", "Negro\0"};

class CCarta {
protected:
	short value;
	Color color;

public:
	CCarta(short _value, Color _color) {
		this->value = _value;
		this->color = _color;
	};

	virtual void mostrarCarta() {
		std::cout << "Valor:" << this->value << "		Color: " << Colores[this->color] << std::endl;
	}

	short getValue() {
		return this->value;
	}
};