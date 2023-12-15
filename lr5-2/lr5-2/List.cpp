#include "List.h"

#include <iostream>
#include <iomanip>

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
	//if (lastReadedElement == nullptr || lastReadedIndex == -1) {
	//	cout << "Нет прочитанных ранее элементов" << endl;
	//}
	//else if (lastReadedElement->next == nullptr) {
	//	cout << "Это последний элемент" << endl;
	//}
	//else {
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

int List::findElemByGenre(string genre) {
	listElem* tmpElem = this->back;
	for (int currentIndex = 0; currentIndex < this->length(); currentIndex++) {
		if (tmpElem->Data.genre == genre) {
			return currentIndex;
		}
		tmpElem = tmpElem->next;
	}

	return -1;
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

void printList(List& listForPrinting)
{
	if (listForPrinting.empty()) {
		cout << "Структура данных пуста" << endl;
		return;
	}
	int index = 0;
	List::listElem* tmpElem = listForPrinting.back;
	while (tmpElem->next != nullptr) {
		tmpElem->Data.printRecord();
		tmpElem = tmpElem->next;
		index++;
	}

	tmpElem->Data.printRecord();
	cout << endl;
}

ostream& operator<<(ostream& os, List& outList)
{
	// TODO: insert return statement here
}

istream& operator>>(std::istream& in, List& inList)
{
	// TODO: insert return statement here
}

ostream& setup(ostream& stream)
{
	stream.setf(ios::left);
	stream << setw(50);
	return stream;
}
