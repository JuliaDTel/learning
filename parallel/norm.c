#include <math.h>

double Calc_Norm_Ax_b(int n, double* a, double* x, double* b);
double Calc_Norm_Xe_X(int n, double* x);


double Calc_Norm_Ax_b(int n, double* a, double* x, double* b)
{
	int i, j;
	double norm_r = 0.;
    double norm_b = 0.;
    double t, diff;
	for (i = 1; i <= n; i++) {
		double diff = 0.;
        for (j = 1; j <= n; j++) {
			diff += a[(i-1)*n + (j-1)] * x[j-1]; // r(i) += A(i, j)*x(j)
		}
        diff = diff - b[i - 1];
        t = fabs(diff);
        norm_r = (t > norm_r) ? t:norm_r;
        t = fabs(b[i - 1]);
        norm_b = (t > norm_b) ? t:norm_b;
	}
	return (norm_b > 0.) ? (norm_r / norm_b) : 1.;
}

double Calc_Norm_Xe_X(int n, double* x)
{
    int i;
    double max = 0.;
    for (i = 1; i <= n; i++) {
        double t = fabs(x[i - 1] - i % 2);
        max = (t > max) ? t:max;
    }
    return max;
}
