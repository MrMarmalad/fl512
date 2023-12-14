#pragma once
#include "Figure.h"
class Circle : public Figure
{
public:
	Circle();
	Circle(double initRadius);
	~Circle();
	double area();
private:
	double radius;
};

