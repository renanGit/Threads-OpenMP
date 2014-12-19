/*
##########################################################
## COP4610 – Principles of Operating Systems – Summer C 2014
## Prof. Jose F. Osorio
## Group: Apsalar
## Group Members: Maylem Gonzalez – 2134900
##                Renan Santana – 4031451
## Project: Multithreaded Programming
## Specs:  
## Due Date: 07/09/2014 by 11:55pm
## Module Name:
##
## We Certify that this program code has been written by us
## and no part of it has been taken from any sources.
##########################################################
*/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define CHUNKSIZE 10
#define N 100

int main (int argc, char *argv[]) {
	int nthreads, tid, i, chunk;

	float a[N], b[N], c[N];
	double dtime; //stores the execution time
	
	for (i=0; i < N; i++)
    		a[i] = b[i] = i * 1.0; // initialize arrays

	chunk = CHUNKSIZE;

	dtime = omp_get_wtime(); //get start time

	#pragma omp parallel shared(a,b,c,nthreads,chunk) private(i,tid) 
	{	
		tid = omp_get_thread_num();

		if (tid == 0) {
			nthreads = omp_get_num_threads();
			printf("Number of threads = %d\n", nthreads);
		}

		printf("Thread %d starting...\n",tid);
	
		#pragma omp for schedule(dynamic,chunk)
		for (i=0; i<N; i++) {
			c[i] = a[i] + b[i];
			printf("Thread %d: c[%d]= %f\n",tid,i,c[i]);
		}
	
	} /* end of parallel section */
	dtime = omp_get_wtime() - dtime; //subtract end time from start time
	printf("OpenMP runtime: %f\n", dtime);
}

