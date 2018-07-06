#pragma once
#include "CardInterface.h"

typedef System::Drawing::Rectangle Rectangulo;

class UNOCard : public CardInterface {
private:
	short value;
	Point xy;
	CColor cardColor;
	CEfecto cardEffect;
	Rectangulo areaDibujo, areaSubImagen;

public:
	UNOCard() {};
	UNOCard(short _value, CColor _cardColor, CEfecto _cardEffect){
		this->cardColor = _cardColor;
		this->cardEffect = _cardEffect;
		this->value = _value;

		short width = WIDTH * (this->value + (3));
		if (_cardEffect>=CAMBIA)
			width = WIDTH * (13);
		else if (_cardEffect>NORMAL) 
			width = WIDTH * (this->cardEffect-1);

		areaSubImagen = Rectangulo(width, HEIGHT*(this->cardColor!=Negro ? 
			this->cardColor:(this->getEfecto()==TOMA4)), WIDTH, HEIGHT);
	}

	short getValue() {
		return this->value;
	}

	CColor getColor() {
		return this->cardColor;
	}

	CEfecto getEfecto() {
		return this->cardEffect;
	}

	void setXY(Point _xy) {
		this->xy = _xy;
	}

	void moveUP(Point mousePo) {
		this->xy = mousePo;
	}

	void hoverUP() {
		this->xy.Y -= 10;
	}

	Rectangulo getAreaSubImagen() {
		return this->areaSubImagen;
	}

	Rectangulo getAreaDibujo(){
		return this->areaDibujo;
	}

	void dibujar(BufferedGraphics ^ buffer, Bitmap^bmp, bool up) {
		areaDibujo = Rectangulo(xy.X,xy.Y, WIDTH*0.5, HEIGHT*0.5);
	
		buffer->Graphics->DrawImage(bmp, areaDibujo, 
			up?areaSubImagen: Rectangulo(WIDTH *13, HEIGHT*3, WIDTH, HEIGHT) , GraphicsUnit::Pixel);
	}
};