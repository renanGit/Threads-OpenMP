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
 
#define M 500
#define N 500

//pragmas for outer and middle for loops
//both pragmas run when both uncommented
//#define OUTER //comment out for only middle for pragma
//#define MIDDLE //comment out for only outer for pragma

int main(int argc, char *argv) {
//set number of threads here
omp_set_num_threads(1);
 
int i, j, k;
double sum;
double **A, **B, **C;
 
A = malloc(M*sizeof(double *));
B = malloc(M*sizeof(double *));
C = malloc(M*sizeof(double *));
 
for (i = 0; i < M; i++) {
	A[i] = malloc(N*sizeof(double));
	B[i] = malloc(N*sizeof(double));
	C[i] = malloc(N*sizeof(double));
}
 
double start, end;
 
for (i = 0; i < M; i++) {
	for (j = 0; j < N; j++) {
		A[i][j] = j*1;
		B[i][j] = i*j+2;
		C[i][j] = j-i*2;
   	}
}
 
start = omp_get_wtime();
#ifdef OUTER 
#pragma omp parallel for shared(A,B,C) private(i,j,k,sum)
#endif
for (i = 0; i < M; i++) {
	#ifdef MIDDLE
	#pragma omp parallel for shared(A,B,C) private(j,k,sum)
	#endif
	for (j = 0; j < N; j++) {
		sum = 0;
		for (k=0; k < M; k++) {
        		sum += A[i][k]*B[k][j];
     		}
     		C[i][j] = sum;
 	}
}

end = omp_get_wtime();
 
printf("Time of computation: %f\n", end-start);
}

