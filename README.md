Threads-OpenMP
==============

Description
In part 1 of this assignment, you will be working with the "threads"' subsystem of Linux. This is the part of Linux that supports multiple concurrent activities within the kernel. In the exercises below, you will write a simple program that creates multiple threads, you will demonstrate the problems that arise when multiple threads perform unsynchronized access to shared data, and you will rectify these problems by introducing synchronization (in the form of Pthreads mutex) into the code. Then, you will simulate one real world synchronization problem by using the synchronization primitives supplied by Pthreads.
In part 2 you will work on a number of tasks in which you will learn and put to practice basic OpenMP directives to parallelize linear code in C and apply synchronization directives equivalent to those provided by the pthread library.
 
Part 1: Simple Multi-threaded Programming using Pthreads
 
The purpose of this exercise is for you to get some experience using the threads primitives provided by Pthreads [1], and to demonstrate what happens if concurrently executing threads access shared variables without proper synchronization. Then you will use the mutex synchronization primitives in Pthreads to achieve proper synchronization.

Part 2: Multi-threaded/Parallel Programming using OpenMP
 
The purpose of this exercise is for you to get some experience using OpenMP directives to turn linear program code into concurrent regions that can execute in parallel in modern multicore systems and to practice with the various synchronization primitives that the API provides.
 
The programs listed in each task are to be compiled and run in both dingo and in your CentOS VMs and the output collected from both environments are to be included in your report and spreadsheet along with your observations.
