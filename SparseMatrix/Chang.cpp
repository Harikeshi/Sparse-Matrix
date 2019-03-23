#include "pch.h"
#include "Chang.h"
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;


Chang::Chang(int **matrix, int n_r, int n_c)
{
	count = 0;
	nr = n_r;
	nc = n_c;
	for (int i = 0; i < nr; i++)
		for (int j = 0; j < nc; j++) {
			if (matrix[i][j] != 0) {
				count++;
			}
		}
	AN = new Element_chang[count];
	JR = new int[nr + 1];
	for (int i = 0, k = 0; i < nr; i++)
	{
		for (int j = 0; j < nc; j++) {
			if (matrix[i][j] != 0) {
				AN[k].data = matrix[i][j];
				if (k == 0) { JR[0] = i; }
				AN[k].JA = j;
				k++;
			}
		}
		JR[i + 1] = k;
	}
}
void Chang::BoxingShow() {
	for (int i = 0; i < this->count; i++) {
		cout << setw(4) << AN[i].data;
	}
	cout << endl;
	for (int i = 0; i < this->count; i++) {
		cout << setw(4) << AN[i].JA;
	}
	cout << endl;
	for (int i = 0; i < nr + 1; i++) {
		cout << setw(4) << JR[i];
	}
	cout << endl;
}
int** Chang::Unboxing() {
	int** matrix;
	matrix = new int *[this->nr];
	for (int i = 0; i < this->nr; i++) {
		matrix[i] = new int[this->nc];
	}
	for (int i = 0; i < this->nr; i++)
		for (int j = 0; j < this->nc; j++) {
			matrix[i][j] = 0;
		}
	int t = 0;//счетчик элементов в строке
	int c = 0;
	int el = 0;//счетчик элементов
	for (int i = 0; i < this->nr; i++)
	{
		c = abs(JR[i + 1] - JR[i]);
		if (c == 0) { continue; }
		while (t != c) {
			matrix[i][AN[el].JA] = AN[el].data;
			t++;
			el++;
		}
		t = 0;
	}
	return matrix;
}

void Chang::UnboxingShow() {
	int** matrix;
	matrix = new int *[this->nr];
	for (int i = 0; i < this->nr; i++) {
		matrix[i] = new int[this->nc];
	}
	for (int i = 0; i < this->nr; i++)
		for (int j = 0; j < this->nc; j++) {
			matrix[i][j] = 0;
		}
	int t = 0;//счетчик элементов в строке
	int c = 0;
	int el = 0;//счетчик элементов
	for (int i = 0; i < this->nr; i++)
	{
		c = abs(JR[i + 1] - JR[i]);
		if (c == 0) { continue; }
		while (t != c) {
			matrix[i][AN[el].JA] = AN[el].data;
			t++;
			el++;
		}
		t = 0;
	}
	for (int i = 0; i < this->nr; i++) {
		cout << endl;
		for (int j = 0; j < this->nc; j++)
			cout << setw(4) << matrix[i][j] << " ";
	}
	cout << endl;
	for (int i = 0; i < this->nr; i++)
		delete[] matrix[i];

	delete[] matrix;
}
Chang Chang::addmatr(Chang a)
{
	int el1 = 0, el2 = 0, cc = 0, JA1, JA2;
	Chang Cho;
	int *jr = new int[this->nr];
	Cho.JR = new int[this->nr];
	Cho.nr = this->nr;
	Cho.nc = this->nc;
	int c3 = 0;
	for (int ia = 0; ia < this->nr; ia++)
	{
		jr[ia] = c3;
		c3 = 0;
		int ct = 0;
		int t1 = 0, t2 = 0;
		bool first = true, second = true;
		int c1 = abs(this->JR[ia + 1] - this->JR[ia]);
		int c2 = abs(a.JR[ia + 1] - a.JR[ia]);
		ct = (c1 <= c2) ? c2 : c1;
		if (ia == 1) {
			int a = 0;
		}
		while (((c1 <= c2) ? t2 : t1) != ct)
		{
			JA1 = this->AN[el1].JA;
			JA2 = a.AN[el2].JA;
			if (t1 == c1) {
				JA1 = this->nc;
			}
			if (t2 == c2) { JA2 = a.nc; }
			if (c1 == 0) { JA1 = this->nc + 1; }
			if (c2 == 0) { JA2 = a.nc + 1; }
			if (JA1 < JA2)
			{
				Cho.AN[cc].data = this->AN[el1].data;
				Cho.AN[cc].JA = JA1;
				Cho.count++;
				c3++;
				second = false;
				first = true;
				cc++;
			}
			if (JA1 > JA2)
			{
				Cho.AN[cc].data = a.AN[el2].data;
				Cho.AN[cc].JA = JA2;
				Cho.count++;
				c3++;
				cc++;
				second = true;
				first = false;
			}
			if (JA1 == JA2)
			{
				Cho.AN[cc].data = this->AN[el1].data + a.AN[el2].data;
				Cho.AN[cc].JA = JA1;
				Cho.count++;
				cc++;
				c3++;
				second = true;
				first = true;
			}

			if (t1 != c1 && first == true)
			{
				el1++; t1++;
			}
			if (t2 != c2 && second == true)
			{
				el2++; t2++;
			}
		}
	}
	if (el1 == this->count - 1) {
		cc++;
		Cho.AN[cc].data = this->AN[el1].data;
		Cho.AN[cc].JA = JA1;
		Cho.count++;
		c3++;
	}
	if (el2 == a.count - 1) {
		cc++;
		Cho.AN[cc].data = a.AN[el2].data;
		Cho.AN[cc].JA = JA2;
		Cho.count++;
		c3++;
	}
	jr[this->nr] = c3 + jr[this->nr - 1];
	Cho.JR = jr;
	cout << endl;
	return Cho;
}