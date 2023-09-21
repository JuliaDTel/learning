// A[i*n + j] - row i column j, total m rows, n columns

#include <malloc.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <string.h>

struct Rotate_ij_Ak_arg {
    int n;
    double *A;
    double *b;
    int i;
    int j;
    double s;
    double c;
    int k;
};



double Sqr(double x);
int Calc_S_and_C(double Aii, double Aij, double *sp, double *cp);
int Rotate_ij(int t, int n, double *A, double *b, int i, int j, double s, double c);
int Solve_SLAE(int t, int n, double *A, double *b, double *x);
void* Rotate_ij_Ak_runner(void *arg_ptr);
int Rotate_ij_Ak(int n, double *A, double *b, int i, int j, double s, double c, int k);


double Sqr(double x)
{
    return x * x;
}

int Calc_S_and_C(double Aii, double Aij, double *sp, double *cp)
{
    double s, c, f, d;
    d = sqrt(Sqr(Aii)+Sqr(Aij));
    s = -Aij / d;
    c = Aii / d;
    *sp = s;
    *cp = c;
}

int Rotate_ij(int t, int n, double *A, double *b, int i, int j, double s, double c)
{
    int threads_needed = n - j;
    int threads_count = threads_needed > t ? t : threads_needed;
    pthread_t *threads = (pthread_t*) malloc(threads_count * sizeof(pthread_t));
    struct Rotate_ij_Ak_arg *args = (struct Rotate_ij_Ak_arg*) malloc(threads_count * sizeof(struct Rotate_ij_Ak_arg));
    int k, thread_i;
    for (k = j, thread_i = threads_count-1; k < n; k ++, thread_i --) {
        if (thread_i < 0) {
            for (thread_i = 0; thread_i < threads_count; thread_i++) {
                pthread_join(threads[thread_i], 0);
            }
            thread_i = threads_count-1;
        }
        args[thread_i].n = n;
        args[thread_i].A = A;
        args[thread_i].b = b;
        args[thread_i].i = i;
        args[thread_i].j = j;
        args[thread_i].s = s;
        args[thread_i].c = c;
        args[thread_i].k = k;
        int error = pthread_create(&threads[thread_i], 0, Rotate_ij_Ak_runner, (void*)(&args[thread_i]));
        if (error != 0) {
            printf("Unable to create thread: %s\n", strerror(error));
        }
    }
    double bj_new = c * b[j] - s * b[i];
    b[i] = s * b[j] + c * b[i];
    b[j] = bj_new;
    for (thread_i = 0; thread_i < threads_count; thread_i++) {
        pthread_join(threads[thread_i], 0);
    }
}

void* Rotate_ij_Ak_runner(void *arg_ptr)
{
    struct Rotate_ij_Ak_arg* arg = (struct Rotate_ij_Ak_arg*) arg_ptr;
    int n = arg->n;
    double *A = arg->A;
    double *b = arg->b;
    int i = arg->i;
    int j = arg->j;
    double s = arg->s;
    double c = arg->c;
    int k = arg->k;
    Rotate_ij_Ak(n, A, b, i, j, s, c, k);
}

int Rotate_ij_Ak(int n, double *A, double *b, int i, int j, double s, double c, int k)
{
    double Ajk_new = c * A[j*n+k] - s * A[i*n+k]; // diagonal
    double Aik_new = s * A[j*n+k] + c * A[i*n+k];
    A[i*n+k] = Aik_new;
    A[j*n+k] = Ajk_new;
}

int Rotate_ij_b(int n, double *A, double *b, int i, int j, double s, double c)
{
    double bj_new = c * b[j] - s * b[i];
    b[i] = s * b[j] + c * b[i];
    b[j] = bj_new;
}

int Solve_SLAE(int t, int n, double *A, double *b, double *x)
{
    int i, j;
    double s, c;
    // nullifying first column, until n-1 for last diagonal to be non-zero
    for (j = 0; j < n - 1; j ++) {
        // iterate rows by j in column i; begin below diagonal
        for (i = j + 1; i < n; i ++) {
            // for an under-diagonal element we calculate s and c
            double Aii = A[j*n+j]; // diagonal
            double Aij = A[i*n+j]; // current under-diagonal
            if (fabs(Aij) < 0.000001)
            {
                // Already zero
                continue;
            }
            Calc_S_and_C(Aii, Aij, &s, &c);
            // recalculate each element in two rows
            Rotate_ij(t, n, A, b, i, j, s, c);
        }
    }
    for (i = n-1; i >= 0; i --) {
        x[i] = b[i] / A[i*n+i];
        for (j = i+1; j < n; j ++) {
            x[i] -= x[j] * A[i*n+j] / A[i*n+i];
        }
    }
}

