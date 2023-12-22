#include <iostream>
#include <string>

#include <stdio.h>
#include <conio.h>

using namespace std;
//вариант 2


// создать очередь и список
/*
дополнение и удаление элемента;
удаление всей структуры;
извлечение (чтение) элемента;
поиск в соответствии со своим вариантом;
обработку элементов структур в соответствии со своим вариантом.

Для добавления элементов и удаления (по п.1 и 2) использовать перегруженные операторы.
В работе использовать перегруженный конструктор, дружественную функцию и перегруженную функцию (их назначение выбрать самостоятельно).
Список должен быть упорядоченным.
Результаты работы должны быть выведены на экран.
Исходные данные должны быть подобраны таким образом, чтобы можно было проверить правильность работы программы.


Типы элементов линейных динамических структур
запись, содержащая сведения о компьютерных играх в составе: название, жанр и год появления

Ключевой признак для поиска
жанр

Обработка
Определение компьютерных игр, появившихся ранее заданного года.
*/

struct GameRecord
{
	string name = "";
	string genre = "";
	int year = 0;

	// если strict == false, то пустые поля будут учитываться как успешно прошедшие проверку
	bool equal(GameRecord testRecord, bool strict = true) const {
		if (strict == true) {
			return (
				this->genre == testRecord.genre &&
				this->name == testRecord.name &&
				this->year == testRecord.year
				);
		}
		else {
			return (
				(this->genre == testRecord.genre || this->genre.empty() || testRecord.genre.empty()) &&
				(this->name == testRecord.name || this->name.empty() || testRecord.name.empty()) &&
				(this->year == testRecord.year || this->year == 0 || testRecord.year == 0)
				);
		}
	}

	bool empty() const {
		if (this->genre.empty() && this->name.empty() && this->year == 0) {
			return true;
		}
		return false;
	}

	void printRecord() const {
		cout << this->name << "\t" << this->genre << "\t" << this->year << endl;
	}

	bool operator > (const GameRecord& comparedRec) const
	{
		return this->year > comparedRec.year;
	}

	bool operator < (const GameRecord& comparedRec) const
	{
		return this->year < comparedRec.year;
	}
};


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
	List findElemsByGenre(string genre);
	List* insertBefore(GameRecord newRecord, int insPlace);
	List* deleteFrom(int elemIndexToDelete);
	bool changeElem(int index, GameRecord changedRecord);
	bool clearList();

	GameRecord getElement(int index);
	GameRecord getElement();
	GameRecord getNext();
	GameRecord getPrev();

	friend void printList(List& listForPrinting);

	void sort(bool asc = true);
	void swap(int indexF, int indexS);
};

//пустой список
List::List()
	: size{ 0 }, back{nullptr}, front{nullptr}, lastReadedElement{nullptr}, lastReadedIndex{-1}
{
}

