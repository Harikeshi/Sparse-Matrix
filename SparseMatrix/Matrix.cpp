#include "pch.h"
#include "Matrix.h"
#include <iomanip>
#include <iostream>


Matrix::Matrix(int An, int Nr, int Nc) {
	nr = Nr;
	nc = Nc;
	JR = new int[nr];
	JC = new int[nc];
}
Matrix::Matrix(int **matrix, int Nr, int Nc) {
	count = 0;
	nr = Nr;
	nc = Nc;
	for (int i = 0; i < nr; i++)
		for (int j = 0; j < nc; j++) {
			if (matrix[i][j] != 0) {
				count++;
			}
		}
	int f_r_elem = 0;
	int f_r_count = 0;//nomer pervogo elementa v stroke
	int k = 0;//номер в массиве AN
	AN = new Element[count];
	for (int i = 0; i < count; i++)
		AN[i].NC = -1;
	JR = new int[nr];
	for (int i = 0; i < nr; i++)
		JR[i] = -1;
	JC = new int[nc];
	for (int i = 0; i < nc; i++)
		JC[i] = -1;
	bool first = false;
	for (int i = 0; i < nr; i++) {
		for (int j = 0; j < nc; j++)
		{
			if (matrix[i][j] != 0 && first == false)
			{
				f_r_count = k;//0
				f_r_elem = matrix[i][j];
				first = true;
				JR[i] = k;
			}
			if (matrix[i][j] != 0)
			{
				AN[k].data = matrix[i][j];
				AN[k].NR = k + 1;
				k++;
			}
			if (j == (nc - 1)) {
				AN[k - 1].NR = f_r_count;
				first = false;
			}
		}
	}
	int c_temp = 0;
	int c_t = 0;
	int c = 0;
	for (int i = 0; i < nr; i++)
		for (int j = 0; j < nc; j++)
		{
			if (matrix[i][j] != 0)
			{
				c++;
				if (AN[c - 1].NC == -1)//первый вход
				{
					AN[c - 1].NC = c - 1;
					JC[j] = c - 1;
					c_temp = c - 1;
					c_t = c - 1;
					for (int t = j + 1; t < nc; t++)
					{
						if (matrix[i][t] != 0)
						{
							c_t++;
						}
					}
					for (int l = i + 1; l < nr; l++)
						for (int z = 0; z < nc; z++) {
							if (matrix[l][z] != 0) {
								c_t++;
								if (z == j) {
									AN[c_t].NC = c - 1;
									AN[c_temp].NC = c_t;
									c_temp = c_t;
								}
							}
						}
				}
			}
		}
}
void Matrix::BoxingShow()
{
	for (int i = 0; i < count; i++)
		cout << setw(4) << i << " ";
	cout << endl;
	for (int u = 0; u < count; u++)
		cout << setw(4) << AN[u].data << " ";
	cout << endl;
	for (int i = 0; i < count; i++)
		cout << setw(4) << AN[i].NR << " ";
	cout << endl;
	for (int i = 0; i < count; i++)
		cout << setw(4) << AN[i].NC << " ";
	cout << endl;
	for (int i = 0; i < nr; i++)
		cout << setw(4) << JR[i] << " ";
	cout << endl;
	for (int i = 0; i < nc; i++)
		cout << setw(4) << JC[i] << " ";
	cout << endl;
}
void Matrix::Unboxing(int** c) {
	int *arr = 0;
	for (int i = 0; i < nr; i++) {
		arr = this->getRow(i);
		for (int j = 0; j < nc; j++)
			c[i][j] = arr[j];
	}
	delete[]arr;
	arr = 0;
}
void Matrix::UnboxingShow()
{
	for (int i = 0; i < nr; i++) {
		this->ShowRow(i);
	}
	//возвратить столбец, в цикле приравнть элементы удалить массив вспомогательный
}
int* Matrix::getRow(int i) {
	//i- номер строки//=0
		//начало строки берем
	int *arr = new int[nc];
	for (int j = 0; j < nc; j++) {
		arr[j] = 0;
	}
	int t = -1;
	int tmp = JR[i];//первый элемент
	int jr_tmp = JR[i];//расчетный элемент
	int tmp_c = tmp;
	while (t != tmp) {
		int nc_tmp = AN[jr_tmp].NC;
		int t_min = jr_tmp;//
		int temp = AN[jr_tmp].NC;//
		while (temp != tmp_c) {
			if (temp < t_min)
			{
				t_min = temp;
			}
			if (nc_tmp < t_min) {
				t_min = nc_tmp;
			}
			temp = AN[nc_tmp].NC;
			nc_tmp = AN[temp].NC;
		}
		int col = 0;
		for (int j = 0; j < nc; j++)
			if (JC[j] == t_min) {
				col = j;
				arr[col] = AN[jr_tmp].data;//!!!
				break;
			}
		jr_tmp = AN[temp].NR;
		t = AN[temp].NR;
		tmp_c = t;
	}
	return arr;
}
int* Matrix::getCol(int i) {
	int *arr = new int[nr];
	for (int j = 0; j < nr; j++) {
		arr[j] = 0;
	}
	//нужно хранить tmp 
	int t = -1;
	int tmp = JC[i];//первый элемент
	int jc_tmp = JC[i];//расчетный элемент
	int tmp_r = tmp;
	while (t != tmp) {//пока не t !=0
					//1
		int nr_tmp = AN[jc_tmp].NR;//следующее значение NR		
		int t_min = jc_tmp;//текущее значение NR
		int temp = AN[jc_tmp].NR;//
		while (temp != tmp_r) {
			if (nr_tmp < t_min)
			{
				t_min = nr_tmp;
			}
			if (temp < t_min) {
				t_min = temp;
			}
			temp = AN[nr_tmp].NR;
			nr_tmp = AN[temp].NR;

		}
		int col = 0;
		for (int j = 0; j < nr; j++)
			if (JR[j] == t_min) {
				col = j;
				arr[col] = AN[temp].data;//????						
				break;
			}
		jc_tmp = AN[temp].NC;
		t = AN[temp].NC;
		tmp_r = t;
	}
	for (int j = 0; j < nr; j++) {
		cout << setw(3) << arr[j] << " ";
	}
	return arr;
}
void Matrix::ShowRow(int i) {
	//i- номер строки//=0
		//начало строки берем
	int *arr = new int[nc];
	for (int j = 0; j < nc; j++) {
		arr[j] = 0;
	}
	int t = -1;
	int tmp = JR[i];//первый элемент
	int jr_tmp = JR[i];//расчетный элемент
	int tmp_c = tmp;
	while (t != tmp) {
		int nc_tmp = AN[jr_tmp].NC;
		int t_min = jr_tmp;//
		int temp = AN[jr_tmp].NC;//
		while (temp != tmp_c) {
			if (temp < t_min)
			{
				t_min = temp;
			}
			if (nc_tmp < t_min) {
				t_min = nc_tmp;
			}
			temp = AN[nc_tmp].NC;
			nc_tmp = AN[temp].NC;
		}
		int col = 0;
		for (int j = 0; j < nc; j++)
			if (JC[j] == t_min) {
				col = j;
				arr[col] = AN[jr_tmp].data;//!!!
				break;
			}
		jr_tmp = AN[temp].NR;
		t = AN[temp].NR;
		tmp_c = t;
	}

	for (int j = 0; j < nc; j++) {
		cout << setw(4) << arr[j] << " ";
	}
	cout << endl;
	delete[]arr;
	arr = 0;
}
Matrix Matrix::mulmatrix(Matrix b)
{
	int** matrix;
	int y = 0;
	matrix = new int *[this->nr];
	for (int i = 0; i < this->nr; i++) {
		matrix[i] = new int[b.nc];
	}
	for (int i = 0; i < this->nr; i++)
		for (int j = 0; j < b.nc; j++) {
			matrix[i][j] = 0;
		}
	int k = 0;//счетчик в новом AN
	int row = 0, col = 0;
	int row_v = 0;
	int col_v = 0;
	int ia = 0, ja = 0;
	int t_c = -1;
	int temp_a, temp_b, tmp_a, tmp_b, jr_tmp, jc_tmp, tmp_r, tmp_c;
	int t_min_a = 0, t_min_b = 0;
	int i_a = 1; int i_b = 2;
	int sum = 0;
	int tp = 0;
	bool row_y = true, col_y = true;
	int t = -1;
	for (int l = 0; l < this->nr; l++)
	{
		for (int m = 0; m < b.nc; m++) {
			row_y = true, col_y = true;
			t = -1;
			t_c = -1;
			tmp_a = this->JR[l];//первый элемент
			jr_tmp = this->JR[l];//расчетный элемент
			tmp_b = b.JC[m];//первый элемент
			jc_tmp = b.JC[m];//расчетный элемент
			sum = 0;//summa при умножении строки на столбец.
			//по строке
			if (this->JR[l] == -1 || b.JC[m] == -1) {
				matrix[ia][ja] = 0; ja++; if (ja == b.nc) { ja = 0; ia++; }
				continue;
			}
			tmp_r = tmp_b;
			tmp_c = tmp_a;
			if (l == 2 && m == 0)
			{
				//cout << endl;
			}
			while (t != tmp_a && t_c != tmp_b) {
				if (row_y == true) {
					int nc_tmp = this->AN[jr_tmp].NC;
					t_min_a = jr_tmp;//
					temp_a = this->AN[jr_tmp].NC;//
					while (temp_a != tmp_c)
					{
						if (temp_a < t_min_a)
						{
							t_min_a = temp_a;
						}
						if (nc_tmp < t_min_a)
						{
							t_min_a = nc_tmp;
						}
						temp_a = this->AN[nc_tmp].NC;
						nc_tmp = this->AN[temp_a].NC;
					}
					row = 0;
					for (int j = 0; j < nc; j++)
						if (this->JC[j] == t_min_a)
						{
							row = j;//номер столбца
							row_v = this->AN[temp_a].data;
							break;
						}
				}
				//по столбцу
				if (col_y == true) {
					int nr_tmp = b.AN[jc_tmp].NR;//следующее значение NR		
					t_min_b = jc_tmp;//текущее значение NR
					temp_b = b.AN[jc_tmp].NR;//
					while (temp_b != tmp_r)
					{
						if (nr_tmp < t_min_b)
						{
							t_min_b = nr_tmp;
						}
						if (temp_b < t_min_b)
						{
							t_min_b = temp_b;
						}
						temp_b = b.AN[nr_tmp].NR;
						nr_tmp = b.AN[temp_b].NR;
					}
					col = 0;
					for (int j = 0; j < nr; j++)
						if (b.JR[j] == t_min_b)
						{
							col = j;
							col_v = b.AN[temp_b].data;
							break;
						}
				}
				//сравниваем row и col
				if (row < col) {
					//след строку , а столбец оставляем
					col_y = false;
					row_y = true;
					jr_tmp = this->AN[temp_a].NR;
					t = this->AN[temp_a].NR;
					tmp_c = t;
				}
				if (row > col) {
					//следующий элемент по столбцу
					col_y = true;
					row_y = false;
					jc_tmp = b.AN[temp_b].NC;
					tmp_r = b.AN[temp_b].NC;
					t_c = b.AN[temp_b].NC;
				}
				if (row == col) {
					col_y = true;
					row_y = true;
					sum += row_v * col_v;//
					//cout << sum << " ";
					jr_tmp = this->AN[temp_a].NR;
					t = this->AN[temp_a].NR;
					jc_tmp = b.AN[temp_b].NC;
					tmp_r = b.AN[temp_b].NC;
					tmp_c = t;
				}
			}
			//if (sum != 0) { 
			matrix[ia][ja] = sum; k++; ja++; if (ja == b.nc) { ja = 0; ia++; } /*cout <<setw(4)<< sum << " "; }*/
		}
		//cout <<".";
	}
	Matrix ar = Matrix(matrix, this->nr, b.nc);
	return ar;
}
void Matrix::mulmatrix(Matrix b, int **c)
{
	int k = 0;//счетчик в новом AN
	int row = 0, col = 0;
	int row_v = 0;
	int col_v = 0;
	int ia = 0, ja = 0;
	int t_c = -1;
	int temp_a, temp_b, tmp_a, tmp_b, jr_tmp, jc_tmp, tmp_r, tmp_c;
	int t_min_a = 0, t_min_b = 0;
	int i_a = 1; int i_b = 2;
	int sum = 0;
	int tp = 0;
	bool row_y = true, col_y = true;
	int t = -1;
	for (int l = 0; l < this->nr; l++)
	{
		for (int m = 0; m < b.nc; m++) {
			row_y = true, col_y = true;
			t = -1;
			t_c = -1;
			tmp_a = this->JR[l];//первый элемент
			jr_tmp = this->JR[l];//расчетный элемент
			tmp_b = b.JC[m];//первый элемент
			jc_tmp = b.JC[m];//расчетный элемент
			sum = 0;//summa при умножении строки на столбец.
			//по строке
			if (this->JR[l] == -1 || b.JC[m] == -1) {
				c[ia][ja] = 0; ja++; if (ja == b.nc) { ja = 0; ia++; }
				continue;
			}
			tmp_r = tmp_b;
			tmp_c = tmp_a;
			if (l == 2 && m == 0)
			{
				//cout << endl;
			}
			while (t != tmp_a && t_c != tmp_b) {
				if (row_y == true) {
					int nc_tmp = this->AN[jr_tmp].NC;
					t_min_a = jr_tmp;//
					temp_a = this->AN[jr_tmp].NC;//
					while (temp_a != tmp_c)
					{
						if (temp_a < t_min_a)
						{
							t_min_a = temp_a;
						}
						if (nc_tmp < t_min_a)
						{
							t_min_a = nc_tmp;
						}
						temp_a = this->AN[nc_tmp].NC;
						nc_tmp = this->AN[temp_a].NC;
					}
					row = 0;
					for (int j = 0; j < nc; j++)
						if (this->JC[j] == t_min_a)
						{
							row = j;//номер столбца
							row_v = this->AN[temp_a].data;
							break;
						}
				}
				//по столбцу
				if (col_y == true) {
					int nr_tmp = b.AN[jc_tmp].NR;//следующее значение NR		
					t_min_b = jc_tmp;//текущее значение NR
					temp_b = b.AN[jc_tmp].NR;//
					while (temp_b != tmp_r)
					{
						if (nr_tmp < t_min_b)
						{
							t_min_b = nr_tmp;
						}
						if (temp_b < t_min_b)
						{
							t_min_b = temp_b;
						}
						temp_b = b.AN[nr_tmp].NR;
						nr_tmp = b.AN[temp_b].NR;
					}
					col = 0;
					for (int j = 0; j < nr; j++)
						if (b.JR[j] == t_min_b)
						{
							col = j;
							col_v = b.AN[temp_b].data;
							break;
						}
				}
				//сравниваем row и col
				if (row < col) {
					//след строку , а столбец оставляем
					col_y = false;
					row_y = true;
					jr_tmp = this->AN[temp_a].NR;
					t = this->AN[temp_a].NR;
					tmp_c = t;
				}
				if (row > col) {
					//следующий элемент по столбцу
					col_y = true;
					row_y = false;
					jc_tmp = b.AN[temp_b].NC;
					tmp_r = b.AN[temp_b].NC;
					t_c = b.AN[temp_b].NC;
				}
				if (row == col) {
					col_y = true;
					row_y = true;
					sum += row_v * col_v;//
					//cout << sum << " ";
					jr_tmp = this->AN[temp_a].NR;
					t = this->AN[temp_a].NR;
					jc_tmp = b.AN[temp_b].NC;
					tmp_r = b.AN[temp_b].NC;
					tmp_c = t;
				}
			}
			//if (sum != 0) { 
			c[ia][ja] = sum; k++; ja++; if (ja == b.nc) { ja = 0; ia++; } /*cout <<setw(4)<< sum << " "; }*/
		}
	}
}
void Matrix::addmatrix(Matrix b, int **c) {
	//todo:
	//находим первый элемент в строке первой матрицы 
	//находим элемент в строке второй матрицы
	//если равны индексы складываем и записываем
	//если индекс строки 1 матрицы больше записываем элемент второй матрицы и переход к след элементу 2 матрицы 
	//если индекс строки 2 матрицы больше записываем элемент первой матрицы в результат и переходим к след элементу 1 матрицы
	int ja = 0;//row index
	int k = 0;//счетчик
	int tmp(0), jr_tmp(0), nc_tmp(0), t_min(0), temp(0), tmp_c(0);
	int tmp_b(0), jr_tmp_b(0), nc_tmp_b(0), t_min_b(0), temp_b(0), tmp_c_b(0), col(0), col_b(0);
	bool first = true, second = true;
	int t = -1;
	int t_c = -1;

	for (int ia = 0; ia < this->nr; ia++) {
		first = true; second = true;
		tmp_b = b.JR[ia];//первый элемент
		jr_tmp_b = b.JR[ia];//расчетный элемент
		tmp = this->JR[ia];//первый элемент
		jr_tmp = this->JR[ia];//расчетный элемент
		tmp_c = tmp;
		tmp_c_b = tmp_b;

		if (ia == 3) {
			int six = 0;
		}

		if (b.JR[ia] == -1) {
			second = false;
			col_b = this->nc;
		}
		if (this->JR[ia] == -1) {
			first = false;
			col = this->nc;
		}
		while ((t_c != tmp_b) && (t != tmp))
		{
			if (first == true)
			{
				nc_tmp = this->AN[jr_tmp].NC;
				t_min = jr_tmp;//
				temp = this->AN[jr_tmp].NC;//
				while (temp != tmp_c)
				{
					if (temp < t_min)
					{
						t_min = temp;
					}
					if (nc_tmp < t_min)
					{
						t_min = nc_tmp;
					}
					temp = this->AN[nc_tmp].NC;
					nc_tmp = this->AN[temp].NC;
				}
				col = 0;
				for (int j = 0; j < nc; j++)
					if (this->JC[j] == t_min) {
						col = j;
						break;
					}
			}
			if (second == true) {
				nc_tmp_b = b.AN[jr_tmp_b].NC;
				t_min_b = jr_tmp_b;//
				temp_b = b.AN[jr_tmp_b].NC;//
				while (temp_b != tmp_c_b) {
					if (temp_b < t_min_b)
					{
						t_min_b = temp_b;
					}
					if (nc_tmp_b < t_min_b) {
						t_min_b = nc_tmp_b;
					}
					temp_b = b.AN[nc_tmp_b].NC;
					nc_tmp_b = b.AN[temp_b].NC;
				}
				col_b = 0;
				for (int j = 0; j < nc; j++)
					if (b.JC[j] == t_min_b) {
						col_b = j;
						break;
					}
			}
			if (col < col_b) {
				c[ia][col] = this->AN[temp].data;
				c[ia][col_b] = b.AN[temp_b].data;
				second = false;
				first = true;
				jr_tmp = this->AN[temp].NR;
				t = this->AN[temp].NR;
				tmp_c = t;
			}
			if (col > col_b) {
				c[ia][col] = this->AN[temp].data;
				if (t_c != -1)
					c[ia][col_b] = b.AN[temp_b].data;
				second = true;
				first = false;
				jr_tmp_b = b.AN[temp_b].NR;
				t_c = b.AN[temp_b].NR;
				tmp_c_b = t_c;
			}
			if (col == col_b) {
				c[ia][col] = this->AN[temp].data + b.AN[temp_b].data;
				second = true;
				first = true;
				jr_tmp = this->AN[temp].NR;
				t = this->AN[temp].NR;
				tmp_c = t;
				jr_tmp_b = b.AN[temp_b].NR;
				t_c = b.AN[temp_b].NR;
				tmp_c_b = b.AN[temp_b].NR;
				if (t_c == tmp_b) {

					second = false;
					if (t != tmp) {
						t_c = -1;
					}
					else t_c = tmp_b;
				}
			}
		}
	}
	for (int ik = 0; ik < nr; ik++) {
		cout << endl;
		for (int jk = 0; jk < nc; jk++)
			cout << c[ik][jk] << " ";
	}
}
Matrix Matrix::addmatrix(Matrix b) {
	int** matrix;
	matrix = new int *[this->nr];
	for (int i = 0; i < this->nr; i++) {
		matrix[i] = new int[this->nc];
	}
	for (int i = 0; i < this->nr; i++)
		for (int j = 0; j < this->nc; j++) {
			matrix[i][j] = 0;
		}

	int ja = 0;//row index
	int k = 0;//счетчик
	int tmp(0), jr_tmp(0), nc_tmp(0), t_min(0), temp(0), tmp_c(0);
	int tmp_b(0), jr_tmp_b(0), nc_tmp_b(0), t_min_b(0), temp_b(0), tmp_c_b(0), col(0), col_b(0);
	bool first = true, second = true;
	int t = -1;
	int t_c = -1;

	for (int ia = 0; ia < this->nr; ia++) {
		first = true; second = true;
		tmp_b = b.JR[ia];//первый элемент
		jr_tmp_b = b.JR[ia];//расчетный элемент
		tmp = this->JR[ia];//первый элемент
		jr_tmp = this->JR[ia];//расчетный элемент
		tmp_c = tmp;
		tmp_c_b = tmp_b;

		if (ia == 3) {
			int six = 0;
		}

		if (b.JR[ia] == -1) {
			second = false;
			col_b = this->nc;
		}
		if (this->JR[ia] == -1) {
			first = false;
			col = this->nc;
		}
		while ((t_c != tmp_b) && (t != tmp))
		{
			if (first == true)
			{
				nc_tmp = this->AN[jr_tmp].NC;
				t_min = jr_tmp;//
				temp = this->AN[jr_tmp].NC;//
				while (temp != tmp_c)
				{
					if (temp < t_min)
					{
						t_min = temp;
					}
					if (nc_tmp < t_min)
					{
						t_min = nc_tmp;
					}
					temp = this->AN[nc_tmp].NC;
					nc_tmp = this->AN[temp].NC;
				}
				col = 0;
				for (int j = 0; j < nc; j++)
					if (this->JC[j] == t_min) {
						col = j;
						break;
					}
			}
			if (second == true) {
				nc_tmp_b = b.AN[jr_tmp_b].NC;
				t_min_b = jr_tmp_b;//
				temp_b = b.AN[jr_tmp_b].NC;//
				while (temp_b != tmp_c_b) {
					if (temp_b < t_min_b)
					{
						t_min_b = temp_b;
					}
					if (nc_tmp_b < t_min_b) {
						t_min_b = nc_tmp_b;
					}
					temp_b = b.AN[nc_tmp_b].NC;
					nc_tmp_b = b.AN[temp_b].NC;
				}
				col_b = 0;
				for (int j = 0; j < nc; j++)
					if (b.JC[j] == t_min_b) {
						col_b = j;
						break;
					}
			}
			if (col < col_b) {
				matrix[ia][col] = this->AN[temp].data;
				matrix[ia][col_b] = b.AN[temp_b].data;
				second = false;
				first = true;
				jr_tmp = this->AN[temp].NR;
				t = this->AN[temp].NR;
				tmp_c = t;
			}
			if (col > col_b) {
				matrix[ia][col] = this->AN[temp].data;
				if (t_c != -1)
					matrix[ia][col_b] = b.AN[temp_b].data;
				second = true;
				first = false;
				jr_tmp_b = b.AN[temp_b].NR;
				t_c = b.AN[temp_b].NR;
				tmp_c_b = t_c;
			}
			if (col == col_b) {
				matrix[ia][col] = this->AN[temp].data + b.AN[temp_b].data;
				second = true;
				first = true;
				jr_tmp = this->AN[temp].NR;
				t = this->AN[temp].NR;
				tmp_c = t;
				jr_tmp_b = b.AN[temp_b].NR;
				t_c = b.AN[temp_b].NR;
				tmp_c_b = b.AN[temp_b].NR;
				if (t_c == tmp_b) {

					second = false;
					if (t != tmp) {
						t_c = -1;
					}
					else t_c = tmp_b;
				}
			}
		}
	}
	return Matrix(matrix, this->nr, this->nc);
}