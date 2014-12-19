TITLE = task1_2 task1_3
CFLAGS = -lpthread -lrt -g

iterate:
	$(foreach var, $(TITLE), gcc -o $(var) $(var).c $(CFLAGS) ;)	

clean:
	rm $(TITLE) *.o

