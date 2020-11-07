#include <iostream>
using namespace std;

template<class Comparable>
class BinarySearchTree;

template <class Comparable>
class BinaryNode {
	Comparable element;
	BinaryNode* left;
	BinaryNode* right;

	BinaryNode(const Comparable& theElement, BinaryNode* lt, BinaryNode* rt) :
		element(theElement), left(lt), right(rt) {}
	friend class BinarySearchTree <Comparable>;
};

template<class Comparable>
class BinarySearchTree {
public:
	explicit BinarySearchTree(const Comparable& notFound);
	BinarySearchTree(const BinarySearchTree& rhs);
	//~BinarySearchTree();

	const Comparable& findMin()const;
	const Comparable& findMax()const;
	const Comparable& find(const Comparable& x)const;

	bool isEmpty()const;
	void printTree(char choi)const;
	void makeEmpty();

	void insert(const Comparable& x);
	void remove(const Comparable& x);
	const BinarySearchTree& operator=(const BinarySearchTree& rhs);

private:
	BinaryNode<Comparable>* root;
	const Comparable ITEM_NOT_FOUND;

	const Comparable& elementAt(BinaryNode<Comparable>* t)const;
	void insert(const Comparable& x, BinaryNode<Comparable>*& t)const;
	void remove(const Comparable& x, BinaryNode < Comparable>*& t)const;

	BinaryNode<Comparable>* findMin(BinaryNode< Comparable>* t)const;
	BinaryNode< Comparable>* findMax(BinaryNode< Comparable>* t)const;
	BinaryNode< Comparable>* find(const Comparable& x, BinaryNode< Comparable>* t)const;

	void makeEmpty(BinaryNode< Comparable>*& t)const;
	void printTree(BinaryNode< Comparable>* t,char choi)const;

	BinaryNode< Comparable>* clone(BinaryNode<Comparable>* t)const;
};
template <class Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(const Comparable& notFound) : ITEM_NOT_FOUND(notFound) { root = NULL; }

template <class Comparable>
const Comparable& BinarySearchTree< Comparable>::elementAt(BinaryNode< Comparable>* t)const {
	if (t == NULL)
		return ITEM_NOT_FOUND;
	else
		return t->element;
}
template <class Comparable>
bool BinarySearchTree< Comparable>::isEmpty()const {
	return root == NULL;
}

//FIND
template <class Comparable>
const Comparable& BinarySearchTree< Comparable>::find(const Comparable& x)const {
	return elementAt(find(x, root));
}

template <class Comparable>
BinaryNode< Comparable>* BinarySearchTree< Comparable>::find(const Comparable& x, BinaryNode< Comparable>* t)const {
	if (t == NULL)
		return NULL;
	else if (x < t->element)
		return find(x, t->left);
	else if (t->element < x)
		return find(x, t->right);
	else {
		cout << " Found " << t->element << " in tree" << endl;
		cout << "(at address " << t << ")" << endl;
		return t;
	}
}


//findmin
//in public 
template <class Comparable>
const Comparable& BinarySearchTree< Comparable>::findMin()const{
	return elementAt(findMin(root));
}
//in private
template <class Comparable>
BinaryNode< Comparable>* BinarySearchTree< Comparable>::findMin(BinaryNode< Comparable>* t)const {
	if (t == NULL)
		return NULL;
	if (t->left == NULL)
		return t;
	return findMin(t->left);
}
//findMax
//in public
template <class Comparable>
const Comparable& BinarySearchTree< Comparable>::findMax()const {
	return elementAt(findMax(root));
}
//in private
template <class Comparable>
BinaryNode< Comparable>* BinarySearchTree< Comparable>::findMax(BinaryNode< Comparable>* t)const {
	if (t != NULL)
		while (t->right != NULL)
			t = t->right;
	return t;
}

//INSERT
//in public
template <class Comparable>
void BinarySearchTree< Comparable>::insert(const Comparable& x) {
	insert(x, root);
}
//in private
template <class Comparable>
void BinarySearchTree< Comparable>::insert(const Comparable& x, BinaryNode< Comparable>*& t)const {
	if (t == NULL) 
		t = new BinaryNode< Comparable>(x, NULL, NULL);
	else if (x < t->element)
		insert(x, t->left);
	else if (t->element < x)
		insert(x, t->right);
	else;//Duplicate do nothing
}

