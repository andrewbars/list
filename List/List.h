#ifndef LIST_H
#define LIST_H
#include <functional>
#include <initializer_list>

template <typename U, typename T>
T& operator>>(const U& newElem, T& list);

template <typename T>
class List{
	typedef std::function<bool(char)> Condition;

	struct Node
	{
		T data;
		Node* prev;
		Node* next;
		Node(T data, Node* prev=nullptr, Node* next=nullptr) : data(data), prev(prev), next(next){};
	};

	Node* head;
	Node* tail;
	int length;
public:
	List() : head(nullptr), tail(nullptr), length(0){};
	List(const List &that)
	{
		if (that.length)
		{
			length = that.length;
			head = new Node(that.head->data);
			tail = head;
			Node* tmp = that.head->next;
			while (tmp)
			{
				tail->next = new Node(tmp->data, tail);
				tail = tail->next;
				tmp = tmp->next;
			}
		}
		else
		{
			length = 0;
			head = tail = nullptr;
		}
	}
	List(List &&that)
	{
		head = that.head;
		tail = that.tail;
		length = that.length;
		that.head = nullptr;
		that.tail = nullptr;
	}
	List(std::initializer_list<T> il) :head(nullptr), tail(nullptr), length(0)
	{
		for (auto p = il.begin(); p != il.end(); p++)
		{
			if (head)
			{
				tail->next = new Node(*p,tail);
				tail = tail->next;
			}
			else
			{
				head = new Node(*p);
				tail = head;
			}
			length++;
		}
	}
	~List()
	{
		while (head)
		{
			Node* nextElem = head->next;
			delete head;
			head = nextElem;
		}
	}

	bool isEmpty() const 
	{
		return !head;
	}
	bool nonEmpty() const 
	{
		return head;
	}
	int Length() const  
	{
		return length;
	}

	List&  operator=(const List& that)
	{
		if (length > 0)
		{
			while (head)
			{
				Node* nextElem = head->next;
				delete head;
				head = nextElem;
			}
		}
		if (that.length)
		{
			length = that.length;
			head = new Node(that.head->data);
			tail = head;
			Node* tmp = that.head->next;
			while (tmp)
			{
				tail->next = new Node(tmp->data, tail);
				tail = tail->next;
				tmp = tmp->next;
			}
		}
		else
		{
			length = 0;
			head = tail = nullptr;
		}
		return *this;
	}
	List& operator=(List &&that)
	{
		if (length > 0)
		{
			while (head)
			{
				Node* nextElem = head->next;
				delete head;
				head = nextElem;
			}
		}
		head = that.head;
		tail = that.tail;
		length = that.length;
		that.head = nullptr;
		that.tail = nullptr;
		return *this;
	}

	List& Add(const T &newElem, int pos)
	{
		if (pos > length || pos < 0)
			throw "Index out of bonds";
		if (length == 0)
		{
			head = tail = new Node(newElem);
		}
		else if (pos == 0)
		{
			head = new Node(newElem, nullptr, head);
			head->next->prev = head;
		}
		else if (pos == length)
		{
			tail = new Node(newElem, tail, nullptr);
			tail->prev->next = tail;
		}
		else
		{
			int count = 0;
			Node*tmp = head;
			while (count < pos)
			{
				count++;
				tmp = tmp->next;
			}
			tmp = new Node(newElem, tmp, tmp->next);
			tmp->prev->next = tmp->next->prev = tmp;
		}
		length++;
		return *this;
	}
	List& AddFirst(const T &newElem)
	{
		return Add(newElem, 0);
	}
	List& AddLast(const T &newElem)
	{
		return Add(newElem, length);
	}
	List& operator<<(const T &newElem)
	{
		return AddLast(newElem);
	}
	friend List& operator>><>(const T& newElem, List& list);

	List& RemoveAt(int pos)
	{
		if (length == 0)
			throw "List is already empty";
		if (pos > length-1 || pos < 0)
			throw "Index out of bonds";
		if (pos == 0)
		{
			head = head->next;
			delete head->prev;
			head->prev = nullptr;
		}
		else if (pos == length-1)
		{
			tail = tail->prev;
			delete tail->next;
			tail->next = nullptr;
		}
		else
		{
			int count = 0;
			Node*tmp = head;
			while (count < pos)
			{
				count++;
				tmp = tmp->next;
			}
			tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;
			delete tmp;
		}
		length--;
		return *this;
	}
	List& Remove(T elem)
	{
		if (length == 0)
			return *this;
		int count = 0;
		Node* tmp = head;
		while (count < length)
		{
			Node* nextElem = tmp->next;
			if (tmp->data == elem)
			{
				RemoveAt(count);
			}
			tmp = nextElem;
			count++;
		}
		return *this;
	}
	List& RemoveFirst()
	{
		return RemoveAt(0);
	}
	List& RemoveLast()
	{
		return RemoveAt(length - 1);
	}

