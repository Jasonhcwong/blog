CC=gcc
CFLAG= -msse4 -g -O2

objs = strlenCommon.o
execs = naiveStrlen betterStrlen sse42Strlen


all: $(execs)

strlenCommon.o: strlenCommon.c strlenCommon.h
	$(CC) $(CFLAG) -o strlenCommon.o -c strlenCommon.c

naiveStrlen: naiveStrlen.c strlenCommon.o
	$(CC) $(CFLAG) -o naiveStrlen naiveStrlen.c strlenCommon.o

betterStrlen: betterStrlen.c strlenCommon.o
	$(CC) $(CFLAG) -o betterStrlen betterStrlen.c strlenCommon.o

sse42Strlen: sse42Strlen.c strlenCommon.o
	$(CC) $(CFLAG) -o sse42Strlen sse42Strlen.c strlenCommon.o

clean:
	rm $(objs) $(execs)


