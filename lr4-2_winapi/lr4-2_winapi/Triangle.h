#pragma once
#include <array>

#include "Circle.h"
#include "Rect.h"

class Triangle : public Circle, public Rect
{
public:
	Triangle();
	Triangle(std::array<double, 3> initSides);
	~Triangle();
	double area();
private:
	std::array<double, 3> sides;
};

