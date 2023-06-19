#include<iostream>
#include<ctime>

using namespace std;
using std::cout;
using std::cin;
using std::endl;

//#define DEBUG
#define delimetr "\n--------------------------------------------------------\n"

class Tree
{
protected:
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr)
			:Data(Data), pLeft(pLeft), pRight(pRight)
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
		bool is_leaf()const
		{
			return pLeft == pRight;
		}
		friend class Tree;
		friend class UniqueTree;

	}*Root;
public:
	Element* getRoot()
	{
		return Root;
	}
	Tree() :Root(nullptr)
	{
		cout << "TConstructor:\t" << this << endl;
	}
	Tree(const std::initializer_list<int>& il) : Tree()
	{
		for (int i : il)insert(i, Root);
	}
	~Tree()
	{
		Clear(Root);
		Root = nullptr;
		cout << "TDestructor:\t" << this << endl;
	}
	
	// обертка 
	void insert(int Data)
	{
		insert(Data, Root);
	}
	int count()const
	{
		return count(Root);
	}
	int minValue()const
	{
		return minValue(Root);
	}
	int maxValue()const
	{
		return maxValue(Root);
	}
	void print()const // перегрузка функции  
	{
		print(Root);
		cout << endl;
	}
	int sum()const
	{
		return sum(Root);
	}
	double avg()const
	{
		return (double)sum(Root) / count(Root);
	}
	int depht()const
	{
		return depht(Root);
	}
private:
	void Clear(Element* Root)
	{
		if (Root == nullptr)return;
		Clear(Root->pLeft);
		Clear(Root->pRight);
		delete Root;
	}
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
	int minValue(Element* Root)const
	{
		if (Root == nullptr)return 0;
		/*if (Root->pLeft == nullptr)return Root->Data;
		else return minValue(Root->pLeft);*/
		return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
	}
	int maxValue(Element* Root)const
	{
		if (Root == nullptr)return 0;
		/*if (Root->pRight == nullptr)return Root->Data;
		else  return maxValue(Root->pRight);*/
		return Root->pRight == nullptr ? Root->Data : maxValue(Root->pRight);
	}
	int count(Element* Root)const
	{
		/*if (Root == nullptr)return 0;
		else return count(Root->pLeft) + count(Root->pRight) + 1; */
		return Root ? count(Root->pLeft) + count(Root->pRight) + 1 : 0;
		//return Root == nullptr ? 0: count(Root->pLeft) + count(Root->pRight) + 1; 
	}
	int sum(Element* Root)const
	{
		return Root == nullptr ? 0 : sum(Root->pLeft) + sum(Root->pRight) + Root->Data;
	}
	/*double avg(Element* Root)const
	{
		return Root == nullptr ? 0 : (sum(Root->pLeft) + sum(Root->pRight))/(count(Root->pLeft)+count (Root->pRight));
		return Root == nullptr ? 0 : sum(Root)/count(Root);
	}*/
	int depht(Element* Root)const
	{
		if (Root == nullptr)return 0; // ассоциативность слева на право
		int l_depht = depht(Root->pLeft) + 1;
		int r_depht = depht(Root->pRight) + 1;
		return l_depht > r_depht ? l_depht : r_depht;
		/*else return depht(Root->pLeft) > depht(Root->pRight) ?
			depht(Root->pLeft) + 1 :
			depht(Root->pRight) + 1;*/
			/*if (depht(Root->pLeft) > depht(Root->pRight))return depht(Root->pLeft) + 1;
			else return depht(Root->pRight) + 1;*/
	}
	int erase(int Data, Element* Root)
	{
		if (Root == nullptr)return 0;
		erase(Data, Root->pLeft);
		erase(Data, Root->pRight);
		if (Data == Root->Data)
		{
			if (Root->is_leaf()) // (Root->pLeft== Root->pRight) 2 вариант 
			{
				delete Root;
				Root = nullptr;
			}
			else 
		}
	}
	//			Methods: 
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << "\t";
		print(Root->pRight);
	}
};

