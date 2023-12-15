#pragma once

#include <fstream>
#include <vector>

using namespace std;

class Ex1
{
public:
	Ex1(string initReadFname, string initWriteFname, int cDataSizeI, int cDataSizeJ);
	~Ex1();
	friend ostream& operator << (std::ostream& os, const Ex1& ex1);
	friend istream& operator >> (std::istream& in, Ex1& ex1);

private:
	fstream in;
	fstream out;
	string readFname;
	string writeFname;
	vector<vector<int>> data;
	int dataSizeI;
	int dataSizeJ;
};