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

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define PTHREAD_SYNC //comment out to disable synchronization

int SharedVariable = 0;
pthread_mutex_t lock;
pthread_barrier_t barr;

/*A function that takes a thread number and loops for 20 times,
 *incrementing a shared variable with each iteration of the loop. 
*/
void SimpleThread(int which) {
	int num, val;

	for(num = 0; num < 20; num++) {
		if (random() > RAND_MAX / 2){ usleep(10); }
	#ifdef PTHREAD_SYNC		
		pthread_mutex_lock(&lock);
	#endif
		val = SharedVariable;
		printf("*** thread %d sees value %d\n", which, val); 
		SharedVariable = val + 1;
	#ifdef PTHREAD_SYNC
		pthread_mutex_unlock(&lock);
	#endif
	}
	#ifdef PTHREAD_SYNC
	pthread_barrier_wait(&barr);
	#endif
	val = SharedVariable;
	printf("Thread %d sees final value %d\n",which, val);
}

/*Starts a thread with a given thread id*/
void * runFunction(void * arg){
	int t_pid = (intptr_t) arg;
	SimpleThread(t_pid);
}

int main(int argc, char *argv[]){
	int i;
	int pthread_num; //number of the threads wanted
	pthread_mutex_init(&lock, NULL);
	if( argc == 2){
		//validate command line parameter
		if (sscanf (argv[1], "%d", &pthread_num)!=1){
			printf("ERROR: Enter the number of threads as an integer");
		}
		//array of threads
		pthread_t t[pthread_num];
		//barrier that forces threads to wait for each other
		pthread_barrier_init(&barr, NULL, pthread_num);
		//create the threads
		for(i = 0; i < pthread_num; i++){
			pthread_create(&t[i], NULL, runFunction, (void *)(intptr_t) i);
		}		
		//join the threads with the parent	
		for(i = 0; i < pthread_num; i++){
			pthread_join(t[i] , NULL);
		}
	}
	return 0;
}
