#pragma once
#include "UNOCard.h"

class CCarta: public UNOCard{
public:
	CCarta() {  };
	CCarta(short _value, CColor _cardColor): UNOCard(_value, _cardColor, NORMAL) {
	}
};

class CCartaEspecial: public UNOCard {
protected:
	CEfecto cardEffect;

public:
	CCartaEspecial() {};
	CCartaEspecial(short _value, CColor _cardColor, CEfecto _cardEffect): UNOCard(_value, _cardColor, _cardEffect) {
	}

};

class CCartaEspecialWild : public CCartaEspecial {
private:
	CColor choosenColor;

public:
	CCartaEspecialWild() {};
	CCartaEspecialWild(short _value, CEfecto _cardEffect): CCartaEspecial(_value, Negro, _cardEffect) {
		return;
	}

	void setNewColor(CColor _color) {
		this->choosenColor = _color;
	}

	CColor cambiaColor() {
		//ask user to change color (¿call visual part?)
		return this->choosenColor;
	}
};

