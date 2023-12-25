#include "List.h"
#include "Utils.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;

//пустой список
List::List()
	: size{ 0 }, back{ nullptr }, front{ nullptr }, lastReadedElement{ nullptr }, lastReadedIndex{ -1 }
{
}

List::List(GameRecord firstRecord) :
	size{ 1 }, lastReadedElement{ nullptr }, lastReadedIndex{ -1 }
{
	listElem* newElem = new(listElem);
	newElem->Data = firstRecord;

	this->back = newElem;
	this->front = newElem;
}

List::~List()
{
}

int List::length() const {
	return this->size;
}

bool List::empty() const {
	return this->length() == 0;
}

List* List::insertBefore(GameRecord newRecord, int insPlace) {
	listElem* newElem;
	listElem* tmpElem;

	int elemCounter = 0;

	newElem = new(listElem);
	newElem->Data = newRecord;

	if (this->empty()) {
		this->back = newElem;
		this->front = newElem;
	}
	else {
		if (insPlace >= this->length()) {
			tmpElem = this->front;
			tmpElem->next = newElem;
			newElem->prev = tmpElem;
			this->front = newElem;
		}
		else if (insPlace <= 0) {
			tmpElem = this->back;
			tmpElem->prev = newElem;
			newElem->next = this->back;
			this->back = newElem;
		}
		else {
			tmpElem = this->back;
			while (elemCounter < insPlace) {
				tmpElem = tmpElem->next;
				elemCounter++;
			}
			newElem->next = tmpElem;
			newElem->prev = tmpElem->prev;
			tmpElem->prev->next = newElem;
			tmpElem->prev = newElem;

		}
	}
	this->size++;
	return this;
}

List* List::deleteFrom(int elemIndexToDelete) {
	listElem* tmpElem;
	if (this->length() == 0) return this;

	if (elemIndexToDelete <= 0) {
		if (this->back->next != nullptr) {
			tmpElem = this->back->next;
			delete this->back;
			this->back = tmpElem;
			this->back->prev = nullptr;
		}
		else {
			delete this->back;
		}

	}
	else if (elemIndexToDelete >= this->length() - 1) {
		tmpElem = this->front->prev;
		delete this->front;
		this->front = tmpElem;
		this->front->next = nullptr;
	}
	else {
		tmpElem = this->back;
		for (int recordCounter = 0; recordCounter < elemIndexToDelete; recordCounter++) {
			tmpElem = tmpElem->next;
		}
		tmpElem->next->prev = tmpElem->prev;
		tmpElem->prev->next = tmpElem->next;

		delete tmpElem;

	}
	this->size--;
	return this;
}

bool List::changeElem(int index, GameRecord changedRecord)
{
	this->insertBefore(changedRecord, index);
	this->deleteFrom(index + 1);
	return true;
}

bool List::clearList()
{
	while (!this->empty()) {
		this->deleteFrom(0);
	}
	this->back = nullptr;
	this->front = nullptr;
	this->lastReadedElement = nullptr;
	this->lastReadedIndex = -1;
	return true;
}

GameRecord List::getElement(int index)
{
	if (index > this->length() - 1 || index < 0) return GameRecord();
	if (lastReadedIndex == index) return this->lastReadedElement->Data;

	listElem* tmpRecord = this->back;
	for (int i = 0; i < index; i++) {
		tmpRecord = tmpRecord->next;
		this->lastReadedIndex = i;
	}
	this->lastReadedElement = tmpRecord;
	this->lastReadedIndex++;
	return tmpRecord->Data;
}

GameRecord List::getElement()
{
	return this->getElement(0);
}

GameRecord List::getNext()
{
	GameRecord retVal = GameRecord();
	if (lastReadedElement != nullptr &&
		lastReadedIndex != -1 &&
		lastReadedElement->next != nullptr)
	{
		lastReadedElement = lastReadedElement->next;
		lastReadedIndex++;
		retVal = lastReadedElement->Data;
	}
	return retVal;
}

GameRecord List::getPrev()
{
	GameRecord retVal = GameRecord();
	if (lastReadedElement == nullptr || lastReadedIndex == -1) {
		cout << "Нет прочитанных ранее элементов" << endl;
	}
	else if (lastReadedElement->prev == nullptr) {
		cout << "Это самый первый элемент" << endl;
	}
	else {
		lastReadedElement = lastReadedElement->prev;
		lastReadedIndex--;
		retVal = lastReadedElement->Data;
	}
	return retVal;
}

void List::operator -=(int elemIndexToDelete) {
	this->deleteFrom(elemIndexToDelete);
}

void List::operator +=(GameRecord newElem) {
	this->insertBefore(newElem, this->length());
}

List List::findElemsByGenre(string genre) {
	listElem* tmpElem = this->back;
	List result;
	for (int currentIndex = 0; currentIndex < this->length(); currentIndex++) {
		if (tmpElem->Data.genre == genre) {
			result += tmpElem->Data;
		}
		tmpElem = tmpElem->next;
	}

	return result;
}

