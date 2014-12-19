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
#include <semaphore.h>
#include <errno.h>
#include <stdbool.h>

//prototypes
void Professor();
void* HelperProf();
void AnswerStart();
void AnswerDone();
void Student(int id);
void* HelperStudent();
void EnterOffice();
void QuestionStart();
void QuestionDone();
void LeaveOffice();

/*Represents a student in a queue. A student has an id,
a certain number of questions, and can either be in the 
office or outside the office*/
struct student{
	int id, num_question, in_office;
	struct student *next;
};

//global variables
int capacity = 0; //capacity of the office
int incoming = 0; //total number of students
int in_room = 0; //number of students in the office
int leave = false; //student left the queue
sem_t prof; //used to make professor wait for student
sem_t stud; //used to make student wait for professor
sem_t satisfied; //used to signal professor
pthread_mutex_t student; //used to make only 1 student speak at a time
pthread_mutex_t enqueue; //used to add a student to the queue
pthread_barrier_t start; //used to initialize the queue first
pthread_t professor; //professor thread

//queue pointers
struct student *tail = NULL, *head = NULL, *iterator = NULL, *prev = NULL; 

/*Set the number of students that can fit in the office*/
void setCapacity(int cap){
	capacity = cap;
}

/*Set the number of students wanting to see the professor*/
void setNumStudents(int num){
	incoming = num;
}

/*Creates a professor thread.*/
void Professor(){
	//initialize the mutexes, semaphores and barriers
	pthread_mutex_init(&student, NULL);
	pthread_mutex_init(&enqueue, NULL);
	sem_init(&prof, 0, 0);
	sem_init(&stud, 0, 0);
	sem_init(&satisfied, 0 ,0);
	pthread_barrier_init(&start,NULL,incoming);
	
	if(pthread_create(&professor, NULL, HelperProf, NULL) !=0){
		perror("Professor thread creation failed");
		exit(0);
	}
}

/*The function used by the professor thread. So long as there are students,
the professor waits for a student to ask a question, responds, and then 
alerts the student that he has finished. If there are no more students in the
queue, the professor naps.*/
void* HelperProf(){
	while(iterator != NULL || incoming > 0){
		AnswerStart();
		AnswerDone();	
		if(incoming == 0){printf("Professor naps...\n");}
	}
}

/*The Professor waits for the student to ask a question before starting to 
answer it.*/
void AnswerStart(){
	sem_wait(&prof); //wait for student
	printf("Professor starts to answer question for student %i.\n", iterator->id);
}

/*The Professor signals the student to continue after the student's question
was answered.*/
void AnswerDone(){
	printf("Professor is done with answer for student %i.\n", iterator->id);
	sem_post(&stud); //signal student
	sem_wait(&satisfied); //wait for student to be satisfied
}

/*Creates Students with a given id number.*/
void Student(int id){	
	//create student node
	struct student *student_node = malloc(sizeof(*student_node));
	student_node->in_office = false; //not in the office
	student_node->id = id; //student id
	student_node->num_question = id % 4 + 1; //#questions:{1..4}
	
	pthread_t s; //student thread
	if(pthread_create(&s, NULL, HelperStudent, (void*)student_node)!= 0){
		perror("Student thread creation failed");
		exit(0);
	}
}

