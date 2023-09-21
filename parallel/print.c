#include <stdio.h>

int MinInt(int i, int j);
void Print_Matrix(double* a, int l, int n, int m);


int MinInt(int i, int j)
{
	return i <= j ? i : j;
}

void Print_Matrix(double* a, int l, int n, int m)
{
	int i, j, nrow = MinInt(l, m), ncol = MinInt(n, m);
	for (i = 0; i < nrow; i++) {
		for (j = 0; j < ncol; j++) {
			printf(" %10.3e", a[i*n + j]); // A(i, j) lxn; example 1.123e-003
		}
		printf("\n");
	}
}
