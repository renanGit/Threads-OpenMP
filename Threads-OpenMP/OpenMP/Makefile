TITLE = helloworld task2_2 task2_3 task2_4
CFLAGS = -fopenmp

iterate:
	$(foreach var, $(TITLE), gcc -o $(var) $(var).c $(CFLAGS) ;)	

clean:
	rm $(TITLE) *.o

