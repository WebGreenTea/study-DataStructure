#include <iostream>
#include <iomanip>
#include <vector>
#include <String>
using namespace std;

template <class HashedObj>
class HashTable {
public:
	explicit HashTable(const HashedObj& notFound, int size = 101);
	HashTable(const HashTable& rhs)
		:ITEM_NOT_FOUND(rhs.ITEM_NOT_FOUND), array(rhs.array), currentSize(rhs.currentSize) {}

	const HashedObj& find(const HashedObj& x);

	void makeEmpty();
	void insert(const HashedObj& x);
	void remove(const HashedObj& x);

	const HashTable& operator=(const HashTable& rhs);

	enum EntryType { ACTIVE, EMPTY, DELETED };
	
	//new
	int nextPrime(int x);
	bool isPrime(int x);
	int beforePrime(int x);
	void createtable(int size);
	void printHash();
private:
	struct HashEntry
	{
		HashedObj element;
		EntryType info;
		HashEntry(const HashedObj& e = HashedObj(), EntryType i = EMPTY) :element(e), info(i) {}
	};

	vector<HashEntry> array;
	int currentSize;
	const HashedObj ITEM_NOT_FOUND;

	bool isActive(int currentPos)const;
	int findPos(const HashedObj& x);
	void rehash();
	
	//new
	int hash(int x, int size)const;
	int hash2(int x);
	
};

template <class HashedObj>
HashTable<HashedObj>::HashTable(const HashedObj& notFound, int size) :ITEM_NOT_FOUND(notFound), array(nextPrime(size)) {
	makeEmpty();
}

template <class HashedObj>
void HashTable<HashedObj>::makeEmpty() {
	currentSize = 0;
	for (int i = 0; i < array.size(); i++) {
		array[i].info = EMPTY;
		array[i].element = NULL;
	}
}

template <class HashedObj>
const HashedObj& HashTable<HashedObj>::find(const HashedObj& x) {
	int currentPos = findPos(x);
	if (isActive(currentPos)) {
		return array[currentPos].element;
	}
	else {
		return ITEM_NOT_FOUND;
	}
}

template <class HashedObj>
int HashTable<HashedObj>::findPos(const HashedObj& x) {
	int collisionNum = 0;
	int currentPos = hash(x, array.size());

	while (array[currentPos].info != EMPTY && array[currentPos].element != x) {
		currentPos = hash(x, array.size()) + (++collisionNum * hash2(x));
		//currentPos += 2 * ++collisionNum - 1;
		if (currentPos >= array.size()) {
			currentPos %= array.size();
		}
	}
	return currentPos;
}

template <class HashedObj>
bool HashTable<HashedObj>::isActive(int currentPos)const {
	return array[currentPos].info == ACTIVE;
}

//REMOVE
template <class HashedObj>
void HashTable<HashedObj>::remove(const HashedObj& x) {
	int currentPos = findPos(x);
	if (isActive(currentPos)) {
		array[currentPos].info = DELETED;
		currentSize--;
		cout << "\n\tDeleted successfully\n" << endl;
	}
	else {
		cout << "Not Found" << endl;
		cout << "Can not be deleted" << endl;
	}
}

//INSERT
template <class HashedObj>
void HashTable<HashedObj>::insert(const HashedObj& x) {
	int currentPos = findPos(x);
	if (isActive(currentPos)) {//duplicate data
		return;
	}
	array[currentPos] = HashEntry(x, ACTIVE);
	//array[currentPos].element = x;
	//array[currentPos].info = ACTIVE;

	if (++currentSize > array.size() *0.7) {
		rehash();
	}
}

template <class HashedObj>
void HashTable <HashedObj>::rehash() {
	vector<HashEntry> oldTable = array;

	array.resize(nextPrime(2 * oldTable.size()));
	makeEmpty();

	for (int i = 0; i < oldTable.size(); i++)
		if (oldTable[i].info == ACTIVE)
			insert(oldTable[i].element);
}

/*template <class HashedObj>
const HashTable<HashedObj>& HashTable<HashedObj>::operator=(const HashTable& rhs) {
	if (this != &rhs) {
		array = rhs.array;
		currentSize = rhs.currentSize;
	}
	return *this;
}*/

//-------------------HASH-------------------
template <class HashedObj>
int HashTable<HashedObj>::hash(int x, int size)const {
	int M = x % size;
	return M;
}
template <class HashedObj>
int HashTable<HashedObj>::hash2(int x) {
	int r = beforePrime(array.size());
	return r - (x % r);
}

