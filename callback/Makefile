CC=g++
CFLAG= -Wall -g -I . -lrt

objs = 
execs = main

all: $(execs)

main: main.cpp
	$(CC) $(CFLAG) -o main main.cpp


test:	all
	@./main

clean:
	rm $(objs) $(execs)


