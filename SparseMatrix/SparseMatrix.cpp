#include "pch.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include "Matrix.h"
#include "Chang.h"
#include <time.h>
#include <locale.h>
#include <stdlib.h>

using namespace std;
void matrixShow(int **a, int nr, int nc) {
	for (int i = 0; i < nr; i++) {
		cout << endl;
		for (int j = 0; j < nc; j++)
			cout << setw(4) << a[i][j] << " ";
	}
	cout << endl;
}
void matrixShow(int **a, int **b, int nr, int nc) {
	for (int i = 0; i < nr; i++) {
		cout << endl; {
			for (int j = 0; j < nc; j++)
				cout << setw(4) << a[i][j] << " ";
			cout << "\t";
			for (int k = 0; k < nc; k++)
				cout << setw(4) << b[i][k] << " ";
		}
	}
	cout << endl;

}
int** matrixInit(int nr, int nc, int array[]) {
	int** matrix = new int *[nr];
	for (int i = 0; i < nr; i++)
	{
		matrix[i] = new int[nc];
	}
	for (int i = 0, k = 0; i < nr; i++)
		for (int j = 0; j < nc; j++) {
			matrix[i][j] = array[k];
			k++;
		}
	return matrix;
}
int** matrixInit(int nr, int nc) {
	int** matrix;
	matrix = new int *[nr];
	for (int i = 0; i < nr; i++) {
		matrix[i] = new int[nc];
	}
	for (int i = 0; i < nr; i++)
		for (int j = 0; j < nc; j++) {
			matrix[i][j] = 0;
		}
	return matrix;
}
int** matrixInitRand(int nr, int nc) {
	int** matrix;
	matrix = new int *[nr];
	for (int i = 0; i < nr; i++) {
		matrix[i] = new int[nc];
	}
	for (int i = 0; i < nr; i++)
		for (int j = 0; j < nc; j++) {
			//matrix[i][j]=(((rand() % 2) == 0) ? (rand() % 10) : 0);
			matrix[i][j] = rand() % 100;
		}
	return matrix;
}


int main() {
	setlocale(LC_ALL, "rus");
	int array[30] = { 0,10,0,20,0,0,11,100,0,12,30,0,0,0,13,0,0,0,15,0,0,0,0,0,0,40,14,0,0,10 };//10->0
	int array1[40] = { 0,12,8,0,7,14,0,0,0,43,11,0,9,0,0,19,0,0,15,10,0,0,0,15,11,0,0,28,0,0,0,0,13,5,100,0,0,22,0,90 };
	int arr[30] = { 0,0,1,3,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,4,0,3,0,0,7,0,1,0,2 };
	double a = 0;
	//Werner C. Rheinboldt, Charles K. Mesztenyi

	//Схема Чанга и Густавсона

	int** mat0 = matrixInitRand(100, 100);
	int** mat1 = matrixInitRand(100, 100);




	/*Chang matrix0 = Chang(mat0, 100, 100);
	Chang matrix1 = Chang(mat1, 100, 100);*/
	//-------------
	clock_t start = clock();
	Matrix matr0 = Matrix(mat0, 100, 100);
	clock_t stop = clock();
	cout << "Create matrix 1 = " << (stop - start) / 1000.0 << endl;
	start = clock();
	Matrix matr1 = Matrix(mat1, 100, 100);
	stop = clock();
	cout << "Create matrix 2 = " << (stop - start) / 1000.0 << endl;
	start = clock();
	Matrix mat2 = matr0.mulmatrix(matr1);
	stop = clock();
	cout << "Multipl = " << (stop - start) / 1000.0 << endl;
	//mat2.UnboxingShow();
	//---------------
	//Chang mat=matrix0.addmatr(matrix1);
	//mat.UnboxingShow();
	//cout << endl;
	//mat.BoxingShow();

	return 0;
}
