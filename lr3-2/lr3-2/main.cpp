#include <iostream>
#include <string>

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



void listTesting() {
	
	cout << "Тестирование списка" << endl;
	List testList = List();
	cout << "Добавление элементов" << endl;
	testList += {"Game1", "Genre1", 1990};
	testList += {"Game2", "Genre2", 1991};
	testList += {"Game3", "Genre3", 1992};
	testList += {"Game7", "Genre7", 2000};
	testList.insertBefore({ "Game4", "Genre4", 1992 }, 1);
	testList.insertBefore({ "Game5", "Genre5", 1993 }, 1);
	testList.insertBefore({ "Game6", "Genre6", 1994 }, 3);
	testList.insertBefore({ "Game8", "Genre8", 2020 }, testList.length()-1);
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
	cout << testList.findElemByGenre("Genre8") << endl;
	cout << testList.findElemByGenre("Genre123123") << endl;

	cout << "Поиск игр появившихся ранее этого года" << endl;
	List filteredList = getRecordsYearsBefore(testList, 1995);
	printList(filteredList);
	
	//очистка списка
	cout << "Очистка списка" << endl;
	filteredList.clearList();
	printList(filteredList);

	cout << "Перегруженный конструктор" << endl;
	List testList2 = List({ "Game1", "Genre1", 1990 });
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
	GameRecord findElemByGenre(string genre);
	bool clearQueue();

	void operator+=(GameRecord newRecord);
	Queue& operator--();
	Queue operator--(int);

	friend Queue getRecordsYearsBefore(Queue checkedQueue, int beforeYear);
	friend void printQueue(Queue& queueForPrinting);

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

Queue getRecordsYearsBefore(Queue checkedQueue, int beforeYear) {
	List tmpList = getRecordsYearsBefore(checkedQueue.queueElems, beforeYear);
	return Queue(tmpList);
}

void queueTesting() {
	cout << "Тестирование очереди" << endl;
	cout << endl << "Добавление элементов" << endl;
	Queue testQueue = Queue();
	testQueue += {"Game1", "Genre1", 1990};
	testQueue += {"Game2", "Genre2", 1991};
	testQueue += {"Game3", "Genre3", 1992};
	testQueue += {"Game4", "Genre4", 1993};
	testQueue.push({ "Game5", "Genre5", 1992 });
	testQueue.push({ "Game6", "Genre6", 1993 });
	testQueue.push({ "Game7", "Genre7", 2000 });
	testQueue.push({ "Game8", "Genre8", 2020 });
	
	printQueue(testQueue);

	cout << "Извлечение элементов" << endl;
	testQueue.pop().printRecord();
	testQueue.pop().printRecord();

	printQueue(testQueue);

	cout << "Удаление элементов" << endl;
	testQueue--;
	testQueue--;
	printQueue(testQueue);

	cout << "Поиск элемента по жанру" << endl;
	testQueue.findElemByGenre("Genre6").printRecord();
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
	cout << endl << endl;
	queueTesting();
	return 1;
}