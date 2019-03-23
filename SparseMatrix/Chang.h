#pragma once
struct Element_chang
{
	int data;
	int JA;
};

class Chang
{
	int nr;
	int nc;
	int count;
	Element_chang *AN;
	int *JR;
public:
	Chang() {
		nr = 0;
		nc = 0;
		count = 0;
		this->AN = new Element_chang[10000];

	}
	Chang(int **matrix, int n_r, int n_c);
	void BoxingShow();
	int** Unboxing();
	void UnboxingShow();
	Chang addmatr(Chang a);
};