//REMOVE
//in public
template <class Comparable>
void BinarySearchTree< Comparable>::remove(const Comparable& x) {
	remove(x, root);
}
//inprivate
template <class Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable& x, BinaryNode< Comparable>*& t)const {
	if (t == NULL)
		return;
	if (x < t->element)
		remove(x, t->left);
	else if (t->element < x)
		remove(x, t->right);
	else if (t->left != NULL && t->right != NULL) {
		t->element = findMin(t->right)->element;
		remove(t->element, t->right);
	}
	else {
		BinaryNode< Comparable>* oldNode = t;
		t = (t->left != NULL) ? t->left : t->right;
		delete oldNode;
	}
}

//Print
//in public
template<class Comparable>
void BinarySearchTree<Comparable>::printTree(char choi)const {
	if (isEmpty()) {
		cout << "Tree is Empty";
	}
	else {
		printTree(root, choi);
	}
}
//in private
template<class Comparable>
void BinarySearchTree<Comparable>::printTree(BinaryNode< Comparable>* t,char choi)const {
	if (choi == '1') {//pre order
		if (t != NULL) {
			cout << " " << t->element << " ";
			printTree(t->left,choi);
			printTree(t->right, choi);
		}
	}
	else if (choi == '2') {//in order
		if (t != NULL) {
			printTree(t->left, choi);
			cout << " " << t->element << " ";
			printTree(t->right, choi);
		}
	}
	else if (choi == '3') {//post order
		if (t != NULL) {
			printTree(t->left, choi);
			printTree(t->right, choi);
			cout << " " << t->element << " ";
		}
	}
}

int main() {
	BinarySearchTree<int> a(-999);
	int X;
	char choi;
	do {
		system("cls");
		cout << "---- Binary Seach Tree ----" << endl;
		cout << "1.Insert" << endl;
		cout << "2.Print Tree" << endl;
		cout << "3.Find" << endl;
		cout << "4.Remove" << endl;
		cout << "5.Quit" << endl;
		cout << "Enter choice :";
		cin >> choi;
		if (choi == '1') {
			cout << " Insert digit :";
			cin >> X;
			a.insert(X);
			cout << " Insert complete" << endl;
			system("pause");
		}
		else if (choi == '2') {
			do {
				system("cls");
				cout << "1.Pre order" << endl;
				cout << "2.In order" << endl;
				cout << "3.Post order" << endl;
				cout << "4.back to main menu" << endl;
				cout << "Enter choice :";
				cin >> choi;
				if (choi == '1') {
					system("cls");
					cout << "Pre order : ";
					a.printTree('1');
					cout << endl;
					system("pause");
					break;
				}
				else if (choi == '2') {
					system("cls");
					cout << "In order : ";
					a.printTree('2');
					cout << endl;
					system("pause");
					break;
				}
				else if (choi == '3') {
					system("cls");
					cout << "Post order : ";
					a.printTree('3');
					cout << endl;
					system("pause");
					break;
				}
				else if (choi == '4') {
					break;
				}
			} while (true);
		}
		else if (choi == '3') {
			do {
				system("cls");
				cout << "1.Find element" << endl;
				cout << "2.Find minimum" << endl;
				cout << "3.Find maximum" << endl;
				cout << "4.back to main menu" << endl;
				cout << "Enter choice :";
				cin >> choi;
				if (choi == '1') {
					cout << "Find digit : ";
					cin >> X;
					X = a.find(X);
					if (X == -999) {
						cout << " Not found in tree" << endl;
						
					}
					/*else {
						cout << "Found " << X << " in tree" << endl;

					}*/
					system("pause");
					break;
				}
				else if (choi == '2') {
					cout << " Minimum is " << a.findMin() << endl;
					system("pause");
					break;
				}
				else if (choi == '3') {
					cout << " Maximum is " << a.findMax() << endl;
					system("pause");
					break;
				}
				else if (choi == '4') {
					break;
				}
			} while (true);
		}
		else if (choi == '4') {
			cout << " Remove digit :";
			cin >> X;
			a.remove(X);
			system("pause");
		}
		else if (choi == '5') {
			break;
		}
	} while (true);
	system("pause");
	return 0;
}