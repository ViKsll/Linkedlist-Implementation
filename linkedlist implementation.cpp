#include <iostream>
#include <string>
using namespace std;

template<typename T>
class List
{
public:
	List();
	~List();
	
        void pop_front();  // delete first element
	void push_back(T data);
	void clear(); // remove data from List
	int GetSize() { return Size; }

	T& operator[](const int index); // to get a access to one of the elements

private:

	template<typename T>
	class Node // class of elements of the class List
	{
	public:
		Node* pNext; // pointer to next element
		T data;
		Node(T data = T(), Node* pNext = nullptr) // constructor
		{
			this->data = data;
			this->pNext = pNext;
		}
	};

	int Size; // for the number of elements in the List
	Node<T>* head; // has to be pointer because we take data from dynamic memory
};

template<typename T>
List<T>::List()
{
	Size = 0;
	head = nullptr;
}

template<typename T>
List<T>::~List()
{
    clear(); // remove data from List
}

template<typename T> // implementation of pop_front method
List<T>::pop_front()
{
	Node<T> *temp = head; // assign the very first element(head) to temporary variable
	head = head->pNext; // assign the very first element(head) to the second element
	delete temp; // delete the very first element(head)
	Size--; // now we have one less element
}

template<typename T>
void List<T>::push_back(T data) // adding a new element at the end of the List
{
	if (head == nullptr) // checking it "head" is empty
	{
		head = new Node<T>(data); // if yes, we creating new element with data
	}
	else
	{
		Node<T>* current = this->head;

		while (current->pNext != nullptr)
		{
			current = current->pNext; // we assign in this field a pointer to next element
		}
		current->pNext = new Node<T>(data); // assign a new element instead of nullptr
	}
	Size++;
}

template<typename T> 
void List<T>::clear() // implementation of clear() method
{
	while (Size) // while Size > 0 we use while loop until we delete all the elements from List
	{
		pop_front();
	}
}

template<typename T>
T& List<T>::operator[](const int index)
{
	int counter = 0;
	Node<T>* current = this->head; // indicates which specific element we are currently in
	while (current != nullptr) // it works until it gets null
	{
		if (counter == index) 
		{
			return current->data; 
		}
		current = current->pNext; // if counter != index, we ask address of the next element from current element
		counter++; // increasing counter by 1 as we go to the next element
	}
}

int main()
{
	List<int> lst;
	lst.push_back(5);
	lst.push_back(10);
	lst.push_back(22);

	cout << lst.GetSize() << endl; // numbers of elements in the List

	cout << lst[2] << endl << endl; // getting a value of the second element in List

	for (int i = 0; i < lst.GetSize(); i++) // getting all elements from List usung a loop
	{
		cout << lst[i] << endl;
	}
	cout << endl;


	int numbersCount;
	cin >> numbersCount;
	for (int i = 0; i < numbersCount; i++) // filling the List using random numbers
	{
		lst.push_back(rand() % 10);
	}

	for (int i = 0; i < lst.GetSize(); i++) // getting all elements from List usung a loop
	{
		cout << lst[i] << endl;
	}
	
	lst.clear(); // clear data from dynamic memory. not necessary use it here since we added this to destructor
	cout << lst.GetSize() << endl;

	return 0;
}


