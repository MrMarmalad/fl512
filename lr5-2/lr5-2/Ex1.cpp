#include <iostream>
#include <string>

#include "Ex1.h"

using namespace std;

void read_array_from_file(double** array, int n, int m, string filename)
{
	ifstream in;

	in.open(filename);

	if (!in.is_open()) {
		cout << "Файл " << filename << "не открывается" << endl;
		return;
	}

	for (auto i = 0; i < n; i++) {
		for (auto j = 0; j < m; j++) {
			in >> array[i][j];
		}
	}
	in.close();
}

void find_nchet_col(double** array, int n, int m, string fname)
{
	ofstream out;

	out.open(fname, ios_base::app);

	if (!out.is_open()) {
		cout << "Файл " << fname << "не открывается" << endl;
		return;
	}

	double minus = 1;
	out << "\n\nОтрицательные элементы нечетных столбцов исходного массива:\n";

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j += 2)
		{

			if (array[i][j] < 0)
			{
				out << array[i][j] << " ";
				minus = array[i][j] * minus;
			}
		}
		out << "\n";
	}
	out.close();
}

void find_max_min(double** array, int n, int m, double** a, string fname)
{
	ofstream out;

	out.open(fname, ios_base::app);

	if (!out.is_open()) {
		cout << "Файл " << fname << "не открывается" << endl;
		return;
	}

	out << "\n\nМаксимальное и минимальное значение четных строк:\n";
	for (int i = 1; i < n; i += 2)
	{
		double min = array[i][1];
		double max = array[i][1];
		for (int j = 0; j < m; j++)
		{
			if (array[i][j] < min)
				min = array[i][j];
			if (array[i][j] > max)
				max = array[i][j];
		}
		a[(i - 1) / 2][0] = min;
		a[i / 2][1] = max;
	}
	out.close();
}

double* create_array(int n)
{
	double* array = new double[n];
	return array;
}

double** create_bivariate_array(int n, int m) {
	double** bivariate_array = new double* [n];
	for (int i = 0; i < n; i++)
	{
		bivariate_array[i] = new double[m];
		for (int j = 0; j < m; j++)
		{
			bivariate_array[i][j] = 0;
		}
	}
	return bivariate_array;
}

void delete_bivariate_array(double** bivariate_array, int n)
{
	for (int i = 0; i < n; i++) {
		delete[] bivariate_array[i];
	}
	delete[] bivariate_array;
}

void delete_array(double* array)
{
	delete[] array;
}

void print_array_to_file(double** array, int n, int m, string fname)
{
	ofstream out;

	out.open(fname, ios_base::app);

	if (!out.is_open()) {
		cout << "Файл " << fname << "не открывается" << endl;
		return;
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			setup(out) << array[i][j];
		}
		out << endl;
	}
	out.close();
}

void print_array(double** array, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("%8.3f ", array[i][j]);
		}
		cout << endl;
	}
}

void array_work()
{
	int n = 0, m = 0, n1 = 0;
	int r = 1;
	double** array = NULL;
	double** a = NULL;
	// Исходный файл
	char filename[] = "array.txt";
	while (r)
	{
		try
		{
			cout << "Введите количество строк n (макс 6)\n";
			cin >> n;
			cout << "Введите количество столбцов m (макс 5)\n";
			cin >> m;
			array = create_bivariate_array(n, m);
			if (n % 2 == 0)
				n1 = n / 2;
			else
				n1 = (n - 1) / 2;
			a = create_bivariate_array(n1, 2);
			read_array_from_file(array, n, m, filename);
		}
		catch (int i)
		{
			cout << "Конец файла\n\n";
			continue;
		}
		r = 0;
	}

	char filename_out[] = "array_out.txt";

	ofstream out;
	out.open(filename_out);
	out << "\nИсходный массив:\n";
	out.close();
	// Печать массива в консоль
	print_array_to_file(array, n, m, filename_out);
	
	// Печать массива в файл
	print_array_to_file(array, n, m, filename_out);
	
	//Нахождение нечетных столбцов исходного массива
	find_nchet_col(array, n, m, filename_out);
	find_max_min(array, n, m, a, filename_out);
	print_array_to_file(a, n1, 2, filename_out);
	system("pause");
	//Освобождение выделенной памяти
	delete_bivariate_array(array, n);

}