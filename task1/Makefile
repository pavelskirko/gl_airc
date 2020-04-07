CC=gcc
CFLAGS=-I.
DEPS = signal_gen.h
OBJ = signal_gen.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

signal_gen: $(OBJ)  
	$(CC) -o $@ $^ $(CFLAGS) 