	List& Concat(const List& that)
	{
		List tmp = that;
		tail->next = tmp.head;
		tail = tmp.tail;
		length += tmp.length;
		tmp.head = tmp.tail = nullptr;
		return *this;
	}
	List& Concat(T* arr, int arrLength)
	{
		for (int i = 0; i < arrLength, i++)
		{
			AddLast(arr[i]);
		}
		return *this;
	}

	T& Head()
	{
		return head->data;
	}
	const T& Head() const 
	{
		return head->data;
	}
	T& Tail()
	{
		return tail->data;
	}
	const T& Tail() const
	{
		return tail->data;
	}
	T& operator[](int index)
	{
		if (index<0 || index>length - 1)
			throw "Index out of bonds";
		if (index == 0)
			return head->data;
		else if (index == length - 1)
			return tail->data;
		else
		{
			int count = 0;
			Node* tmp=head;
			while (count < index)
			{
				count++;
				tmp = tmp->next;
			}
			return tmp->data;
		}
	}
	const T& operator[](int index) const 
	{
		if (index<0 || index>length - 1)
			throw "Index out of bonds";
		if (index == 0)
			return head->data;
		else if (index == length - 1)
			return tail->data;
		else
		{
			int count = 0;
			Node* tmp = head;
			while (count < index)
			{
				count++;
				tmp = tmp->next;
			}
			return tmp->data;
		}
	}
	List Take(int num)const 
	{
		if (num >= length)
			return *this;
		List tmp;
		int count = 0;
		Node* toCopy = head;
		while (count < num)
		{
			tmp << toCopy->data;
			toCopy = toCopy->next;
			count++;
		}
		return tmp;
	}
	List Drop(int num) const 
	{
		if (num <= 0)
			return *this;
		List tmp;
		int count = 0;
		Node* toCopy = head;
		while (count < length)
		{
			if (count >= num)
				tmp << toCopy->data;
			toCopy = toCopy->next;
			count++;
		}
		return tmp;
	}
	List TakeRight(int num) const 
	{
		return Drop(length - num);
	}
	List DropRight(int num) const 
	{
		return Take(length - num);
	}
	List TakeWhile(Condition f) const 
	{
		List newList;
		Node* tmp = head;
		while (f(tmp->data))
		{
			newList << tmp->data;
			tmp = tmp->next;
		}
		return newList;
	}
	List DropWhile(Condition f) const 
	{
		List newList;
		Node* tmp = head;
		while (f(tmp->data))
		{
			tmp = tmp->next;
		}
		while (tmp)
		{
			newList << tmp->data;
			tmp = tmp->next;
		}
		return newList;
	}
	List TakeRightWhile(Condition f) const 
	{
		List newList;
		Node* tmp = tail;
		while (f(tmp->data))
		{
			tmp->data>>newList;
			tmp = tmp->prev;
		}
		return newList;
	}
	List DropRightWhile(Condition f) const 
	{
		List newList;
		Node* tmp = tail;
		while (f(tmp->data))
		{
			tmp = tmp->prev;
		}
		while (tmp)
		{
			tmp->data >> newList;
			tmp = tmp->prev;
		}
		return newList;
	}

	List Filter(Condition f) const 
	{
		if (length == 0)
			return *this;
		List newList;
		Node* tmp=head;
		while (tmp)
		{
			if (f(tmp->data))
				newList << tmp->data;
			tmp = tmp->next;
		}
		return newList;
	}
	List  FilterNot(Condition f) const 
	{
		if (length == 0)
			return *this;
		List newList;
		Node* tmp = head;
		while (tmp)
		{
			if (!f(tmp->data))
				newList << tmp->data;
			tmp = tmp->next;
		}
		return newList;
	}

	bool exists(Condition f) const 
	{
		Node* tmp = head;
		while (tmp)
		{
			if (f(tmp->data))
				return true;
			tmp = tmp->next;
		}
		return false;
	}
	bool ForAll(Condition f) const 
	{
		if (length == 0)
			return false;
		Node* tmp = head;
		while (tmp)
		{
			if (!f(tmp->data))
				return false;
			tmp = tmp->next;
		}
		return true;
	}

	int IndexWhere(Condition f) const 
	{
		if (length == 0)
			return -1;
		Node* tmp = head;
		int count = 0;
		while (tmp)
		{
			if (f(tmp->data))
				return count;
			tmp = tmp->next;
			count++;
		}
		return -1;
	}
	int IndexOf(const T& item) const 
	{
		return IndexWhere([item](T x){return x == item; });
	}
	int LastIndexWhere(Condition f) const 
	{
		if (length == 0)
			return -1;
		Node* tmp = tail;
		int count = length-1;
		while (tmp)
		{
			if (f(tmp->data))
				return count;
			tmp = tmp->prev;
			count--;
		}
		return -1;
	}
	int LastIndexOf(const T& item) const 
	{
		return LastIndexWhere([item](T x){return x == item; });
	}

};


template <typename U, typename T>
T& operator>>(const U& newElem, T& list)
{
	return list.AddFirst(newElem);
}


#endif