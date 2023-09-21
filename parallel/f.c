#include <math.h>

int MaxInt(int i, int j);
double f(int k, int n, int i, int j);


double f(int k, int n, int i, int j)
{
	double a;
	switch (k) {
	case 1:
		a = n - MaxInt(i, j) + 1.;
		break;
	case 2:
		a = MaxInt(i, j);
		break;
	case 3:
		a = fabs(i - j);
		break;
	case 4:
		a = 1./(i + j - 1.);
		break;
	}
	return a;
}
