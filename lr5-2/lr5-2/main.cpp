//иерархией классов ввода - вывода;
//манипуляторами и управлением вводом - выводом с их помощью;
//способами перегрузки операторов << и >> ;
//чтением и записью текстовых и двоичных файлов;
//функциями ввода - вывода.

//Задание на выполнение лабораторной работы.
//Выполнить лабораторную работу №1(ЗАДАНИЕ 4) с использованием текстовых файлов для ввода данных и вывода результатов.
//Выполнить лабораторную работу №3, дополнив ее методом ввода данных из текстового файла.
//На основе варианта задания лабораторной работы №3 разработать программу, включающую:
//Ввод данных из текстового файла,
//Запись данных в двоичный файл,
//Модификацию данных двоичного файла,
//Удаление данных из двоичного файла,
//Любую арифметическую обработку данных двоичного файла,
//Один из перегруженных операторов << или >> ,
//Собственную манипуляторную функцию.
//Результат выводить в текстовый файл, используя форматный вывод и манипуляторы.

//№2
//Дан двумерный массив V(6, 5).
//Требуется
//ввести исходный массив из текстового файла;
//вывести исходный массив в текстовый файл;
//сформировать массив из минимальных и максимальных элементов четных строк массива;
//напечатать сформированный массив;
//найти и напечатать произведение отрицательных элементов нечетных столбцов исходного массива.

#include <iostream>
#include <direct.h>


#include "Ex1.h"
#include "List.h"
#include "Queue.h"

using namespace std;

string ex1Fname = "Ex1.txt",
	ex2TextFname = "Ex2_3.txt",
	
	ex2BinFname = "Ex2Bin.txt",
	ex2BinFnameIn = "Ex2BinIn.txt",
	ex2BinFnameOut = "Ex2BinOut.txt";

void listTesting() {
	List testList;
	fstream inOut;

	//
	char dir[255];
	_getcwd(dir, 255);

	inOut.open(ex2TextFname);
	if (!inOut) {
		cout << "Невозможно открыть файл: " << ex2TextFname << endl;
		printf("Текущая директория:  %s", dir);
	}
	else {
		inOut >> testList;
		testList.sort();
		printList(testList, false);
		inOut.close();
	}

	cout << "Запись в бинарь" << endl;
	testList.writeToBinary(ex2BinFname);
	printList(testList, false);
	testList.clearList();
	printList(testList, false);
	testList.readFromBinary(ex2BinFname);

	testList.sort();
	printList(testList, false);

	cout << "Изменение строк" << endl;
	testList.changeStringBinary(0, { "The Legend Of Zelda: Ocarina of Time", "Action-adventure", 1998 }, ex2BinFname);
	printList(testList, false);

	cout << "Удаление строки" << endl;
	testList.deleteStringFromBinary(0, ex2BinFname);
	printList(testList, false);

	cout << "Поиск по жанру" << endl;
	auto testList2 = testList.findElemsByGenre("Action");
	printList(testList2, false);
	cout << endl;

	cout << "Поиск игры самого раннего года выпуска" << endl;
	cout << "Самая ранняя игра: " << testList.findFirstGameYearBinary(ex2BinFname) << endl;
}

void queueTesting() {
	Queue testQueue;
	fstream inOut;
	//
	char dir[255];
	_getcwd(dir, 255);
	//
	inOut.open(ex2TextFname);
	if (!inOut) {
		cout << "Невозможно открыть файл: " << ex2TextFname << endl;
		printf("Текущая директория:  %s", dir);
	}
	else {
		inOut >> testQueue;
		printQueue(testQueue);
		inOut.close();
	}

	testQueue.writeToBinary(ex2BinFname);
	printQueue(testQueue);
	testQueue.clearQueue();
	printQueue(testQueue);
	testQueue.readFromBinary(ex2BinFname);
	printQueue(testQueue);

	cout << "Изменение строк" << endl;
	testQueue.changeStringBinary(0, { "Game1", "Genre1", 1999 }, ex2BinFname);
	printQueue(testQueue);

	cout << "Удаление строки" << endl;
	testQueue.deleteStringFromBinary(0, ex2BinFname);
	printQueue(testQueue);

	cout << "Поиск игры самого раннего года выпуска" << endl;
	cout << "Самая ранняя игра: " << testQueue.findFirstGameYearBinary(ex2BinFname) << endl;
}

int main() {
	setlocale(LC_ALL, "rus");
	listTesting();
	//queueTesting();

	return 1;
}