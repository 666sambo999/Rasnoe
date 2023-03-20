#include <iostream>

using namespace std;

void main()
{
	setlocale(LC_ALL, "");
	// Треугольник паскаля
	int a; 
	cout << "Введите количество строк в треугольнике: "; cin >> a; 
	for (int i = 0; i < a; i++)
	{
		int value = 1; 
		for (int j = 0; j <= i; j++)
		{
			cout << value << " ";
			value = value * (i-j) / (j + 1);
		}
		cout << endl; 
	}
}