#include <time.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

void Fill_Matrix(int k, double* A, int n);
int Read_Matrix(char *file_matr, double *A, int n);
void Fill_b(double* a, int n, double* b);
double Calc_Norm_Ax_b(int n, double* a, double* x, double* b);
double Calc_Norm_Xe_X(int n, double* x);
int Solve_SLAE(int t, int n, double *A, double *b, double *x);
void Print_Matrix(double* a, int l, int n, int m);


int main(int argc, char* argv[])
{
	int t, n, m, k;
    double t0, n0, m0, k0;
	char* file_matr = 0;
	double *a, *b, *x;
	if (argc >= 5) {
        t0 = atof(argv[1]);
		n0 = atof(argv[2]);
		m0 = atof(argv[3]);
		k0 = atof(argv[4]);
		if ((int)k0 == 0) {
			if (argc >= 6) {
				file_matr = argv[5];
			} else {
                printf("Error: no file with matrix filename\n");
                return 5;
            }
		}
        else if (argc > 5) {
                printf("Error: too many arguments\n");
                return -1;
            }
	} else {
        printf("Error: at least 4 arguments\n");
        return 4;
    }
	// t > 0
    if (t0 <= 0 || t0-(int)t0 > 0.0)
    {
        printf("Error: wrong threads count\n");
        return 1;
    }
	// n > 0
    if (n0 <= 0 || n0-(int)n0 > 0.0)
    {
        printf("Error: wrong n-value\n");
        return 1;
    }
	// m > 0
    if (m0 <= 0 || m0-(int)m0 > 0.0)
    {
        printf("Wrong m-value\n");
        return 2;
    }
	// 0 <= k <= 4
    if (k0 < 0 || k0 > 4 || k0-(int)k0 > 0.0)
    {
        printf("Wrong k-value\n");
        return 3;
    }

    t = (int)t0;
    n = (int)n0;
    m = (int)m0;
    k = (int)k0;

	a = malloc(sizeof(double)*n*n);
	if (k == 0) {
		int result = Read_Matrix(file_matr, a, n);
		if (result == -1) {
            printf("Matrix file open error\n");
            free(a);
            return 6;
        }
		if (result == -2) {
            printf("Matrix file format error\n");
            free(a);
            return 7;
        }
	}
	else
		Fill_Matrix(k, a, n);

	printf("Matrix A:\n");
	Print_Matrix(a, n, n, m);
    
	b = malloc(sizeof(double)*n);
	x = malloc(sizeof(double)*n);

	Fill_b(a, n, b);

    clock_t start = clock();

    Solve_SLAE(t, n, a, b, x);

    clock_t finish = clock();
    double duration = (double) (finish - start) / CLOCKS_PER_SEC;
	printf("Time spent: %10.3e\n", duration);

	if (k == 0)
		Read_Matrix(file_matr, a, n);
	else
		Fill_Matrix(k, a, n);
	Fill_b(a, n, b);

    double rel_norm_r = Calc_Norm_Ax_b(n, a, x, b);
	printf("||Ax-b||/||b|| = %10.3e\n", rel_norm_r);

    double norm_err = Calc_Norm_Xe_X(n, x);
	printf("||x-xe|| = %10.3e\n", norm_err);

	printf("Solution x:\n");
	Print_Matrix(x, n, 1, m);

	free(a);
	free(b);
	free(x);

    return 0;
}

void Fill_b(double* a, int n, double* b)
{
	int i, k;
	for (i = 0; i < n; i++) {
		b[i] = 0.;
		for (k = 0; k <= (n-1)/2; k++) {
			b[i] += a[i*n + 2*k]; // b(i) += A(i, 2*k+1)
		}
	}
}
