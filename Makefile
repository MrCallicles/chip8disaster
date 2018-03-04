CC = gcc
CFLAGS=-Wall -pedantic -std=c11
NAME= chip8disaster
TESTNAME= test_chip


all: $(NAME)

clean:
	rm *.o test/*.o $(NAME) $(TESTNAME)

test: format.o cpu.o stack.o init.o test/test.c test/test.h \
	test/test_decrementdelay.o test/test_cpuexeccode.o test/test_getinstructionasm.o \
	test/test_initcpu.o test/test_getinstructionid.o test/test_getoponevalue.o \
	test/test_getoptwovalue.o test/test_getinstruction.o
	$(CC) test/test.c format.o cpu.o stack.o init.o test/test_initcpu.o test/test_getoptwovalue.o \
		test/test_getoponevalue.o test/test_getinstructionid.o test/test_getinstructionasm.o \
		test/test_getinstruction.o test/test_decrementdelay.o test/test_cpuexeccode.o \
		$(CFLAGS) -o $(TESTNAME)

test/test_initcpu.o : test/test_initcpu.c test/test.h
	$(CC) -c test/test_initcpu.c $(CFLAGS) -o test/test_initcpu.o

test/test_getoptwovalue.o : test/test_getoptwovalue.c test/test.h
	$(CC) -c test/test_getoptwovalue.c $(CFLAGS) -o test/test_getoptwovalue.o

test/test_getoponevalue.o : test/test_getoponevalue.c test/test.h
	$(CC) -c test/test_getoponevalue.c $(CFLAGS) -o test/test_getoponevalue.o

test/test_getinstructionid.o : test/test_getinstructionid.c test/test.h
	$(CC) -c test/test_getinstructionid.c $(CFLAGS) -o test/test_getinstructionid.o

test/test_getinstructionasm.o : test/test_getinstructionasm.c test/test.h
	$(CC) -c test/test_getinstructionasm.c $(CFLAGS) -o test/test_getinstructionasm.o

test/test_getinstruction.o : test/test_getinstruction.c test/test.h
	$(CC) -c test/test_getinstruction.c $(CFLAGS) -o test/test_getinstruction.o

test/test_decrementdelay.o : test/test_decrementdelay.c test/test.h
	$(CC) -c test/test_decrementdelay.c $(CFLAGS) -o test/test_decrementdelay.o

test/test_cpuexeccode.o : test/test_cpuexeccode.c test/test.h
	$(CC) -c test/test_cpuexeccode.c $(CFLAGS) -o test/test_cpuexeccode.o

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

