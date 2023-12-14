#include <iostream>

#include "Rect.h"

using namespace std;

double Rect::area() {
	if (this->width == 0 || this->height == 0) {
		cout << "Минимум одна из сторон прямоугольника равна 0" << endl;
		return 0;
	}
	return this->width * this->height;
}

Rect::Rect() : width{ 0 }, height{ 0 }
{
	this->StrFigureType = "Rect";
}

Rect::Rect(double initWidth, double initHeight)
	:width{ initWidth }, height{ initHeight }
{
	this->StrFigureType = "Rect";
}

Rect::~Rect() {}