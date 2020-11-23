// Lab7.3(Iter).cpp 
// Михайлов Олександр
// Опрацювання динамічних багатовимірних масивів
// Варіант 24

#include <iostream>
#include <Windows.h>
#include <time.h>
#include <iomanip>

using namespace std;

void Create(int** mas, const int row, const int column, const int Min, const int Max) {
	for (int i = 0; i < row; i++)
		for (int j = 0; j < column; j++)
			mas[i][j] = Min + rand() % (Max - Min + 1);
}

void Print(int** mas, const int row, const int column) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			cout << setw(4) << mas[i][j] << "  ";
		}
		cout << endl;
	}
	cout << endl;
}

int MultiplicationResult(int** mas, const int row, const int column) {

	int col = row;
	bool* n = new bool [col];
	long long int Result = 1;

	for (int i = 0; i < row; i++) { // Перевіряємо чи рядок підходить
		n[i] = true; // Рядок підходить

		for (int j = 0; j < column; j++) { 
			if (mas[i][j] < 0) {
				n[i] = false;  // Рядок не підходить
			}
		}
	}

	for (int i = 0; i < row; i++) { // Множимо рядки, які підходять
		if (n[i] == true) {
			for (int j = 0; j < column; j++) {
				Result *= mas[i][j];
			}
		}
	}

	delete[] n;
	return Result;
}

void UpperDiagonals(int** mas, const int row, int* SumMasUpper) {
	for (int k = 1; k < row - 2; k++) {
		int Sum = 0;
		for (int j = k, i = 0; j < row; j++, i++) {
			Sum += mas[i][j];
		}
		SumMasUpper[k - 1] = Sum;
	}
}

void BottomDiagonals(int** mas, const int row, int* SumMasBottom) {
	for (int k = 1; k < row - 2; k++) {
		int Sum = 0;
		for (int i = k, j = 0; i < row; i++, j++) {
			Sum += mas[i][j];
		}
		SumMasBottom[k - 1] = Sum;
	}
}

void FindMaxUpperDiagonals(int** mas, const int row, int* SumMasUpper, int& MaxUpper) {
	for (int i = 0; i < row - 2; i++) {
		if (SumMasUpper[i] > MaxUpper) {
			MaxUpper = SumMasUpper[i];
		}
	}
}

void FindMaxBottomDiagonals(int** mas, const int row, int* SumMasBottom, int& MaxBottom) {
	for (int i = 0; i < row - 2; i++) {
		if (SumMasBottom[i] > MaxBottom) {
			MaxBottom = SumMasBottom[i];
		}
	}
}

void FindMaxFromAll(int** mas, const int row, int& MaxFromAll, int& MaxBottom, int& MaxUpper) {
	MaxFromAll = MaxBottom;
	if (MaxUpper > MaxBottom) {
		MaxFromAll = MaxUpper;
	}
}

void MaxFromSum(int** mas, const int row) {
	int* SumMasBottom = new int[row - 2];
	int* SumMasUpper = new int[row - 2];

	UpperDiagonals(mas, row, SumMasUpper);
	BottomDiagonals(mas, row, SumMasBottom);

	int MaxUpper = SumMasUpper[0], MaxBottom = SumMasBottom[0], MaxFromAll = 0;

	FindMaxUpperDiagonals(mas, row, SumMasUpper, MaxUpper);
	FindMaxBottomDiagonals(mas, row, SumMasBottom, MaxBottom);
	FindMaxFromAll(mas, row, MaxFromAll, MaxBottom, MaxUpper);

	cout << " Максимум серед сум елементів діагоналей, паралельних до головної діагоналі матриці: " << MaxFromAll << endl;

	delete[] SumMasBottom;
	delete[] SumMasUpper;
}

int main()
{
	srand((unsigned)time(NULL));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int k, n, M, Min, Max;

	cout << " Введіть кількість рядків матриці: "; cin >> k;
	cout << " Введіть кількість стовпців матриці: "; cin >> n; cout << endl;
	cout << " Введіть мінімальне можливе значення у матриці: "; cin >> Min;
	cout << " Введіть максимальне можливе значення у матриці: "; cin >> Max; cout << endl;
	
	//1
	int** a = new int* [k];
	for (int i = 0; i < k; i++) {
		a[i] = new int[n];
	}

	Create(a, k, n, Min, Max);
	Print(a, k, n);
	
	// 1) Добуток елементів у рядках, де немає від'ємних елементів.
	cout << " Добуток елементів у рядках, де немає від'ємних елементів: " << MultiplicationResult(a, k, n) << endl << endl;

	// 2) Максимум серед сум елементів діагоналей, паралельних до головної діагоналі матриці.
	cout << " Для виконання завдання №2 буде сформована нова матриця b ( M x M )" << endl << endl;
	cout << " Введіть кількість рядків та стовпців нової матриці: "; cin >> M; cout << endl;

	//2
	int** b = new int* [M];
	for (int i = 0; i < M; i++) {
		b[i] = new int[M];
	}

	Create(b, M, M, Min, Max);
	Print(b, M, M);
	MaxFromSum(b, M);

	for (int i = 0; i < k; i++) {
		delete[] a[i];
	}
	delete[] a;

	for (int i = 0; i < M; i++) {
		delete[] b[i];
	}
	delete[] b;

	cin.get();
	return 0;
}
