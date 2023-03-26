#pragma once


template<typename T>
class List
{
private:
	int num;
	struct node
	{
		T data;
		node* next;
		node* previous;
	};
	node* head;
	node* tail;
public:
	class iterator
	{
	private:
		node* ptr;
	public:
		iterator(node* ptr = nullptr)
			:ptr(ptr)
		{}
		iterator(const iterator& other)
		{
			ptr = other.ptr;
		}

		iterator& operator++()
		{
			ptr = ptr->next;
			return *this;
		}
		iterator& operator--()
		{
			if (ptr == nullptr)
			{
				ptr = tail;
				return *this;
			}
			ptr = ptr->previous;
			return *this;
		}
		T& operator*()
		{
			return ptr->data;
		}
		bool operator==(const iterator& other)
		{
			return ptr == other.ptr;
		}
		bool operator!=(const iterator& other)
		{
			return ptr != other.ptr;
		}
		void operator=(const iterator& other)
		{
			ptr = other.ptr;
		}
	};
	

	List();
	~List();
	iterator begin();
	iterator end();
	void add(T data);
	bool insert(T data, int index);//在第index后插入
	bool remove(int index);
	void clear();
	int size()const;
	void set(int index, T data);
	bool empty();
};

template<typename T>
inline List<T>::List()
	:head(new node), num(0)
{
	tail = head;
}

template<typename T>
inline List<T>::~List()
{
	clear();
	delete head;
}

template<typename T>
inline typename List<T>::iterator List<T>::begin()
{
	return iterator(head->next);
}//在List<T>前加上typename来保证依赖名称是一个类型

template<typename T>
inline typename List<T>::iterator List<T>::end()
{
	return iterator(tail->next);
}

template<typename T>
inline void List<T>::add(T data)
{
	node* newptr;
	newptr = new node{ data, nullptr, tail };
	tail->next = newptr;
	tail = newptr;
	num++;
	return;
}

template<typename T>
inline bool List<T>::insert(T data, int index)
{
	if (index > num)
	{
		return false;
	}
	else if (index == num)
	{
		add(data);
		return true;
	}

	node* nowptr = head;
	for (int i = 1; i <= index; i++)
	{
		nowptr = nowptr->next;
	}
	node* nextptr = nowptr->next;
	node* newptr = new node{ data, nullptr, nullptr };

	newptr->next = nextptr;
	newptr->previous = nowptr;
	nowptr->next = newptr;
	nextptr->previous = newptr;
	num++;
	return true;
}

template<typename T>
inline bool List<T>::remove(int index)
{
	if (index > num || index == 0)
	{
		return false;
	}
	else if (index == num)
	{
		node* nowptr = tail;
		tail = tail->previous;
		tail->next = nullptr;
		delete nowptr;
		num--;
		return true;
	}

	node* nowptr = head;
	for (int i = 1; i <= index; i++)
	{
		nowptr = nowptr->next;
	}
	node* nextptr = nowptr->next;
	node* previousptr = nowptr->previous;
	previousptr->next = nextptr;
	nextptr->previous = previousptr;

	nowptr->data.~T();
	delete nowptr;
	num--;

	return true;
}

template<typename T>
inline void List<T>::clear()
{
	while (num != 0)
	{
		remove(1);
	}
}

template<typename T>
inline int List<T>::size() const
{
	return num;
}

template<typename T>
inline void List<T>::set(int index, T data)
{
	if (index > num || index == 0)
	{
		throw "index out of range";
	}
	node* nowptr = head;
	for (int i = 1; i <= index; i++)
	{
		nowptr = nowptr->next;
	}
	nowptr->data = data;
}

template<typename T>
inline bool List<T>::empty()
{
	return num == 0;
}