List getRecordsYearsBefore(List checkedList, int beforeYear) {
	List filteredList;
	GameRecord tmpRecord;

	if (checkedList.empty()) {
		cout << "Список пустой" << endl;
	}
	else {
		tmpRecord = checkedList.getElement();
		while (!tmpRecord.empty())
		{
			if (tmpRecord.year < beforeYear) {
				filteredList.insertBefore(tmpRecord, filteredList.length());
			}
			tmpRecord = checkedList.getNext();
		}
	}
	return filteredList;
}

void printList(List& listForPrinting, bool debugInfo = false)
{
	if (listForPrinting.empty()) {
		cout << "Структура данных пуста" << endl << endl;
		return;
	}
	int index = 0;
	GameRecord tmpElem;

	if (debugInfo) {
		cout << "Вывод списка" << endl;
		cout << "Back " << listForPrinting.back << "\tFront " << listForPrinting.front << endl;
	}
	
	auto tmpListEl = listForPrinting.back;
	while (tmpListEl != nullptr) {
		if (debugInfo) {
			cout << tmpListEl->prev << endl;
		}

		cout << tmpListEl->Data << endl << endl;
		
		if (debugInfo) {
			cout << tmpListEl->next << endl << endl;
		}
			
		tmpListEl = tmpListEl->next;
	}
	cout << endl;
}

ostream& operator<<(ostream& os, List& outList)
{
	outList.getElement(0);
	GameRecord tmpRecord = outList.getElement(0);
	while (!tmpRecord.empty()) {
		setup(os) << tmpRecord;
		tmpRecord = outList.getNext();
	}
	return os;
}

istream& operator>>(std::istream& in, List& inList)
{
	GameRecord tmpRecord;

	while (!in.eof()) {
		in >> tmpRecord;
		inList.insertBefore(tmpRecord, inList.length());
	}
	return in;
}

void List::writeToBinary(string fname)
{
	fstream outStream;
	stringstream ss;

	outStream.open(fname, ios::out | ios::binary | ios::trunc);
	if (!outStream) {
		cout << "Ошибка открытия файла:" + fname << endl;
		return;
	}

	GameRecord tmpRecord = this->getElement(0);
	string writeString;

	for (int i = 0; i < this->length(); i++) {
		tmpRecord = this->getElement(i);
		ss << tmpRecord;
		if (i < this->length() - 1) {
			ss << endl;
		}
	}
	writeString = ss.str();
	outStream.write(writeString.c_str(), writeString.size());
	outStream.close();
}

void List::readFromBinary(string fname)
{
	std::fstream in;
	in.open(fname, ios::in | ios::binary);
	
	if (!in) {
		cout << "Ошибка открытия файла:" + fname << endl;
		return;
	}
	
	GameRecord tmpRec;
	while (!in.eof()) {
		in >> tmpRec;
		this->insertBefore(tmpRec, this->length());
	}
	in.close();
}

void List::changeStringBinary(int index, GameRecord changedRecord, string fname)
{
	this->changeElem(index, changedRecord);
	this->writeToBinary(fname);
}

void List::deleteStringFromBinary(int index, string fname)
{
	this->deleteFrom(index);
	this->writeToBinary(fname);
}

GameRecord List::findFirstGameYearBinary(string fname)
{
	this->clearList();
	this->readFromBinary(fname);

	GameRecord tmpRecord = this->getElement(0);
	GameRecord retVal = this->getElement(0);
	//int minYear = tmpRecord.year;

	while (!tmpRecord.empty()) {
		if (tmpRecord < retVal) {
			retVal = tmpRecord;
		}
		tmpRecord = this->getNext();
	}
	return retVal;
}

void List::swap(int indexF, int indexS) {
	auto tmpRecord = this->getElement(indexF);
	this->changeElem(indexF, this->getElement(indexS));
	this->changeElem(indexS, tmpRecord);
}

void List::sort(bool asc) {
	// Сортировка массива пузырьком
	for (int i = 0; i < this->length(); i++) {
		for (int j = 0; j < this->length() - (i + 1); j++) {
			if (asc) {
				if (this->getElement(j) > this->getElement(j + 1)) {
					this->swap(j, j + 1);

				}
			}
			else {
				if (this->getElement(j) < this->getElement(j + 1)) {
					this->swap(j, j + 1);
				}
			}

		}
	}
}

bool List::writeToFile(string fname)
{
	fstream out;
	stringstream ss;
	GameRecord tmpRecord;

	out.open(fname, ios::out);
	if (!out.is_open()) {
		cout << "Невозможно открыть файл " << fname << endl;
		return false;
	}

	for (int i = 0; i < this->length(); i++) {
		tmpRecord = this->getElement(i);
		ss << tmpRecord;
	}
	out << ss.str();
	return true;
}

bool List::readFromFile(string fname) 
{
	fstream in;
	GameRecord tmpRecord;
	

	in.open(fname, ios::in);
	if (!in.is_open()) {
		cout << "Невозможно открыть файл " << fname << endl;
		return false;
	}

	while (!in.eof()) {
		in >> tmpRecord;
		*this += tmpRecord;
	}

	return true;
}