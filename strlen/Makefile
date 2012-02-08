CC=gcc
CFLAG= -msse4 -g -O2

objs = strlenCommon.o
execs = naiveStrlen betterStrlen sse42Strlen libcStrlen
nTimes = 1000000

all: $(execs)

strlenCommon.o: strlenCommon.c strlenCommon.h
	$(CC) $(CFLAG) -o strlenCommon.o -c strlenCommon.c

naiveStrlen: naiveStrlen.c strlenCommon.o
	$(CC) $(CFLAG) -o naiveStrlen naiveStrlen.c strlenCommon.o

betterStrlen: betterStrlen.c strlenCommon.o
	$(CC) $(CFLAG) -o betterStrlen betterStrlen.c strlenCommon.o

sse42Strlen: sse42Strlen.c strlenCommon.o
	$(CC) $(CFLAG) -o sse42Strlen sse42Strlen.c strlenCommon.o

libcStrlen: libcStrlen.c strlenCommon.o
	$(CC) $(CFLAG) -o libcStrlen libcStrlen.c strlenCommon.o

test:
	@echo "size,naiveStrlen,betterStrlen,sse42Strlen,libcStrlen"
	@for ((i = 2; i <= 1024; i = i + 2)) ; do \
		echo "$$i,"`./naiveStrlen  $(nTimes) $$i`","`./betterStrlen $(nTimes) $$i`","`./sse42Strlen  $(nTimes) $$i`","`./libcStrlen  $(nTimes) $$i` ; \
	done
	@echo "size,naiveStrlen,betterStrlen,sse42Strlen,libcStrlen"
	@for ((i = 1; i <= 65536; i = i * 2)) ; do \
		echo "$$i,"`./naiveStrlen  $(nTimes) $$i`","`./betterStrlen $(nTimes) $$i`","`./sse42Strlen  $(nTimes) $$i`","`./libcStrlen  $(nTimes) $$i` ; \
	done

clean:
	rm $(objs) $(execs)


