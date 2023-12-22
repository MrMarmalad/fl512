#pragma once

#include "GameRecord.h"
#include "List.h"

class Queue
{
public:
	Queue();
	Queue(GameRecord firstRecord);
	Queue(List initList);
	~Queue();
	bool push(GameRecord newElem);
	GameRecord pop();
	GameRecord findElemByGenre(string genre);
	bool clearQueue();

	void operator+=(GameRecord newRecord);
	Queue& operator--();
	Queue operator--(int);

	friend Queue getRecordsYearsBefore(Queue checkedQueue, int beforeYear);
	friend void printQueue(Queue& queueForPrinting);
	//
	friend ostream& operator << (ostream& os, Queue& outQueue);
	friend istream& operator >> (std::istream& in, Queue& inQueue);

	void readFromBinary(string fname);
	void writeToBinary(string fname);
	void changeStringBinary(int index, GameRecord changedRecord, string fname);
	void deleteStringFromBinary(int index, string fname);

	GameRecord findFirstGameYearBinary(string fname);


	void sort(bool asc);
	void swap(int indexF, int indexS);

private:
	List queueElems;
};

