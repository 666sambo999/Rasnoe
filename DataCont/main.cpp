﻿#include <iostream>
#include <ctime>

using namespace std;

using std::cout;

#define tab "\t"
#define delimetr  "\n---------------------------------------\n"


class List
{
	class Element
	{		// это включение или композиция в класс
		int Data; // значение элемента 
		Element* pNext; // указатель на сдедующий элемент 
		Element* pPrev;  //указатель на предыдущий элемент 
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			: Data(Data), pNext(pNext), pPrev(pPrev) // инициализация в заголовке
		{
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~Element()
		{
#ifdef DEBUG			
			cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
		}
		friend class List;
	}*Head, * Tail; // объекты и указатели на объекты можно объявлять сражу после описания класса
	size_t size;			// это псевдоним для типа данных 

	class ConstBaseIterator
	{
		// Generalisation - обобщает 
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp) : Temp(Temp) {}
		~ConstBaseIterator() {}

		bool operator==(const ConstBaseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ConstBaseIterator& other)const
		{
			// return !(*this == other);
			return this->Temp != other.Temp; // будет быстрее, так как проц сравгивает адреса
		}
		const int& operator*()const
		{
			return Temp->Data;
		}
	};
public:
	class ConstIterator : public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp) :ConstBaseIterator(Temp)
		{
#ifdef DEBUG
			cout << "ItConstructor\t" << this << endl;
#endif // DEBUG

		}
		~ConstIterator()
		{
#ifdef DEBUG
			cout << "ItDestructor\t" << this << endl;
#endif // DEBUG

		}
		ConstIterator operator ++()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ConstIterator operator ++(int)
		{
			ConstIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		ConstIterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstIterator operator --(int)
		{
			ConstIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}

	};
	class ConstReverseIterator : public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp) : ConstBaseIterator(Temp)
		{
#ifdef DEBUG
			cout << "RItConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~ConstReverseIterator()
		{
#ifdef DEBUG
			cout << "RItDestructor:\t" << this << endl;
#endif // DEBUG
		}
		ConstReverseIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstReverseIterator operator++(int)
		{
			ConstReverseIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ConstReverseIterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstReverseIterator& operator--(int)
		{
			ConstReverseIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}

	};
	class Iterator : public ConstIterator
	{
	public:
		Iterator(Element* Temp) : ConstIterator(Temp) {}
		~Iterator() {}
		int& operator*()
		{
			return Temp->Data;
		}
	};
	class ReverseIterator :public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp) : ConstReverseIterator(Temp) {}
		~ReverseIterator() {}
		int& operator*()
		{
			return Temp->Data;
		}
	};
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	ConstIterator begin()const
	{
		return Head;
	}
	ConstIterator end()const
	{
		return nullptr;
	}
	ReverseIterator rbegin()
	{
		return Tail;
	}
	ReverseIterator rend()
	{
		return nullptr;
	}
	ConstReverseIterator rbegin()const
	{
		return Tail;
	}
	ConstReverseIterator rend()const
	{
		return nullptr;
	}

	//			Constructors 
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(int size)
	{
		while (size--)push_back(int());
	}
	List(const std::initializer_list<int>& il) :List()
	{
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	List(const List& other) :List() // Конструктор копирования 
	{
		*this = other; // повторное использование кода 
		cout << "LCopyConstructor:\t" << this << endl;
	}
	~List()
	{
		while (Tail)pop_back();
		//while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}
	//			Operators
	List& operator=(const List& other)
	{
		//1)удаляем старое значение объекта 
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		cout << "LCopyAssigment:\t" << this << endl;
		return*this;
	}


	//			Adding element 
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
			size++;
			return;
		}
		/*Element* New = new Element(Data, Head);
		New ->pNext = Head;
		Head->pPrev = New;
		Head = New;*/
		Head = Head->pPrev = new Element(Data, Head);
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
		}
		else
		{
			/*Element* New = new Element(Data);
			New->pPrev = Tail;
			Tail->pNext = New;
			Tail = New;*/
			Tail = Tail->pNext = new Element(Data, nullptr, Tail);
		}
		size++;  // отработает как в if так и в else
	}
	void insert(int Data, int index)
	{
		if (index == 0)return push_front(Data);
		if (index == size)return push_back(Data);
		if (index > size)return;
		Element* Temp;
		if (index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - index - 1; i++)Temp = Temp->pPrev;
		}
		/*Element* New = new Element(Data);
		New->pNext = Temp;
		New->pPrev = Temp->pPrev;
		Temp->pPrev ->pNext = New;
		Temp->pPrev = New;*/
		Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
		size++;
	}
	void erase(int index)
	{
		if (index == 0)return pop_front();
		if (index == size - 1)return pop_back();
		if (index >= size)return;
		Element* Temp;
		if (index < size / 2)
		{
			Temp = Head; // заходим через голову 
			for (int i = 0; i < index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail; // заходим через хвост 
			for (int i = 0; i < size - index - 1; i++)Temp = Temp->pPrev;
		}
		//1) Исключаем элемент из списка
		Temp->pPrev->pNext = Temp->pNext;
		Temp->pNext->pPrev = Temp->pPrev;
		//2) удаляем элeмент из памяти 
		delete Temp;
		size--;
	}

	//			Removing Methods
	void pop_front()
	{
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			//size--;
			size = 0;
			return;
		}
		Head = Head->pNext; // смещаем голову 
		delete Head->pPrev;
		Head->pPrev = nullptr;
		size--;
	}
	void pop_back()
	{
		if (Head == Tail)return pop_front();
		/*{
			delete Head;
			Head = Tail = nullptr;
			size = 0;
			return;
		}*/
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}

	//			Methods
	void print()
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
	}
	void revers_print()const
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
	}
};

