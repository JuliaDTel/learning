#include <math.h>
#include <stdio.h>

double f(int k, int n, int i, int j);
void Fill_Matrix(int k, double* A, int n);
int Read_Matrix(char *file_matr, double *A, int n);
int MaxInt(int i, int j);


int MaxInt(int i, int j)
{
	return i >= j ? i : j;
}

void Fill_Matrix(int k, double* A, int n)
{
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			A[i*n + j] = f(k, n, i+1, j+1); // A(i, j) nxn
		}
	}
}

int Read_Matrix(char *file_matr, double *A, int n)
{
	int i, j, num = 0;
	double t;
	FILE* f = fopen(file_matr, "rt");
	if (f == 0)
        return -1; // open error
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (fscanf(f, "%lg", &t) == 1) {
				A[i*n + j] = t; // A(i, j) nxn
				num++;
			}
			else
				break;
		}
	}
	fclose(f);

	if (num != (n * n))
        return -2; // data error

	return 0;
}