List::List(GameRecord firstRecord) :
	size{ 1 }, lastReadedElement{ nullptr }, lastReadedIndex{ -1 }
{
	listElem *newElem = new(listElem);
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
	listElem *tmpElem;
	if (this->length()  == 0) return this;
	
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
				if (this->getElement(j) > this->getElement(j+1)) {
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

void listTesting() {
	
	cout << "Тестирование списка" << endl;
	List testList = List();
	cout << "Добавление элементов" << endl;
	testList += {"Quake", "Action", 1997};
	testList += {"StarCraft", "Strategy", 1998};
	testList += {"Resident Evil 2", "Action", 1998};
	testList += {"Carmageddon", "Racing", 1996};
	testList.insertBefore({ "The Legend Of Zelda: Ocarina of Time", "Adventure", 1992 }, 1);
	testList.insertBefore({ "Tony Hawk's Pro Skater", "Sport", 2002 }, 1);
	testList.insertBefore({ "SimCity", "Simulator", 1994 }, 3);
	testList.insertBefore({ "Animal Crossing", "Action", 2001}, testList.length()-1);
	printList(testList);

	cout << "Сортировка списка" << endl;
	testList.sort();
	printList(testList);

	cout << "Удаление элементов" << endl;
	testList -= 2;
	printList(testList);
	cout << endl;
	testList -= 1;
	printList(testList);
	testList.deleteFrom(0);
	testList.deleteFrom(testList.length()-1);
	printList(testList);

	cout << endl << "Поиск по жанру" << endl;
	auto findedRecords = testList.findElemsByGenre("Action");
	printList(findedRecords);

	cout << "Поиск игр появившихся ранее этого года" << endl;
	List filteredList = getRecordsYearsBefore(testList, 2000);
	printList(filteredList);
	
	//очистка списка
	cout << "Очистка списка" << endl;
	filteredList.clearList();
	printList(filteredList);
	cout << endl;

	cout << "Перегруженный конструктор" << endl;
	List testList2 = List({ "Perfect Dark", "Action", 2000 });
	printList(testList2);
}

class Queue
{
public:
	Queue();
	Queue(GameRecord firstRecord);
	Queue(List initList);
	~Queue();
	bool push(GameRecord newElem);
	GameRecord pop();
	List findElemsByGenre(string genre);
	bool clearQueue();

	void operator+=(GameRecord newRecord);
	Queue& operator--();
	Queue operator--(int);

	friend Queue getRecordsYearsBefore(Queue checkedQueue, int beforeYear);
	friend void printQueue(Queue& queueForPrinting);

	void sort(bool asc = true);
	void swap(int indexF, int indexS);

private:
	List queueElems;
};

Queue::Queue()
	:queueElems{List()}
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

List Queue::findElemsByGenre(string genre)
{
	return this->queueElems.findElemsByGenre(genre);
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

void Queue::sort(bool asc) {
	this->queueElems.sort(asc);
}

void Queue::swap(int indexF, int indexS) {
	this->queueElems.swap(indexF, indexS);
}

void printQueue(Queue& queueForPrinting)
{
	printList(queueForPrinting.queueElems);
}

Queue getRecordsYearsBefore(Queue checkedQueue, int beforeYear) {
	List tmpList = getRecordsYearsBefore(checkedQueue.queueElems, beforeYear);
	return Queue(tmpList);
}

void queueTesting() {
	cout << "Тестирование очереди" << endl;
	cout << endl << "Добавление элементов" << endl;
	Queue testQueue = Queue();
	
	testQueue += {"StarCraft", "Strategy", 1999};;
	testQueue += {"Quake", "Action", 1995};
	testQueue += {"Carmageddon", "Racing", 1996};
	testQueue += {"Resident Evil 2", "Action", 1998};
	testQueue.push({ "Animal Crossing", "Action", 1994 });
	testQueue.push({ "SimCity", "Simulator", 1994 });
	testQueue.push({ "The Legend Of Zelda: Ocarina of Time", "Adventure", 1992 });
	testQueue.push({"Tony Hawk's Pro Skater", "Sport", 2002});
	printQueue(testQueue);

	cout << "Сортировка очереди" << endl;
	testQueue.sort();
	printQueue(testQueue);

	cout << "Извлечение элементов" << endl;
	testQueue.pop().printRecord();
	testQueue.pop().printRecord();
	cout << endl;
	
	printQueue(testQueue);

	cout << "Удаление элементов" << endl;
	testQueue--;
	testQueue--;
	printQueue(testQueue);

	cout << "Поиск элементов по жанру" << endl;
	auto tmpList = testQueue.findElemsByGenre("Action");
	printList(tmpList);
	cout << "\n";

	cout << "Поиск записей с годом ранее заданного" << endl;
	Queue testQueue2 = getRecordsYearsBefore(testQueue, 1995);
	printQueue(testQueue2);

	cout << "Очистка очереди" << endl;
	testQueue2.clearQueue();
	printQueue(testQueue2);
}

int main() {
	setlocale(LC_ALL, "rus");
	listTesting();
	cout << "================================" << endl;
	cout << endl << endl;
	queueTesting();
	return 1;
}