#include <iostream>

#include "Triangle.h"

using namespace std;

double Triangle::area() {
	double hP = 0;
	for (auto side : this->sides)
	{
		if (side == 0) {
			cout << "Одна из сторон треугольника равна 0" << endl;
			return 0;
		}
		hP += side / 2;
	}
	return sqrt(hP * (hP - this->sides[0]) * (hP - this->sides[1]) * (hP - this->sides[2]));
}

Triangle::Triangle() : Circle()
{
	this->sides = { 0, 0, 0 };

}

Triangle::Triangle(array<double, 3> initSides) :
	Circle(),
	sides{ initSides }
{}

Triangle::~Triangle() {}