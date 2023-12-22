#pragma once

#include <string>
#include <iostream>
using namespace std;

struct GameRecord
{
	string name = "";
	string genre = "";
	int year = 0;

	// ���� strict == false, �� ������ ���� ����� ����������� ��� ������� ��������� ��������
	bool equal(GameRecord testRecord, bool strictEq = true) const;

	bool empty() const;

	void printRecord() const;

	bool operator > (const GameRecord& comparedRec) const;

	bool operator < (const GameRecord& comparedRec) const;

	
};

ostream& operator << (ostream& os, const GameRecord& gr);

std::istream& operator >> (std::istream& in, GameRecord& gm);