#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
using namespace std;

vector<int> mainarray;
vector<int> insertionarr;
vector<int> QSarr;
int roundQ = 0;

template <class Comparable>
void insertionSort(vector<Comparable>& a) {
	for (int p = 1; p < a.size(); p++) {
		Comparable tmp = a[p];
		int Pmove = 0;
		int j;
		for (j = p; j > 0 && tmp < a[j - 1]; j--) {
			a[j] = a[j - 1];
			Pmove += 1;
		}
		a[j] = tmp;
		cout << "After p = " << p << "  ";
		for (int i = 0; i < insertionarr.size(); i++) {
			cout << insertionarr[i] << "  ";
		}
		cout << "| "<<Pmove << endl;
	}
}
template <class Comparable>
void insertionSort(vector<Comparable>& a,int left,int right) {

	for (int p = left+1; p < right+1; p++) {
		Comparable tmp = a[p];
		int j;
		for (j = p; j > 0 && tmp < a[j - 1]; j--) {
			a[j] = a[j - 1];
		}
		a[j] = tmp;
	}
}
template <class Comparable>
const Comparable& median3(vector<Comparable>& a, int left, int right) {
	int center = (left + right) / 2;
	if (a[center] < a[left]) {
		swap(a[left], a[center]);
	}
	if (a[right] < a[left]) {
		swap(a[left], a[right]);
	}
	if (a[right] < a[center]) {
		swap(a[center], a[right]);
	}

	swap(a[center], a[right - 1]);
	return a[right - 1];
}
template <class Comparable>
void quicksort(vector<Comparable>& a, int left, int right,int cutoff) {
	roundQ += 1;
	cout << "Round " << roundQ << "      ";
	if (left + cutoff <= right) {
		Comparable pivot = median3(a, left, right);
		int i = left, j = right - 1;
		for (;;) {
			while (a[++i] < pivot) {}
			while (pivot < a[--j]) {}
			if (i < j) {
				swap(a[i], a[j]);
			}
			else {
				break;
			}
		}
		swap(a[i], a[right - 1]);
		
		for (int i = 0; i < QSarr.size(); i++) {
			cout << QSarr[i] << "  ";
		}
		string stri = to_string(i) + " ";
		string strj = to_string(j) + " ";
		cout << "|" <<setw(7)<< a[i] << "|" <<setw(3) << stri << "|" <<setw(3)<< strj << " "<< endl;

		quicksort(a, left, i - 1,cutoff);
		quicksort(a, i + 1, right,cutoff);
	}
	else {
		insertionSort(a, left, right);
		for (int i = 0; i < QSarr.size(); i++) {
			cout << QSarr[i] << "  ";
		}
		cout << "| " << "- (insertionsort)" << endl;
		
	}
}
template<class Comparable>
void quicksort(vector<Comparable> &a ,int cutoff) {
	quicksort(a, 0, a.size() - 1, cutoff);
}

int main() {
	char choi;
	do {
		system("cls");
		cout << "----Sorting----" << endl;
		cout << " 1.Input" << endl;
		cout << " 2.InsertionSort" << endl;
		cout << " 3.QuickSort" << endl;
		cout << " 4.Quit" << endl;
		cout << " Enter Choice: ";
		cin >> choi;
		if (choi == '4') {
			return 0;
		}
		else if (choi == '1') {
			system("cls");
			int numele;
			cout << "How many element:";
			cin >> numele;
			mainarray.resize(numele);
			for (int i = 0;i< mainarray.size();i++) {
				cout << "Enter element " << i + 1 << " : ";
				cin >> mainarray[i];
			}
		}
		else if (choi == '2') {
			system("cls");
			cout << "Orriginal:   ";
			for (int i = 0;i<mainarray.size();i++) {
				cout << mainarray[i] <<"  ";
			}
			cout << "| P.move";
			cout << endl;
			insertionarr = mainarray;
			insertionSort(insertionarr);
			system("pause");
		}
		else if (choi == '3') {
			system("cls");
			int cutoff;
			cout << "Enter cutoff number";
			cin >> cutoff;
			cout << "Orriginal:   ";
			for (int i = 0; i < mainarray.size(); i++) {
				cout << mainarray[i] << "  ";
			}
			cout << "| Pivot " <<"| i "<<"| j "<< endl;
			QSarr = mainarray;
			quicksort(QSarr,cutoff);
			system("pause");
			roundQ = 0;
		}
		




	} while (true);
}



