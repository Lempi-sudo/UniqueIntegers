// ConsoleApplication1.cpp : Defines the entry point for the console application.
//
#include"stdafx.h"
#include <conio.h>
#include <Windows.h>
#include<iostream>
#include <ctime>
using namespace std;
bool trace = false;


class UniqueIntegers
{
private:
	int* _massiv;
	size_t _size;
	int _sum;
public:
	UniqueIntegers()
	{
		_size = 0;
		_massiv = nullptr;
	}
	~UniqueIntegers() {
		delete[] _massiv;
	}
	UniqueIntegers(const UniqueIntegers&rhs)
	{
		if (trace)
		{
			std::cout << "конструктор копирования(copy-ctor)";
		}
		_massiv = new int[rhs._size];
		_size = rhs._size;
		_sum = rhs._sum;
		for (int i = 0; i < _size; i++)
		{
			_massiv[i] = rhs._massiv[i];
		}
	}
	UniqueIntegers&operator=(const UniqueIntegers& rhs)
	{
		if (trace)
		{
			std::cout << "оператор присваивания копирования (copy-assing)";
		}
		delete[]_massiv;
		_size = rhs._size;
		_sum = rhs._sum;
		_massiv = new int(rhs._size);
		for (int i = 0; i < rhs._size; i++)
		{
			_massiv[i] = rhs._massiv[i];
		}
		return *this;
	}
	UniqueIntegers(UniqueIntegers&&rhs)noexcept:_massiv(rhs._massiv), _size(rhs._size), _sum(rhs._sum)
	{
		if (trace)
		{
			std::cout << "конструктор перемещения(move-ctor) ";
		}
		rhs._massiv = nullptr;
		rhs._size = 0;
		rhs._sum = 0;
	}
	UniqueIntegers&operator=(UniqueIntegers&&rhs)noexcept
	{

		if (trace)
		{
			std::cout << "оператор присваивания перемещения(move-assign)";
		}
		delete[]_massiv;
		_massiv = rhs._massiv;
		_size = rhs._size;
		_sum = rhs._sum;
		rhs._massiv = nullptr;
		rhs._size = 0;
		rhs._sum = 0;
		return*this;
	}
	UniqueIntegers&Input_Random_Value(int sz)
	{
		delete[]_massiv;
		_massiv = new int[sz];
		_size = sz;
		bool BeNumber;
		for (size_t i = 0; i < _size; )
		{
			BeNumber = false;
			int randomValue = rand() % (50);
			/*int randomValue = rand() %(RAND_MAX);*/
			for (size_t j = 0; j < i; ++j)
			{
				if (_massiv[j] == randomValue)
				{
					BeNumber = true;
					break;
				}
			}
			if (!BeNumber)
			{
				_massiv[i] = randomValue;
				i++;
			}

		}
		_sum = 0;
		for (size_t i = 0; i < _size; ++i)
		{
			_sum += _massiv[i];
		}
		return *this;
	}
	void _insert(int value)
	{
		if (this->is_common_number(value))
		{
			int*copy = new int[_size];
			for (size_t i = 0; i < _size; i++)
			{
				copy[i] = _massiv[i];
			}
			delete[]_massiv;
			_massiv = new int[_size + 1];
			_size += 1;
			for (size_t i = 0; i <_size-1; i++)
			{
				_massiv[i] = copy[i];
			}
			_massiv[_size - 1] = value;
		}
		this->_summa();
	}
	void _insert_end(int value)
	{
		if (this->is_common_number(value))
		{
			int*copy=new int[_size];
			for (size_t i = 0; i < _size; i++)
			{
				copy[i] = _massiv[i];
			}
			delete[]_massiv;
			_massiv = new int[_size + 1];
			_size += 1;
			_massiv[0] = value;
			for (size_t i = 1; i <_size; i++)
			{
				_massiv[i] = copy[i - 1];
			}
		}
		this->_summa();
	}
	UniqueIntegers & _remove(int value)
	{
		if (this->is_common_number(value) == false)
		{
			int* copy=new int[_size];
			for (size_t i = 0; i < _size; i++)
			{
				copy[i] = _massiv[i];
			}
			delete[]_massiv;
			_massiv = new int[_size - 1];
			_size = _size - 1;
			int index = 0;
			for (size_t i = 0; i <_size+1; i++)
			{
				if (value != copy[i])
				{
					_massiv[index] = copy[i];
					index++;
				}
			}
		}
		this->_summa();
		return *this;
	}
	int Get_Size()const
	{
		return _size;
	}
	bool is_common_number(int value)const
	{
		for (size_t i = 0; i < _size; i++)
		{
			if (value == _massiv[i])
			{
				return false;
			}
		}
		return true;
	}
	int operator[](int index)const
	{
		if ((index < 0) || (index > _size - 1))
		{
			throw exception("Выход за переделы массивай");
		}
		return _massiv[index];
	}
	int&operator[](int index)
	{
		if ((index < 0) || (index > _size - 1))
		{
			throw exception("Выход за переделы массивай");
		}
		return _massiv[index];
	}
	int _summa()
	{
		int sum = 0;
		for (size_t i = 0; i < _size; i++)
		{
			sum += _massiv[i];
		}
		_sum = sum;
		return sum;
	}
};

