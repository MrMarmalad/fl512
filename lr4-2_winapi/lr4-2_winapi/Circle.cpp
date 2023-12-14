#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <typeinfo>

#include "Circle.h"

using namespace std;

double Circle::area() {
	if (this->radius <= 0) {
		cout << "Радиус = 0" << endl;
		return 0;
	}
	return M_PI * (this->radius * this->radius);
}

Circle::Circle() : radius{ 0 }
{
	this->StrFigureType = typeid(*this).name();
}

Circle::Circle(double initRadius) : radius{ initRadius }
{
	this->StrFigureType = typeid(*this).name();
}

Circle::~Circle() {}