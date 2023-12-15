//��������� ������� ����� - ������;
//�������������� � ����������� ������ - ������� � �� �������;
//��������� ���������� ���������� << � >> ;
//������� � ������� ��������� � �������� ������;
//��������� ����� - ������.

//������� �� ���������� ������������ ������.
//��������� ������������ ������ �1(������� 4) � �������������� ��������� ������ ��� ����� ������ � ������ �����������.
//��������� ������������ ������ �3, �������� �� ������� ����� ������ �� ���������� �����.
//�� ������ �������� ������� ������������ ������ �3 ����������� ���������, ����������:
//���� ������ �� ���������� �����,
//������ ������ � �������� ����,
//����������� ������ ��������� �����,
//�������� ������ �� ��������� �����,
//����� �������������� ��������� ������ ��������� �����,
//���� �� ������������� ���������� << ��� >> ,
//����������� �������������� �������.
//��������� �������� � ��������� ����, ��������� ��������� ����� � ������������.

//�2
//��� ��������� ������ V(6, 5).
//���������
//������ �������� ������ �� ���������� �����;
//������� �������� ������ � ��������� ����;
//������������ ������ �� ����������� � ������������ ��������� ������ ����� �������;
//���������� �������������� ������;
//����� � ���������� ������������ ������������� ��������� �������� �������� ��������� �������.

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
	//
	inOut.open(ex2TextFname);
	if (!inOut) {
		cout << "���������� ������� ����: " << ex2TextFname << endl;
		printf("������� ����������:  %s", dir);
	}
	else {
		inOut >> testList;
		printList(testList);
		inOut.close();
	}

	testList.writeToBinary(ex2BinFname);
	printList(testList);
	testList.clearList();
	printList(testList);
	testList.readFromBinary(ex2BinFname);
	printList(testList);

	cout << "��������� �����" << endl;
	testList.changeStringBinary(0, { "Game1", "Genre1", 1999 }, ex2BinFname);
	printList(testList);

	cout << "�������� ������" << endl;
	testList.deleteStringFromBinary(0, ex2BinFname);
	printList(testList);

	cout << "����� ���� ������ ������� ���� �������" << endl;
	cout << "����� ������ ����: " << testList.findFirstGameYearBinary(ex2BinFname) << endl;
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
		cout << "���������� ������� ����: " << ex2TextFname << endl;
		printf("������� ����������:  %s", dir);
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

	cout << "��������� �����" << endl;
	testQueue.changeStringBinary(0, { "Game1", "Genre1", 1999 }, ex2BinFname);
	printQueue(testQueue);

	cout << "�������� ������" << endl;
	testQueue.deleteStringFromBinary(0, ex2BinFname);
	printQueue(testQueue);

	cout << "����� ���� ������ ������� ���� �������" << endl;
	cout << "����� ������ ����: " << testQueue.findFirstGameYearBinary(ex2BinFname) << endl;
}

int main() {
	setlocale(LC_ALL, "rus");
	listTesting();
	queueTesting();

	return 1;
}