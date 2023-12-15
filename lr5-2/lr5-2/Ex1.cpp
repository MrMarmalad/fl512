#include "Ex1.h"

Ex1::Ex1(string initReadFname, string initWriteFname,int cDataSizeI, int cDataSizeJ)
	: readFname{initReadFname}, writeFname{initWriteFname}, dataSizeI{cDataSizeI}, dataSizeJ{cDataSizeJ}
{
	this->in.open(initReadFname, fstream::in);
	this->out.open(initWriteFname, fstream::out | fstream::trunc);
	for (int i = 0; i < dataSizeI; i++) {
		this->data.push_back(vector<int>());
	}
	return;
}

std::ostream& operator << (std::ostream& os, const Ex1& ex1) {
	for (int i = 0; i < ex1.dataSizeI; i++) {
		for (int j = 0; j < ex1.data[i].size(); j++) {
			os << ex1.data[i][j] << "\t";
		}
		os << endl;
	}
	return os;
}
std::istream& operator >> (std::istream& in, Ex1& ex1) {
	vector <int> tmpVec;
	int tmpInt;
	for (int i = 0; i < ex1.dataSizeI; i++) {
		for (int j = 0; j < ex1.dataSizeJ; j++) {
			in >> tmpInt;
			tmpVec.push_back(tmpInt);
		}
		ex1.data.push_back(tmpVec);
		tmpVec = vector<int>();
	}
	return in;
}


Ex1::~Ex1()
{
	this->in.close();
	this->out.close();
}