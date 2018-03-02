CC = gcc
CFLAGS=-Wall -pedantic -std=c11
NAME= chip8disaster
TESTNAME= test_chip


all: $(NAME)

test: format.o cpu.o stack.o init.o test.c
	$(CC) test.c format.o cpu.o stack.o init.o $(CFLAGS) -o $(TESTNAME)

clean:
	rm *.o $(NAME) $(TESTNAME)

$(NAME): main.c format.o cpu.o stack.o init.o
	$(CC) main.c format.o cpu.o stack.o init.o $(CFLAGS) -o $(NAME)

format.o: format.c format.h
	$(CC) -c format.c $(CFLAGS) -o format.o

cpu.o: cpu.c cpu.h
	$(CC) -c cpu.c $(CFLAGS) -o cpu.o

stack.o: stack.c stack.h
	$(CC) -c stack.c $(CFLAGS) -o stack.o

init.o: init.c init.h
	$(CC) -c init.c $(CFLAGS) -o init.o

