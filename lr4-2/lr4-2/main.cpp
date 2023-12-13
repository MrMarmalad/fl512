//�2
//������� ����� - "������", ����������� ����� - "�������" (��� ����������, ���������� real).
//����������� ������ - "����������", "�������������", "�����������"
//���������:
//����������: ������(real)
//������������� : ������(real), ������(real)
//����������� : ����� ������(������ �� 3 - � ��������� ���� real)
//��������� "��������" ������ ������ �� ������.
//��������� "�����" ������� �������� ������� ���������� �� ������.


#define _USE_MATH_DEFINES
#include <iostream>
#include <array>
#include <math.h>
#include <typeinfo>
#include <string>


using namespace std;

class Figure {
public: 
	double virtual area() {
		cout << "����� ������������ ������ ������ Figure" << endl;
	}
	void virtual print() {
		cout << "������� " << this->StrFigureType << " = " << this->area() << endl;
	}
	string getStrFigureType() {
		return "Figure";
	}
protected:
	string StrFigureType = "Figure";
};

class Circle : public Figure
{
public:
	Circle();
	Circle(double initRadius);
	~Circle();
	double area() {
		if (this->radius <= 0) {
			cout << "������ = 0" << endl;
			return 0;
		}
		return M_PI * (this->radius * this->radius);
	}
private:
	double radius;
};

Circle::Circle() : radius{ 0 } 
{
	this->StrFigureType = typeid(*this).name();
}

Circle::Circle(double initRadius): radius{initRadius} 
{
	this->StrFigureType = typeid(*this).name();
}

Circle::~Circle() {}

class Rectangle: public Figure
{
public:
	Rectangle();
	Rectangle(double width, double height);
	~Rectangle();
	double area() {
		if (this->width == 0 || this->height == 0) {
			cout << "������� ���� �� ������ �������������� ����� 0" << endl;
			return 0;
		}
		return this->width * this->height;
	}
private:
	double width;
	double height;
};

Rectangle::Rectangle() : width{0}, height{0}
{
	this->StrFigureType = "Rectangle";
}

Rectangle::Rectangle(double initWidth, double initHeight)
	:width{initWidth}, height{initHeight} 
{
	this->StrFigureType = "Rectangle";
}

Rectangle::~Rectangle() {}

class Triangle: public Circle, public Rectangle
{
public:
	Triangle();
	Triangle(array<double, 3> initSides);
	~Triangle();
	double area() {
		double hP = 0;
		for (auto side : this->sides)
		{
			if (side == 0) {
				cout << "���� �� ������ ������������ ����� 0" << endl;
				return 0;
			}
			hP += side / 2;
		}
		return sqrt(hP * (hP - this->sides[0]) * (hP - this->sides[1]) * (hP - this->sides[2]));
	}
private:
	array<double, 3> sides;
};

Triangle::Triangle(): Circle()
{
	this->sides = { 0, 0, 0 };
	
}

Triangle::Triangle(array<double, 3> initSides) : 
	Circle(),
	sides{initSides}
{}

Triangle::~Triangle() {}



int main() {
	return 0;
}