COP4610 – Principles of Operating Systems – Summer C 2014
Prof. Jose F. Osorio
Group: Apsalar
Group Members: Maylem Gonzalez – 2134900
               Renan Santana – 4031451
File: README

Locations:
	CentOS: /root/Desktop/Assignment3
	Dingo: /cop4610-vmstorage/students/mgonz108/Assignment3
Task 1.1
To run this task, open the file task1_2.c and comment out line number 23, which reads "#define PTHREAD_SYNC." This will disable all the synchronization changes that took place in Task 1.2. After this line has been commented out, typing in "make" in the directory of the file will compile it.

Task 1.2
Open the file task1_2.c and leave line number 23 ("#define PTHREAD_SYNC") uncommented. Type in "make" in the directory of the file to compile it.

Task 1.3
To run this task, compile task1_3.c by typing "make" into the directory. The program must be provided with two parameters; the first representing the total number of students, and the second representing the capacity of the office. For example, type the following into the terminal to run this task for 100 students and an office capacity of 8 students: ./task1_3 100 8

Task 2.1
To run this task, navigate to the OpenMP subdirectory of the provided folder. The file helloworld.c (task 2.1) is compiled by entering make into the terminal at the file's directory. To run this task, type ./helloworld into the terminal. To change the number of threads used in this task, enter "export OMP_NUM_THREADS=#" into the terminal, where # is the number of threads wanted. To verify the number of threads being created, enter "echo $OMP_NUM_THREADS". 

Task 2.2
To compile this task, navigate to the OpenMP subdirectory and type "make" into the terminal. The task can be run by entering ./task2_2 into the terminal. The scheduling of the threads can be changed from dynamic to static by changing the word "dynamic" in line 49 to "static". The number of threads used in the task can be modified as described above under Task 2.1.

Task 2.3
To compile this task, navigate to the OpenMP subdirectory and type "make" into the terminal. The task can be run by entering the following into the terminal: ./task2_3. The number of threads used can be modified as described above under Task 2.1.

Task 2.4
To compile this task, navigate to the OpenMP subdirectory and type "make" into the terminal. The task can be run by entering ./task2_4 into the terminal. To modify the number of threads used, changed the number in omp_set_num_threads(#) on line 32. To modify the size of the matrix, change the values of M and N on lines 22 and 23. To compile the file with only the outer for loop parallelized, comment out line 28 ("#define MIDDLE"). To only parallelize the middle for loop, comment out line 27 ("#define OUTER"). To run the task with both of these for loops parallelized, leave both of these lines uncommented. To run the task without any parallelization, comment out both of these lines.

