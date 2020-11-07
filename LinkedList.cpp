#include <iostream>
using namespace std;

template<class Object>
class List;

template<class Object>
class ListItr;

template <class Object>
class ListNode
{
	ListNode(const Object& theElement = Object(), ListNode* n = NULL)
		: element(theElement), next(n) {}

	Object element;
	ListNode* next;

	friend class List<Object>;
	friend class ListItr<Object>;

};

template<class Object>
class ListItr
{
public:
	ListItr() : current(NULL)

	{
	}

	bool isPastEnd() const
	{
		return current == NULL;
	}

	void advance()
	{
		if (!isPastEnd())
			current = current->next;
	}
	const Object& retrieve() const
	{
		if (isPastEnd())
			//throw BadIterator();
			return NULL;

		return current->element;
	}

private:
	ListNode<Object>* current;

	ListItr(ListNode<Object>* theNode) : current(theNode) { }
	friend class List<Object>;
};

template<class Object>
class List
{
public:
	List();
	List(const List& rhs);
	~List();

	bool isEmpty() const;
	void makeEmpty();
	ListItr<Object> zeroth() const;
	ListItr<Object> first() const;
	void insert(const Object& x, const ListItr<Object>& p);
	ListItr<Object> find(const Object& x) const;
	ListItr<Object> findPrevious(const Object& x) const;
	int remove(const Object& x);
	//void findAddress(const Object& x) const;//for find address 

	const List& operator=(const List& rhs);

private:
	ListNode<Object>* header;
};

template <class Object>
List<Object>::List()
{
	header = new ListNode<Object>;
}

template <class Object>
bool List<Object>::isEmpty() const
{
	return header->next == NULL;
}

template <class Object>
ListItr<Object> List<Object>::zeroth() const
{
	return ListItr<Object>(header);
}

template <class Object>
ListItr<Object> List<Object>::first() const
{
	return ListItr<Object>(header->next);
}


template<class Object>
ListItr<Object> List<Object>::find(const Object& x) const
{
	ListNode<Object>* itr = header->next;

	while (itr != NULL && itr->element != x)
		itr = itr->next;
	return ListItr<Object>(itr);
}

/*template <class Object>
void List<Object>::findAddress(const Object& x) const {
	ListNode<Object>* itr = header->next;

	while (itr != NULL && itr->element != x)
		itr = itr->next;
	cout << itr << endl;
}*/


template <class Object>
int List<Object>::remove(const Object& x)
{
	ListItr<Object> p = findPrevious(x);

	if (p.current->next != NULL)
	{
		ListNode<Object>* oldNode = p.current->next;
		p.current->next = p.current->next->next;
		delete oldNode;
		return 1;//for tell main deleted
	}
	return 0;//for tell main not deleted
}

template <class Object>
ListItr<Object> List<Object>::findPrevious(const Object& x) const
{
	ListNode<Object>* itr = header;

	while (itr->next != NULL && itr->next->element != x)
		itr = itr->next;
	return ListItr<Object>(itr);
}

template<class Object>
void List<Object>::insert(const Object& x, const ListItr<Object>& p)
{
	if (p.current != NULL)
		p.current->next = new ListNode<Object>(x, p.current->next);
}

template <class Object>
void List<Object>::makeEmpty()
{
	while (!isEmpty())
		remove(first().retrieve());
}

template<class Object>
List<Object>::~List()
{
	makeEmpty();
	delete header;
}

template<class Object>
void printList(const List<Object>& theList) {
	if (theList.isEmpty()) {
		cout << "------------------" << endl;
		cout << " -- Empty list --" << endl;
		cout << "------------------" << endl;
	}
	else {
		ListItr<Object> itr = theList.first();
		for (;!itr.isPastEnd();itr.advance())
			cout << itr.retrieve() << " ";
	}
	cout << endl;
	system("pause");
}

int main() {

	int choi = 0;//for user select choice in main menu
	int element;//for user input element
	int count = 0;//count of position
	List<int> a;
	ListItr<int> b;
	ListItr<int> X; //for menu find //for keep *current that is element from user find 
	b = a.zeroth();
	do {
		system("cls");
		cout << "1.Insert" << endl;
		cout << "2.PrintList" << endl;
		cout << "3.Find" << endl;
		cout << "4.Remove" << endl;
		cout << "5.Quit" << endl;
		cout << "---------------" << endl;
		cout << "Enter choice: ";
		cin >> choi;

		if (choi < 5) {
			switch (choi) {
			case 1:
				int choi1;
				do {
					system("cls");
					cout << "---------------" << endl;
					cout << "1.Insert Front " << endl;
					cout << "2.Insert Back" << endl;
					cout << "---------------" << endl;
					cout << "Enter choice: ";
					cin >> choi1;
				} while (choi1 > 2);
				if (choi1 == 1) {
					cout << "Enter element : ";
					cin >> element;
					a.insert(element, b);
					//not use b = a.zeroth because b(current) still header
					count++;
				}
				else {
					cout << "Enter element : ";
					cin >> element;
					b = a.findPrevious(NULL);//b(current) to tail list
					a.insert(element, b);//insert to back tail
					b = a.zeroth();  //b(current) back to header
					count++;
				}
				break;

			case 2:
				system("cls");
				if (count>0) {
					cout << "List has " << count << " element" << endl;
				}
				printList(a);
				break;

			case 3:
				int choi2;
				system("cls");
				cout << "-----------" << endl;
				cout << " 1.Find " << endl;
				cout << " 2.Findkth " << endl;
				cout << "-----------" << endl;
				cout << "Enter choice: ";
				cin >> choi2;
				if (choi2 == 1) {
					cout << "-----------------------------------" << endl;
					cout << " What element do you want to find?" << endl;
					cout << "-----------------------------------\n" << endl;
					cout << "Enter element :";
					cin >> element;
					X = a.find(element);//X(current) = first element found in list 
					int position;//for count position of element
					position = 1;
					if (X.retrieve() == NULL) {
						cout << "\n---Find not found---\n" << endl;
					}
					else if (X.retrieve() != NULL) {
						b.advance();	//change b(current) from header to list position 1
						while (X.retrieve() != b.retrieve()) { //loop for find position
							b.advance();
							position++;
						}
						cout << "Found " << element << " in position " << position << endl << endl;

					}
					system("pause");
					b = a.zeroth();
				}
				else {
					/*
					cout << "Enter element:";
					cin >> element;
					cout << "element " << element << " is in the Node address ";
					a.findAddress(element);*/
					int pos;
					if (count > 0) {
						do {
							cout << "Enter Position (Less than " << count + 1 << " ):" ;
							cin >> pos;
							if (pos > count) {
								cout << "Don't Position.Please Input Again." << endl;
							}
						} while (pos > count);
						b = a.first();//b(current) to list position 1
						if (pos > 1) {
							for (int i=1;i < pos;i++) {
								b.advance();
							}
						}
						cout << "In position " << pos << " have element " << b.retrieve() << endl;
						//cout << " Thia element ("<<b.retrieve()<<") is position "<<i;
						b = a.zeroth();
						system("pause");
					}
					
				}
				break;

			case 4:
				system("cls");
				cout << "-------------------------------------" << endl;
				cout << " What element do you want to remove?" << endl;
				cout << "-------------------------------------\n" << endl;
				cout << "Enter element: ";
				cin >> element;
				if (a.remove(element)) {
					count--;
					cout << element << " removed from list\n" << endl;
				}
				else {
					cout << "Can't be removed\n " << element << " not in the list\n" << endl;
				}
				system("pause");
				break;
			default:
				break;
			}
		}

	} while (choi != 5);
	return 0;


}

