#include "List.h"
#include <iostream>

using namespace std;

void main()
{
	List<int> l;
	for (int i = 0; i < 10; i++)
		l << i;
	for (int i = 0; i < 10; i++)
		cout << l[i] << ' ';
	List<int> ls;
	for (int i = 10; i < 20; i++)
		ls << i;
	cout << endl;
	l.Concat(ls);
	for (int i = 0; i < 20; i++)
		cout << l[i] << ' ';
	cout << endl;
	List<int> xs = l.DropRightWhile([](int x){return x > 16; });
	for (int i = 0; i < xs.Length(); i++)
	{
		cout << xs[i] << ' ';
	}
	cout << endl;
	l = xs;
	for (int i = 0; i < l.Length(); i++)
	{
		cout << l[i] << ' ';
	}

	const List<int> cs = xs;
	cout << cs[1];
	cout << endl;
	cout << l.IndexOf(15);
	cout << endl;
}
