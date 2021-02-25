GCC = gcc
FLAGS = -std=c99 -pedantic -Wall -pthread

CFLAGS = -lm

PROGS = principal

principal:
	$(GCC) $(FLAGS) modulo.c -c
	$(GCC) $(FLAGS) $@.c -c
	$(GCC) $(FLAGS) -o $@ $@.o modulo.o

clean:
	$(RM) $(PROGS) *.o 