CC = gcc
CFLAGS=-Wall


all: chip8disassembler

clean:
	rm *.o chip8disassembler

chip8disassembler: main.c format.o cpu.o stack.o init.o
	$(CC) main.c format.o cpu.o stack.o init.o $(CFLAGS) -o chip8disassembler

format.o: format.c format.h
	$(CC) -c format.c $(CFLAGS) -o format.o

cpu.o: cpu.c cpu.h
	$(CC) -c cpu.c $(CFLAGS) -o cpu.o

stack.o: stack.c stack.h
	$(CC) -c stack.c $(CFLAGS) -o stack.o

init.o: init.c init.h
	$(CC) -c init.c $(CFLAGS) -o init.o

