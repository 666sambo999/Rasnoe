#include <iostream>

using namespace std;

void main()
{
	setlocale(LC_ALL, "");
	// ����������� �������
	int a; 
	cout << "������� ���������� ����� � ������������: "; cin >> a; 
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