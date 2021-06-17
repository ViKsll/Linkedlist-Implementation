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
	void push_front(T data); // add a new element to the beginning of the List                
	void insert(T data, int index); // inserting element in the middle of List                                                                           
	void removeAt(int index); // deleting element at the specified index                     
	void pop_back(); // deleting last element                          

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

template<typename T>
void List<T>::push_front(T data) // implementation of push_front method                                        
{
	head = new Node<T>(data, head); // creating new element to the beggining of List and adding data                
	Size++; // increase size of the List
}

template<typename T>
void List<T>::insert(T data, int index) // implementation of insert method                                       
{
	if (index == 0)
	{
		push_front(data);
	}
	else
	{
		Node<T>* previous = this->head; // creating temporary pointer(previous) and assign "head" to it
		for (int i = 0; i < index - 1; i++) // finding previous element of index 
		{
			previous = previous->pNext; // then assign the address of next element to a new previous element
		}
		Node<T>* newNode = new Node<T>(data, previous->pNext); // creating new element and passing data to the constructor
		previous->pNext = newNode; // the address of the next element is added to our new current element
		Size++;
	}
}

template<typename T>
void List<T>::removeAt(int index)                                                                              
{
	if (index == 0)
	{
		pop_front();
	}
	else
	{
		Node<T>* previous = this->head; 
		for (int i = 0; i < index - 1; i++) 
		{
			previous = previous->pNext; // finding previous element and assign the adress of the next element
		}
		Node<T>* toDelete = previous->pNext; // creating temporary pointer(toDelete) and assign address of our old element that pointed to the next element
		previous->pNext = toDelete->pNext; // then adress of previous element points to the next element(exclusing element that has to be removed)
		delete toDelete;
		Size--;
	}
}

template<typename T>
void List<T>::pop_back()                                                                    
{
	remove(Size - 1);
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
	
	lst.push_front(11); // now 11 will be first number in the List                                                      
	cout << lst.GetSize() << endl; 

	lst.insert(99, 2); // adding element 99 as the third number in the List                                             
	cout << lst.GetSize() << endl;

	lst.removeAt(1); // deleting second element                                                                         
	cout << lst.GetSize() << endl;

	lst.pop_back(); // removed the last element                                                                          
	cout << lst.GetSize() << endl;
	
	lst.clear(); // clear data from dynamic memory. not necessary use it here since we added this to destructor
	cout << lst.GetSize() << endl;

	return 0;
}


