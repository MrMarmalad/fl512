#include <iostream>

#include "Figure.h"

using namespace std;

double Figure::area() {
	cout << "����� ������������ ������ ������ Figure" << endl;
	return 0;
}
void Figure::print() {
	cout << "������� " << this->StrFigureType << " = " << this->area() << endl;
}
string Figure::getStrFigureType() {
	return "Figure";
}