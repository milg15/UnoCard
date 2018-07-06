#pragma once

using namespace System::Drawing;


//SOMETHING IS WRONG HERE FIX It
enum CColor { Rojo, Amarillo, Verde, Azul, Negro };
enum CEfecto { NORMAL, PASA, RETORNO, TOMA2, CAMBIA, TOMA4 };
#define CHEIGHT 195
#define CWIDTH 140


class CardInterface{
protected:
	short HEIGHT = 195;
	short WIDTH = 140;

	CardInterface() {
		
	};
	
};