//bool is_common_number(const UniqueIntegers&rhs, int value)
//{
//	for (size_t i = 0; i < rhs.Get_Size(); i++)
//	{
//		if (value == rhs[i])
//		{
//			return false;
//		}
//	}
//	return true;
//}
std::ostream & operator<< (std::ostream & outs, const UniqueIntegers&rhs)
{
	for (int i = 0; i < rhs.Get_Size(); i++)
	{

		outs << rhs[i] << "  ";
	}
	outs << endl;
	return outs;
}
void operator+(UniqueIntegers&rhs, int number)
{
	rhs._insert(number);
}
void operator+(int number, UniqueIntegers&rhs)
{
	rhs._insert_end(number);
}
void operator-(UniqueIntegers&rhs, int number)
{
	rhs._remove(number);
}
UniqueIntegers operator+(const UniqueIntegers&rhs, const UniqueIntegers&tmp)
{
	UniqueIntegers result(rhs);
	for (size_t i = 0; i < tmp.Get_Size(); i++)
		result._insert(tmp[i]);
	return result;
}
UniqueIntegers operator-(const UniqueIntegers&rhs, const UniqueIntegers&tmp)
{
	UniqueIntegers result(rhs);
	for (size_t i = 0; i < tmp.Get_Size(); i++)
		result._remove(tmp[i]);
	return result;
}
UniqueIntegers TotalNumber(const UniqueIntegers&tmp, const UniqueIntegers&rhs)
{
	UniqueIntegers result;
	for (int i = 0; i < tmp.Get_Size(); i++)
	{
		for (int j = 0; j < rhs.Get_Size(); j++)
		{
			if (tmp[i] == rhs[j])
			{
				result._insert(tmp[i]);
			}
		}
	}
	result._summa();
	return result;
}

int main()
{
	setlocale(LC_ALL, "RUS");
	srand(time(NULL));
	int x1, x2, x3, x4, x5, x6;
	UniqueIntegers res;
	cout << "Введите размерность массива №1" << endl;
	cin >> x1;
	UniqueIntegers test1;
	test1.Input_Random_Value(x1);
	cout << "ваш массив" << test1 << endl;
	cout << "Введите размерность массива №2" << endl;
	cin >> x2;
	UniqueIntegers test2;
	test2.Input_Random_Value(x2);
	cout << "ваш массив" << test2 << endl;
	getchar();
	while (1)
	{
		system("cls");
		cout << "[1]-Оператор[]\n[2]-Показать пересечение\n[3]-Показать объединение (operator+)\n[4]-прибавдение числа (коммунативно)\n[5]-Показать разность множеств(operator-)\n[6]-вычитание числа из множества (operator-)\n [7]-Подсчет суммы\n\n[ESC]-Выход ";
		int key = _getch();
		if (key == 27)
		{
			break;
		}
		switch (key)
		{
		case 49:
			system("cls");
			cout << test1;
			cout << "введите номер элемента в массиве(отсчет начинается с нуля )  " << endl;
			cin >> x3;
			try {
				int number = test1[x3];
				cout << "это число" << number;
			}
			catch (const exception& ex)
			{

				cout << "Выход за пределы массива.размерность массива" << (test1.Get_Size() - 1);
			}
			getchar();
			getchar();
			break;
		case 50:
			system("cls");
			cout << test1;
			cout << endl << endl;
			cout << test2;
			cout << "ПЕРЕСЕЧЕНИЕ" << endl;
			res = TotalNumber(test1, test2);
			cout << res;
			getchar();
			getchar();
			break;
		case 51:
			system("cls");
			cout << test1;
			cout << endl << endl;
			cout << test2;
			cout << "ОБЪЕДИНЕНИЕ" << endl;
			res = test1 + test2;
			cout << res;
			getchar();
			getchar();
			break;
		case 52:
			system("cls");
			cout << test1;
			cout << "ПРИБАВЛЕНИЕ (Массив+число)" << endl;
			cout << "введите число " << endl;
			cin >> x4;
			test1 + x4;
			cout << test1;
			cout << "ПРИБАВЛЕНИЕ (число+массив)" << endl;
			cout << "введите число " << endl;
			cin >> x5;
			x5 + test1;
			cout << test1;
			getchar();
			getchar();
			break;
		case 53:
			system("cls");
			cout << test1;
			cout << endl << endl;
			cout << test2;
			cout << "РАЗНОСТЬ МНОЖЕСТВ" << endl;
			res = test1 - test2;
			cout << res;
			getchar();
			getchar();
			break;
		case 54:
			system("cls");
			cout << test1;
			cout << "ЗАДАЙТЕ ЧИСЛО  " << endl;
			cin >> x6;
			test1 - x6;
			cout << test1;
			getchar();
			getchar();
			break;
		case 55:
			system("cls");
			cout << test1;
			cout << "СУММА ЭЛЕМЕНТОВ   " << endl;
			cout << test1._summa();
			getchar();
			getchar();
			break;
		default: break;
		}
	}
	trace = true;
	UniqueIntegers a, y;
	a.Input_Random_Value(2);
	y.Input_Random_Value(3);
	printf("\n\n");
	UniqueIntegers z(a);
	printf("\n\n");
	UniqueIntegers g;
	g.Input_Random_Value(8);
	g = a;
	printf("\n\n");
	UniqueIntegers uy;
	uy = a + y;
	printf("\n\n");
	printf("\n\n");
	printf("\n\n");
	UniqueIntegers r = y + a;
	trace = false;
	getchar();
	return 0;
}