//-------------------PRIME-------------------
template <class HashedObj>
int HashTable<HashedObj>::nextPrime(int x) {
	if (isPrime(x)) {
		return x;
	}
	else {
		x++;
		while (!isPrime(x)) {
			x++;
		}
		return x;
	}

}
template <class HashedObj>
bool HashTable<HashedObj>::isPrime(int n) {
	bool isPrime = true;
	if (n == 1) {
		isPrime = false;
		return isPrime;
	}
	for (int i = 2; i <= n / 2; i++) {
		if (n % i == 0)
		{
			isPrime = false;
			break;
		}
	}
	return isPrime;
}
template <class HashedObj>
int HashTable<HashedObj>::beforePrime(int x) {
	--x;
	while (!isPrime(x)) {
		--x;
	}
	//cout << x;
	return x;
}
//-------------------CREATE-------------------
template <class HashedObj>
void HashTable<HashedObj>::createtable(int size) {
	array.resize(size);
	makeEmpty();
}
//-------------------PRINT-------------------
template <class HashedObj>
void HashTable<HashedObj>::printHash() {
	cout << "\t-------------------------------------------------" << endl;
	cout << "\t--------------------HashTable--------------------" << endl;
	cout << "\t-------------------------------------------------" << endl;
	cout << "\t[ " << setw(8) << "Position" << " ]" << setw(8);
	cout << " [" << setw(8) << " Element" << " ]" << setw(11);
	cout << "[ " << " Info" << "  ]" << endl;
	cout << "\t-------------------------------------------------" << endl;

	for (int i = 0; i < array.size(); i++) {
		string INFO = (array[i].info == 0) ? "ACTIVE" : (array[i].info == 1) ? "EMPTY" : "DELETED";
		cout << "\t[   " << setw(3) << i << "    ]" << setw(8);
		if (array[i].element == NULL) {
			cout << " [" << setw(8) << "-" << " ]" << setw(11);
		}
		else {
			cout << " [" << setw(8) << array[i].element << " ]" << setw(11);
		}
		cout << "[" << setw(7) << INFO << " ]" << endl;
	}
	cout << "\t-------------------------------------------------" << endl;
	cout << "\t Table size [ " << array.size() << " ]" << endl;
	cout << "\t Amount of data in the hashTable [ " << currentSize <<" ]" << endl;
	
}
int main() {
	char choi;
	HashTable<int> a(-999);
	int elementin;
	int temp;
	do {
		system("cls");
		cout << "\t-----Hashing-----\n";
		cout << "\t 1.Create Hash Table\n";
		cout << "\t 2.Insert\n";
		cout << "\t 3.Print\n";
		cout << "\t 4.Remove\n";
		cout << "\t 5.Find\n";
		cout << "\t 6.Quit\n";
		cout << "\nEnter choice:";
		cin >> choi;
		if (choi == '6') {
			break;
		}
		else if (choi == '1') {
			int size;
			system("cls");
			cout << "----Create Hash Table----\n";
			cout << " Enter Table Size: ";
			cin >> size;
			if (a.isPrime(size)) {
				a.createtable(size);
				cout << "-----------------------------------------------\n\n";
				cout << " Successfully created a hash table of size " << size << endl << endl;
				cout << "-----------------------------------------------\n";
			}
			else {
				temp = a.nextPrime(size);
				cout <<"\n  "<< size << " is not a prime number" << endl;
				cout << "\n  next prime number is " << temp << endl;
				a.createtable(temp);
				cout << "-----------------------------------------------\n\n";
				cout << " Successfully created a hash table of size " << temp << endl << endl;
				cout << "-----------------------------------------------\n";
			}
			system("pause");
		}
		else if (choi == '2') {
			system("cls");
			cout << "----Insert----\n";
			cout << "Insert :";
			cin >> elementin;
			a.insert(elementin);
			cout << "\n\tSuccessfully inserted\n" << endl;
			system("pause");
		}
		else if (choi == '3') {
			system("cls");
			a.printHash();
			cout << endl;
			system("pause");
		}
		else if (choi == '4') {
			system("cls");
			cout << "----Remove----\n";
			cout << "Remove :";
			cin >> elementin;
			a.remove(elementin);
			system("pause");
		}
		else if (choi == '5') {
			int FIND;
			system("cls");
			cout << "----Find----\n";
			cout << "Find :";
			cin >> elementin;
			FIND = a.find(elementin);
			if (FIND == -999) {
				cout << "  Find not found\n";
			}
			else {
				cout << "  Found " << elementin << " in hash table" << endl;
			}
			system("pause");
		}
	} while (true);
	return 0;
}