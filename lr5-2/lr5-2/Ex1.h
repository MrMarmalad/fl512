#pragma once

#include <fstream>
#include <string>

#include "Utils.h"

using namespace std;

void read_array_from_file(double** array, int n, int m, string filename); // ������ ������� �� �����
void find_nchet_col(double** array, int n, int m, string filename); // ���������� �������� ����� ��������������� �������
void find_max_min(double** array, int n, int m, double** a, string fname);
double** create_bivariate_array(int n, int m); // �������� ���������� ������������� �������
double* create_array(int n); // �������� ����������� ������������� �������
void delete_bivariate_array(double** bivariate_array, int n); // �������� ���������� ������������� �������
void delete_array(double* array); // �������� ����������� ������������� �������
void print_array_to_file(double** array, int n, int m, string filename);
void print_array(double** array, int n, int m);

void array_work();