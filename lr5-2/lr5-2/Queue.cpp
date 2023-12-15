#include "Queue.h"
#include "List.h"

Queue::Queue()
	:queueElems{ List() }
{}

Queue::Queue(GameRecord firstRecord)
	:queueElems{ List(firstRecord) }
{}

Queue::Queue(List initList)
	:queueElems{ initList }
{}

Queue::~Queue()
{}

bool Queue::clearQueue()
{
	this->queueElems.clearList();
	return true;
}

bool Queue::push(GameRecord newElem)
{
	this->queueElems.insertBefore(newElem, 0);
	return true;
}

GameRecord Queue::pop()
{
	GameRecord retVal = GameRecord();
	retVal = this->queueElems.getElement(this->queueElems.length() - 1);
	this->queueElems.deleteFrom(this->queueElems.length() - 1);
	return retVal;
}

GameRecord Queue::findElemByGenre(string genre)
{
	GameRecord tmpRecord;
	GameRecord retVal;
	List tmpList = List();
	for (int i = 0; i < this->queueElems.length(); i++) {
		tmpRecord = this->pop();
		if (tmpRecord.genre == genre) {
			retVal = tmpRecord;
		}
		tmpList.insertBefore(tmpRecord, tmpList.length());
	}
	this->queueElems = tmpList;
	return retVal;
}

void Queue::operator+=(GameRecord newRecord)
{
	this->push(newRecord);
}

Queue& Queue::operator--()
{
	this->pop();
	return *this;
}

Queue Queue::operator--(int) {
	--*this;
	return *this;
}

void Queue::readFromBinary(string fname)
{
	this->queueElems.readFromBinary(fname);
}

void Queue::writeToBinary(string fname)
{
	this->queueElems.writeToBinary(fname);
}

void Queue::changeStringBinary(int index, GameRecord changedRecord, string fname)
{
	this->queueElems.changeStringBinary(index, changedRecord, fname);
}

void Queue::deleteStringFromBinary(int index, string fname)
{
	this->queueElems.deleteStringFromBinary(index, fname);
}

int Queue::findFirstGameYearBinary(string fname)
{
	return this->queueElems.findFirstGameYearBinary(fname);
}

void printQueue(Queue& queueForPrinting)
{
	printList(queueForPrinting.queueElems);
}

ostream& operator<<(ostream& os, Queue& outQueue)
{
	os << outQueue.queueElems;
	return os;
}

istream& operator>>(std::istream& in, Queue& inQueue)
{
	in >> inQueue.queueElems;
	return in;
}

Queue getRecordsYearsBefore(Queue checkedQueue, int beforeYear) {
	List tmpList = getRecordsYearsBefore(checkedQueue.queueElems, beforeYear);
	return Queue(tmpList);
}
