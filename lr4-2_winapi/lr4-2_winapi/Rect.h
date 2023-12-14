#pragma once
#include "Figure.h"
class Rect : public Figure
{
public:
	Rect();
	Rect(double width, double height);
	~Rect();
	double area();
private:
	double width;
	double height;
};

