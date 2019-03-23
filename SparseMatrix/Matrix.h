#pragma once
#include <iostream>
#include <iomanip>

using namespace std;

struct Element
{
	int data;
	int NR;
	int NC;
};
class Matrix
{
public:
	int count;//���������� ��������� ���������
private:
	Element *AN;//������ ��������� ���������
	int *JR;//������ JR
	int *JC;//������ JC
	int nr;//���������� �����
	int nc;//���������� ��������

public:
	Matrix(int An, int Nr, int Nc);
	Matrix(int **matrix, int Nr, int Nc);
	void UnboxingShow();
	void BoxingShow();
	int* getRow(int i);
	int* getCol(int i);
	Matrix mulmatrix(Matrix b);
	void mulmatrix(Matrix b, int **c);
	void addmatrix(Matrix b, int **c);
	void Unboxing(int** c);
	Matrix addmatrix(Matrix b);
private:
	void ShowRow(int i);
};

