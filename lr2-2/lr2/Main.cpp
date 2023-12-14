#include <iostream>
#include <stdio.h>

using namespace std;

class Series1
{
    //   ареатангенс	arth	artanh, tanh−1       atanh
    //   сходимость (-1; 1)
    private:
        double x=0.12345;
        double eps = 1e-6;
        double f = 0;
        double f_n = 1e+6;
        int n = 0;
    public:
        void print()
        {
            while (fabs(f_n) > eps)
            {
                f_n = pow(x, 2 * n + 1) / (2 * (double)n + 1);
                f += f_n;
                n++;
                //cout << "f_n: " << f_n << endl << "f: " << f << endl << "n: " << n << endl;
            }
            cout << "Класс 1:\n";
            cout << "arth(x) = " << f << "\n";
            cout << "Проверка: arth(x) = " << atanh(x) << "\n\n";
        }
};

class Series2
{
private:
    double x;
    double eps;
    double f;
    double f_n;
    int n;
public:
    // Конструктор
    Series2( double c_x = 0.12345, double c_eps = 1e-6, double c_f = 0, double c_f_n = 1e+6, int c_n = 0)
        : x{c_x}, eps{c_eps}, f{c_f}, f_n{c_f_n}, n{c_n}
    {
    }
    // Деструктор
    ~Series2()
    {
        cout << "Тут сработал деструктор Series2 \n";
    }

    void print()
    {
        while (fabs(f_n) > eps)
        {
            f_n = pow(x, 2 * n + 1) / (2 * (double)n + 1);
            f += f_n;
            n++;
        }
        cout << "Класс 2:\n";
        cout << "arth(x) = " << f << "\n";
        cout << "Проверка: arth(x) = " << atanh(x) << "\n\n";
    }
};

class Series3
{
private:
    double _x;
    double _eps;
    double _f;
    double _f_n;
    int _n;
    int _n_rec;
    double _x_n_recur;
    double sum_recur = 0;
public:
  /*  void print_while();
    void print_recurs_sum();
    void print_recurs_member();*/

    double calc_series() 
    {
        while (fabs(_f_n) > _eps)
        {
            //_f_n = pow(-1, _n) * 1 / ((2 * (double)_n + 1) * pow(_x, 2 * _n + 1));
            _f_n = pow(_x, 2 * _n + 1) / (2 * (double)_n + 1);
            _f += _f_n;
            _n++;
        }
        return _f;
    }

    double recurs_sum()
    {
        double current_f_n = calc_f_n(_n_rec);
        if (fabs(current_f_n) < _eps)
        {
            _n_rec = 0;
            return current_f_n;
        }
        _n_rec++;
        return current_f_n + recurs_sum();
    }

    double calc_f_n(int n)
    {
        //double f_n = pow(-1, n) * 1 / ((2 * (double)n + 1) * pow(_x, 2 * n + 1));
        double f_n = pow(_x, 2 * double(n) + 1) / (2 * (double)n + 1);
        return f_n;
    }

    double recurs_member()
    {
        _x_n_recur = calc_member(_x_n_recur, _n_rec);
        double current_x_n = _x_n_recur;
        if (fabs(_x_n_recur) < _eps)
        {
            _n_rec = 0;
            _x_n_recur = _x;
            return current_x_n;
        }
        _n_rec++;
        return current_x_n + recurs_member();
    }
    // делим текущий на предыдущий и получаем формулу
    double calc_member(double x_n, int n)
    {
        if (n == 0)
        {
            return _x;
        }
        return x_n * (pow(x_n, 2) * (2 * double(n) - 1) / (2 * double(n) + 1));
        //x_n * (-1) / pow(_x, 2) * ((double)2 * n - 1) / ((double)2 * n + 1);
    }

    // Конструктор
    Series3(double x, double eps, double f=0, double f_n=1e+6, int n=0, int n_rec=0):
        _x{x}, _eps{eps}, _x_n_recur{x}, _f{f}, _f_n{f_n}, _n{n}, _n_rec{n_rec}
    {
        //_x = x;
        //_eps = eps;
        //_f = 0;
        //_f_n = 1e+6;
        //_n = 0;
        //_n_rec = 0;
        //_x_n_recur = _x;
    }

    // Деструктор
    ~Series3()
    {
        cout << "Тут сработал деструктор Series3 \n";
    }

    // Явное использование встроенной функции
  inline void print_while()
    {
        if (fabs(_x) >= 1)
        {
            cout << "Ряд расходится!\n\n";
            return;
        }
        cout << "While (через разложение): arth(x) = " << calc_series() << "\n";
        cout << "Проверка: arth(x) = " << atanh(_x) << "\n\n";
    }

    void print_recurs_sum()
    {
        if (fabs(_x) >= 1)
        {
            cout << "Ряд расходится!\n\n";
            return;
        }
        cout << "Рекурсия (сумма): arth(x) = " << recurs_sum() << "\n";
        cout << "Проверка: arth(x) = " << atanh(_x) << "\n\n";
    }

    void print_recurs_member()
    {
        if (fabs(_x) >= 1)
        {
            cout << "Ряд расходится!\n\n";
            return;
        }
        cout << "Рекурсия (член ряда): arth(x) = " << recurs_member() << "\n";
        cout << "Проверка: arth(x) = " << atanh(_x) << "\n\n";
    }
};



int main()
{
    setlocale(LC_ALL, "Russian");
    Series1 n1;
    n1.print();
    Series2 n2;
    n2.print();
    double x;
    double eps;
    cout << "Введите x ( область сходимости ряда (-1; 1) )\n";
    cin >> x;
    cout << "Введите необходимую точность\n";
    cin >> eps;
    Series3 n3{ x, eps };
    cout << "\nКласс 3:\n";
    n3.print_while();
    n3.print_recurs_sum();
    n3.print_recurs_member();
    // Использование массива объектов
    Series3 n[3] = {Series3(x, eps), Series3(x, eps), Series3(x, eps)};
    cout << "\nИспользуя массив объектов:\n";
    n[0].print_while();
    n[1].print_recurs_sum();
    n[2].print_recurs_member();
    return 0;
}
