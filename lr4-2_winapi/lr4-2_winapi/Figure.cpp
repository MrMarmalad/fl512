#include <iostream>

#include "Figure.h"

using namespace std;

double Figure::area() {
	cout << "Вызов виртуального метода класса Figure" << endl;
	return 0;
}
void Figure::print() {
	cout << "Площадь " << this->StrFigureType << " = " << this->area() << endl;
}
string Figure::getStrFigureType() {
	return "Figure";
}