// Lab_7_3_1
#include <iostream>
#include <iomanip>
using namespace std;

int myrand(const int& min, const int& max) {
	return min > 0 ?
		rand() % (max - min + 1) + min :
		rand() % (abs(min) + max + 1) + min;
}

void full_matrix(int** matrix, const int* size, const int* dia) {
	for (int i = 0; i < size[0]; i++)
		for (int j = 0; j < size[1]; j++)
			matrix[i][j] = myrand(dia[0], dia[1]);
}

void draw_matrix(int** matrix, const int* size) {
	for (int i = 0; i < size[0]; i++) {
		for (int j = 0; j < size[1]; j++)
			cout << setw(4) << matrix[i][j];
		cout << endl;
	}
}

bool has_null(const int* mass, int size_i) {
	for (--size_i; size_i >= 0; size_i--)
		if (mass[size_i] == 0)
			return true;

	return false;
}

int ms_count_vid(const int* mass, int size_i) {
	int count = 0;
	for (--size_i; size_i >= 0; size_i--)
		if (mass[size_i] < 0)
			count++;

	return count;
}

int mt_count_vid(int** matrix, const int *size) {
	int count = 0;
	for (int i = 0; i < size[0]; i++)
		if (has_null(matrix[i], size[1]))
			count += ms_count_vid(matrix[i], size[1]);
	return count;
}

int min_(const int* mass, int size_i) {
	int min = 0;
	for (--size_i; size_i > 0; --size_i)
		if (mass[size_i] < mass[min])
			min = size_i;
	return min;
}

int max_stolb(int** matrix, int size_i, const int j) {
	int max = 0;
	for (--size_i; size_i > 0; --size_i)
		if (matrix[size_i][j] > matrix[max][j])
			max = size_i;
	return max;
}

int** add_row(int** matrix, int &rows) {
	int** mt_1 = new int* [++rows];
	if (matrix != nullptr) {
		memcpy(mt_1, matrix, sizeof(int*) * (rows - 1));
		delete[] matrix;
	}
	return mt_1;
}

void get_sidlovi_tochki(int** matrix, const int *size, int** &out_tochki, int *out_size) {
	for (int i = 0; i < size[0]; i++)
		for (int j = 0; j < size[1]; j++)
			if (min_(matrix[i], size[1]) == j &&
				max_stolb(matrix, size[0], j) == i)
			{
				out_tochki = add_row(out_tochki, out_size[0]);
				out_tochki[out_size[0] - 1] = new int[2]{ i, j };
			}
}

void main() {
	srand(time(NULL));
	int** matrix = nullptr, size[2], dia[2];
	cout << "k = "; cin >> size[0];
	cout << "n = "; cin >> size[1];
	cout << "start dia = "; cin >> dia[0];
	cout << "stop dia  = "; cin >> dia[1];

	matrix = new int* [size[0]];
	for (int k = 0; k < size[0]; k++)
		matrix[k] = new int[size[1]];

	full_matrix(matrix, size, dia);
	draw_matrix(matrix, size);
	
	cout << "count vid: " << mt_count_vid(matrix, size) << endl; 

	int **sidlovi_tochki = nullptr, size_1[2] = {0 , 2};
	get_sidlovi_tochki(matrix, size, sidlovi_tochki, size_1);
	cout << endl << "Tochki: " << endl;
	if (sidlovi_tochki != nullptr)
		draw_matrix(sidlovi_tochki, size_1);
	else cout << "None" << endl;
	cout << endl;

	for (int n = 0; n < size[0]; n++)
		delete[] matrix[n];
	delete[] matrix;


	if (sidlovi_tochki != nullptr) {
		for (int n = 0; n < size_1[0]; n++)
			delete[] sidlovi_tochki[n];
		delete[] sidlovi_tochki;
	}
}