#pragma once

#include <fstream>
#include <string>

#include "Utils.h"

using namespace std;

void read_array_from_file(double** array, int n, int m, string filename); // Чтение массива из файла
void find_nchet_col(double** array, int n, int m, string filename); // Нахождение нечетных строк сформированного массива
void find_max_min(double** array, int n, int m, double** a, string fname);
double** create_bivariate_array(int n, int m); // Создание двумерного динамического массива
double* create_array(int n); // Создание одномерного динамического массива
void delete_bivariate_array(double** bivariate_array, int n); // Удаление двумерного динамического массива
void delete_array(double* array); // Удаление одномерного динамического массива
void print_array_to_file(double** array, int n, int m, string filename);
void print_array(double** array, int n, int m);

void array_work();