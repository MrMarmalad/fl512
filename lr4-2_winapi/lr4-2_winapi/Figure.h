#pragma once
#include <string>
class Figure {
public:
	double virtual area();
	void virtual print();
	std::string getStrFigureType();
protected:
	std::string StrFigureType = "Figure";
};
