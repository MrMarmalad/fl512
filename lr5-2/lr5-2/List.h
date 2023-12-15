#pragma once

#include "GameRecord.h"

class List
{

private:
	struct listElem {
		GameRecord Data;
		listElem* prev = nullptr;
		listElem* next = nullptr;
	};
	int size;
	listElem* back;
	listElem* front;

	listElem* lastReadedElement;
	int lastReadedIndex;

public:
	List();
	List(GameRecord firstRecord);
	~List();

	//add new element to end
	void operator +=(GameRecord newElem);
	//delete element with index
	void operator -=(int elemIndexToDelete);

	int length() const;
	bool empty() const;
	int findElemByGenre(string genre);
	List* insertBefore(GameRecord newRecord, int insPlace);
	List* deleteFrom(int elemIndexToDelete);
	bool changeElem(int index, GameRecord changedRecord);
	bool clearList();



	GameRecord getElement(int index);
	GameRecord getElement();
	GameRecord getNext();
	GameRecord getPrev();

	friend void printList(List& listForPrinting);
	//
	friend ostream& operator <<(ostream& os, List& outList);
	friend istream& operator >> (std::istream& in, List& inList);

	void readFromBinary(string fname);
	void writeToBinary(string fname);
	void changeStringBinary(int index, GameRecord changedRecord, string fname);
	void deleteStringFromBinary(int index, string fname);
	int findFirstGameYearBinary(string fname);

};

List getRecordsYearsBefore(List checkedList, int beforeYear);
ostream& setup(ostream& stream);
