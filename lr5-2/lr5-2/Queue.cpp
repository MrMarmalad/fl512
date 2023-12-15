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

void printQueue(Queue& queueForPrinting)
{
	printList(queueForPrinting.queueElems);
}

ostream& operator<<(ostream& os, Queue& outQueue)
{
	// TODO: insert return statement here
}

istream& operator>>(std::istream& in, Queue& inQueue)
{
	// TODO: insert return statement here
}

Queue getRecordsYearsBefore(Queue checkedQueue, int beforeYear) {
	List tmpList = getRecordsYearsBefore(checkedQueue.queueElems, beforeYear);
	return Queue(tmpList);
}