class UniqueTree : public Tree
{
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else if (Data > Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
public:
	void insert(int Data)
	{
		insert(Data, Root);
	}
};
template <typename T>
void measure(const char desctription[], const Tree& tree, T(Tree::*member_function)()const)// desctription - строка массива char
{
	clock_t t_start = clock();
	cout << desctription << "\t" << (tree.*member_function)() << "\t";
	clock_t t_end = clock();
	cout << "выполнено за " << double(t_end - t_start) / CLOCKS_PER_SEC << " сек.\n";
}

//#define BASE_CHECK
#define DEPHT_CHECK
//#define PERFORMENCE_CHECK
void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "Введите размер дерева: "; cin >> n;
	Tree tree;
	cout << "Минимальное значение в дереве: " << tree.minValue() << endl;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	//tree.print(tree.getRoot());
	tree.print();
	cout << endl;
	cout << "Минимальное значение в дереве: " << tree.minValue() << endl;
	cout << "максимальное значение в дереве: " << tree.maxValue() << endl;
	cout << "Количество элементов в дереве: " << tree.count() << endl;
	cout << "Сумма элементов в дереве: " << tree.sum() << endl;
	cout << "Среднее-арифметическое элементов в дереве: " << tree.avg() << endl;
	cout << "Глубина дерева: " << tree.depht() << endl;
	UniqueTree u_tree;
	for (int i = 0; i < n; i++)
	{
		u_tree.insert(rand() % 100);
	}
	u_tree.print();
	cout << endl;
	cout << "Минимальное значение в дереве: " << u_tree.minValue() << endl;
	cout << "максимальное значение в дереве: " << u_tree.maxValue() << endl;
	cout << "Количество элементов в дереве: " << u_tree.count() << endl;
	cout << "Среднее-арифметическое элементов в дереве: " << u_tree.avg() << endl;
	cout << "Сумма элементов в дереве: " << u_tree.sum() << endl;
	cout << "Глубина дерева: " << u_tree.depht() << endl;

	//u_tree.print(u_tree.getRoot());

#endif // BASE_CHECK

#ifdef DEPHT_CHECK
	Tree tree = { 50,25,75,16,32,64,80,17,85,91 };
	tree.~Tree();
	tree.print();
	cout << "Глубина дерева: " << tree.depht() << endl;
#endif // DEPHT_CHECK

#ifdef PERFORMENCE_CHECK
	clock_t t_start, t_end; // тест по времени 
	int n;
	cout << "Введите размер дерева: "; cin >> n;
	Tree tree;
	t_start = clock(); // функция клок возвращает количество тактов проца
	//cout << "Минимальное значение в дереве: " << tree.minValue() << endl;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	t_end = clock();
	cout << "Дерево заполнено за " << double(t_end - t_start) / CLOCKS_PER_SEC << " сек.\n";

	measure("Минимальное значение в дереве: ", tree, &Tree::minValue);
	measure("Максимальное значение в дереве:", tree, &Tree::maxValue);
	measure("Сумма элементов дерева:", tree, &Tree::sum);
	measure("Количества элементов дерева:", tree, &Tree::count);
	measure("Среднее-арифметичское элементов дерева:", tree, &Tree::avg);
	measure("Глубина дерева", tree, &Tree::depht);

	
	////tree.print(tree.getRoot());
	////tree.print();
	//t_start = clock();
	//cout << "Минимальное значение в дереве: " << tree.minValue() << "\t";
	//t_end = clock();
	//cout << double(t_end - t_start) / CLOCKS_PER_SEC << " сек.\n";

	//t_start = clock();
	//cout << "максимальное значение в дереве: " << tree.maxValue() << "\t";
	//t_end = clock();
	//cout << double(t_end - t_start) / CLOCKS_PER_SEC << " сек.\n";

	//t_start = clock();
	//cout << "Количество элементов в дереве: " << tree.count() << "\t";
	//t_end = clock();
	//cout << double(t_end - t_start) / CLOCKS_PER_SEC << " сек.\n";

	//t_start = clock();
	//cout << "Сумма элементов в дереве:\t " << tree.sum() << "\t";
	//t_end = clock();
	//cout << double(t_end - t_start) / CLOCKS_PER_SEC << " сек.\n";

	//t_start = clock();
	//cout << "Среднее-арифметическое элементов в дереве: " << tree.avg() << "\t";
	//t_end = clock();
	//cout << double(t_end - t_start) / CLOCKS_PER_SEC << " сек.\n";

	//t_start = clock();
	//cout << "Глубина дерева: " << tree.depht() << "\t";
	//t_end = clock();
	//cout << double(t_end - t_start) / CLOCKS_PER_SEC << " сек.\n";
#endif // PERFORMENCE_CHECK

}