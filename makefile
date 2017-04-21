CC=clang
CFLAGS= -c -Wall

all: test
test: main.o regions.o
	$(CC) main.o regions.o  -o test

test.o: main.c
	$(CC) $(CFLAGS) main.c

regionsV3.o: regions.c regions.h
	$(CC) $(CFLAGS) regions.c


clean:
	rm -rf *.o test