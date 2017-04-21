CC=clang
CFLAGS= -c -Wall

all: test

test.o: main.c
	$(CC) $(CFLAGS) main.c



clean:
	rm -rf *.o test