/*The function used by the student threads. When each student thread is created,
 it adds its student into the queue. If there is space in the office, students 
enter and take turns asking their questions. Students with no questions left 
leave the office.*/
void* HelperStudent(void * s){
	struct student * stu = s;

	//enqueue the student 
	pthread_mutex_lock(&enqueue);
	if(head != NULL){ tail = tail->next = stu; }
	else{ tail = prev = iterator = head = stu; }
	pthread_mutex_unlock(&enqueue);
	pthread_barrier_wait(&start);
		
	//while there are still students in the queue
	while(iterator != NULL){
		//student thread picks up lock
		pthread_mutex_lock(&student);
		//handles the entering of students
		EnterOffice();
		//if the current student has questions left...
		if(iterator != NULL && iterator->num_question > 0){
			QuestionStart(); 
			QuestionDone(); 
		}
		//if a student has no questions left...
		if(iterator != NULL && iterator->num_question == 0){
			LeaveOffice(); //the student leaves
		}
		
		//signal professor to move on to next student
		sem_post(&satisfied);		

		if(leave){ leave = false; }
		// if a student did not leave, go to the next student
		else if(iterator != NULL){
			//if the current student is not the last in the list...
			if( iterator->next != NULL){
				prev = iterator;
				iterator = iterator->next; //get the next student
			}
			//otherwise, go back to the first student
			else{ iterator = head;}
		}	
		pthread_mutex_unlock(&student); //student releases lock
	}//end of while
	pthread_exit(NULL);
}

/*Checks whether the student can enter the room based on the capacity of the 
room and the number of students already inside the room.*/
void EnterOffice(){
	//if the student is not in the office already
	if(iterator != NULL && !iterator->in_office){
		//and there is space in the office
		if(in_room < capacity){
			//enter the room
			in_room++;
			iterator->in_office = true; //inside the room
			printf("Student %i enters the office.\n", iterator->id);
		}
		else{ iterator = head; }
	}
}

/*Student asks a question and signals the professor that a question was asked*/
void QuestionStart(){
	printf("Student %i asks a question.\n", iterator->id);
	sem_post(&prof); //signal professor	
}

/*Student waits for the professor's response and is satisfied when it is given.*/
void QuestionDone(){
	sem_wait(&stud); //wait for professor's answer
	iterator->num_question--;
	printf("Student %i is satisfied.\n", iterator->id);
}

/*A function that handles removing a student from the list of students in the room*/
void LeaveOffice(){
	--in_room; //decrement the number of people in the room
	--incoming; //decrement the total number of students
	printf("Student %i leaves the office.\n", iterator->id);

	//case 1: last student in the list is removed, and no
	//more students remain
	if(incoming == 0 && iterator->next == NULL){ 
		iterator = NULL;
		leave = true;
	}
	//case 2: dequeue the first student in the list
	else if(head == iterator && iterator->next != NULL){ 
		head = iterator->next;
		iterator = head;
		leave = true;
	}
	//case 3: remove a student in the middle of the list
	else if(iterator->next != NULL && prev->next != NULL){
		prev->next = iterator->next;
		iterator = prev->next;
		leave = true;
	}
	//case 4: the last student in the list is removed, but
	//there are still students waiting for the professor
	else if(iterator->next == NULL){ 
		prev->next = iterator->next;
		iterator = head;
		leave = true;
	}
}

int main(int argc, char* argv[]){
	int i;
	int cap = 0; //the capacity of the office
	int num = 0; //the number of students
	
	//for validating command line parameters
	int status1 = 0; 
	int status2 = 0;

	if( argc == 3){
		status1 = sscanf(argv[1], "%d", &num);
		status2 = sscanf(argv[2], "%d", &cap); 	
		//test whether the two parameters are integers
		if(status1 != 1 && status2 != 1){
			printf("ERROR: Enter the number of students and the capacity as integers > 0\n");
			return 0;
		}
		//test whether the integers are in the acceptable range (>0)
		if(num <= 0 || cap <= 0){ 
			printf("INVALID INPUT: Student and Capacity must be > 0\n"); 
			return 0; 
		}
		
		//set the capacity and the number of students
		setCapacity(cap);
		setNumStudents(num);
		
		//create the professor
		Professor();
		//create the students	
		for(i = 0; i < num; i++){ Student(i); }
		
		pthread_join(professor, NULL);
	}
	else{ //2 parameters were not supplied
		printf("ERROR: Enter the number of students and the capacity of the room\n");
	}
	return 0;
}

