#include <stdlib.h>
#include <malloc.h> 
#include <math.h>

double _sampen(double *y, int n, int M, double r)
{

    double *p = NULL;
    double *e = NULL;
    long *run = NULL, *lastrun = NULL, N;
    double *A = NULL, *B = NULL;
    int M1, j, nj, jj, m;
    int i;
    double y1;
	double result;
	
    M++;
    if ((run = (long *) calloc(n, sizeof(long))) == NULL)
	exit(1);
    if ((lastrun = (long *) calloc(n, sizeof(long))) == NULL)
	exit(1);
    if ((A = (double *) calloc(M, sizeof(double))) == NULL)
	exit(1);
    if ((B = (double *) calloc(M, sizeof(double))) == NULL)
	exit(1);
    if ((p = (double *) calloc(M, sizeof(double))) == NULL)
	exit(1);

    /* start running */
    for (i = 0; i < n - 1; i++) {
	nj = n - i - 1;
	y1 = y[i];
	for (jj = 0; jj < nj; jj++) {
	    j = jj + i + 1;
	    if (((y[j] - y1) < r) && ((y1 - y[j]) < r)) {
		run[jj] = lastrun[jj] + 1;
		M1 = M < run[jj] ? M : run[jj];
		for (m = 0; m < M1; m++) {
		    A[m]++;
		    if (j < n - 1)
			B[m]++;
		}
	    }
	    else
		run[jj] = 0;
	}			/* for jj */
	for (j = 0; j < nj; j++)
	    lastrun[j] = run[j];
    }				/* for i */

    N = (long) (n * (n - 1) / 2);
//    p[0] = A[0] / N;
//    printf("SampEn(0,%g,%d) = %lf\n", r, n, -log(p[0]));

//    for (m = 1; m < M; m++) {
	m=M-1;
	if (m==0)
	    p[0] = A[0] / N;
	else
	    p[m] = A[m] / B[m - 1];

	if (p[m] == 0)
	    result =  - _HUGE;
	else
	    result = -log(p[m]);
//    }

    free(A);
    free(B);
    free(p);
    free(run);
    free(lastrun);
    return(result);
}
/* ==================================================================== */
