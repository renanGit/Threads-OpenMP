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

int main (int argc, char *argv[]) {

	int nthreads, tid; 

	/* Fork a team of threads giving them their own copies of variables */
	#pragma omp parallel private(nthreads, tid)
	{
		
		tid = omp_get_thread_num(); // Obtain thread number
		printf("Hello World from thread = %d\n", tid);

		if (tid == 0) { // Only master thread does this
			nthreads = omp_get_num_threads();
			printf("Number of threads = %d\n", nthreads);
		}

	} /* All threads join master thread and disband */
}