List operator+(const List& left, const List& right)
{
	List cat = left;
	for (List::ConstIterator it = right.begin(); it != right.end(); ++it)
	{
		//*it *= 10;
		cat.push_back(*it);
	}
	return cat;
}


//#define Base_Check
#define Home_Work1
//#define Iterator_Perfomance
//#define ITERATORS_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef Base_Check
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
		//list.push_back(rand() % 100);
	}
	list.print();
	list.revers_print();
	//list.pop_front();
	/*list.~List();
	list.pop_front();
	list.pop_back();
	list.print();
	list.revers_print();*/

	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.print();
	list.revers_print();


	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();
	list.revers_print();
#endif // Base_Check
#ifdef Iterator_Perfomance

	clock_t t_start, t_end;
	int sum = 0;
	t_start = clock();
	List list(2000000);
	t_end = clock();
	cout << "Список создан за " << double(t_end - t_start) / CLOCKS_PER_SEC << " секунд\n";

	//List list = { 3,5,8,13,21 };
	//list.print();

#ifdef Home_Work1
	t_start = clock();
	for (int i : list)
	{
		//cout << i << tab;
		sum += i;
	}
	cout << endl;
	t_end = clock();
	cout << "Сумма найдена за " << double(t_end - t_start) / CLOCKS_PER_SEC << " секунд\n";
	cout << delimetr << endl;
	/*List::Iterator begin = list.begin();
	List::Iterator end = list.end();
	for (List::Iterator it = begin; it != end; ++it)*/
	int sum2 = 0;
	t_start = clock();
	for (List::Iterator it = list.begin(); it != list.end(); ++it)
	{
		//cout << *it << tab;
		sum2 += *it;
	}
	cout << endl;
	t_end = clock();
	cout << "Сумма найдена за " << double(t_end - t_start) / CLOCKS_PER_SEC << " секунд\n";
#endif // Home_Work1

#endif // Iterator_Perfomance

#ifdef ITERATORS_CHECK
	List list = { 3,5,8,13,21 };
	for (List::Iterator it = list.begin(); it != list.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;

	for (List::ReverseIterator it = list.rbegin(); it != list.rend(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // ITERATORS_CHECK

	List list1 = { 3,5,8,13,21 };
	List list2 = { 34,55,89 };
	List list3 = list1 + list2; //CopyConstructor, потому что мы создаем объект, а не создаваемый  

	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;

	for (List::Iterator it = list3.begin(); it != list3.end(); ++it)
	{
		*it *= 10;
	}
	for (int i : list3)cout << i << tab; cout << endl;

}